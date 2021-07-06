#include <Arduino.h>
#include <pgmspace.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncDNSServer.h>
#include <ESPAsyncWebServer.h>
#include <types.h>
#include <configuration.h>
#include <Oops.hpp>
#include <ZoneManager.hpp>

// Global Objects
AsyncDNSServer dnsServer;
AsyncWebServer webServer(PORT);

void setup() {
  Serial.begin(9600);
  LittleFS.begin();

  Serial.println("Starting up");

  WiFi.softAP(SSID, PASSWORD, CHANNEL, HIDDEN, MAX_CLIENTS) ? Serial.println("Wifi Network Started")
                                                            : Serial.println("Wifi Network Failed to Start");

  dnsServer.setErrorReplyCode(AsyncDNSReplyCode::ServerFailure);
  dnsServer.start(53, DOMAIN_NAME, IPAddress(192,168,4,1));

  Oops::initialize();
  ZoneManager::initialize();

  // Register Routes
  webServer.serveStatic("/css", LittleFS, "/css");

  webServer.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", String(), false, [](const String& var) {
        if(var == "STATUS_CLASS") {
          return statusClasses[Oops::getFlag()];
        }
        if(var == "STATUS_TEXT") {
          return statusMessages[Oops::getFlag()];
        }
        if(var == "ZONENAME") {
          return ZoneManager::getZoneName(4);
        }
        if(var == "ZONETIME") {
          return String("9:00 pm");
        }
        if(var == "ZONEDURATION") {
          return String("30 Minutes");
        }
        return String(" ");
    });
  });

  webServer.begin();

  // Turn on onboard LEDs for status
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  digitalWrite(LED_BUILTIN, !STATUS);
  digitalWrite(STATUS_LED, HIGH);
}

void loop() {
  if(Oops::idle()) {
    return;
  }
  ZoneManager::idle();
}
