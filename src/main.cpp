#include <Arduino.h>
#include <pgmspace.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncDNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <LittleFS.h>
#include <QTE.hpp>
#include <types.h>
#include <configuration.h>

// Global Objects
AsyncDNSServer dnsServer;
AsyncWebServer webServer(PORT);
TemplateEngine engine;
_errorFlags errorFlag = NO_ERRORS;

void setFlag(_errorFlags flag) {
  errorFlag = flag;
}

_errorFlags getErrorFlags() {
  return errorFlag;
}

void defaultAlert() {
  for (size_t i = 0; i < 2; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SPKR, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(SPKR, LOW);
  }
}

void handleError() {
  switch(errorFlag) {
    case NO_ERRORS:
      return;
    case TIME_NOT_SET:
      defaultAlert();
      break;
  }
}



void setup() {
  LittleFS.begin();

  Serial.begin(9600);
  Serial.println("Starting up");

  WiFi.softAP(SSID, PASSWORD, CHANNEL, HIDDEN, MAX_CLIENTS) ? Serial.println("Wifi Network Started")
                                                            : Serial.println("Wifi Network Failed to Start");


  dnsServer.setErrorReplyCode(AsyncDNSReplyCode::ServerFailure);
  dnsServer.start(53, DOMAIN_NAME, IPAddress(192,168,4,1));

  File zoneFile = LittleFS.open(ZONEFILE, "r+");
  String zoneConfiguration = zoneFile.readString();
  Serial.println(zoneConfiguration);

  // Register Routes
  webServer.serveStatic("/css", LittleFS, "/css");

  webServer.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    File file = LittleFS.open("/index.html", "r");
    // char response[1000];
    // sprintf(response, indexPage, "Test Title", pattern, 100);
    String html = file.readString();
    String values[][2] = {{"Hello", "World"}, {"Test", "Render"}};
    String response = engine.renderTemplate(html, values, 2);
    request->send(200, "text/html", response);
    file.close();
  });

  webServer.begin();

  // Turn on onboard LED for status
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, !STATUS);

}

void loop() {
  //
}
