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
DynamicJsonDocument zoneFile(2048);


void setFlag(_errorFlags flag) {
  errorFlag = flag;
}

_errorFlags getErrorFlags() {
  return errorFlag;
}

void idle() {
  if (timeStatus() != timeSet) {
    errorFlag = TIME_NOT_SET;
  }
}

void runZones() {
  Serial.println("Running Zones");
}

void defaultAlert() {
  digitalWrite(STATUS_LED, HIGH);
  digitalWrite(SPKR, HIGH);
  delay(250);
  digitalWrite(STATUS_LED, LOW);
  digitalWrite(SPKR, LOW);
  delay(250);
}

bool handleError() {
  switch(errorFlag) {
    case NO_ERRORS:
      digitalWrite(STATUS_LED, HIGH);
      return false;
    case TIME_NOT_SET:
      defaultAlert();
      break;
    case JSON_PARSING_ERROR:
      defaultAlert();
      break;
  }
  return true;
}



void setup() {
  LittleFS.begin();

  Serial.begin(9600);
  Serial.println("Starting up");

  WiFi.softAP(SSID, PASSWORD, CHANNEL, HIDDEN, MAX_CLIENTS) ? Serial.println("Wifi Network Started")
                                                            : Serial.println("Wifi Network Failed to Start");


  dnsServer.setErrorReplyCode(AsyncDNSReplyCode::ServerFailure);
  dnsServer.start(53, DOMAIN_NAME, IPAddress(192,168,4,1));

  File jsonFile = LittleFS.open(ZONEFILE, "r+");
  DeserializationError err = deserializeJson(zoneFile, jsonFile.readString());
  if (err) {
    setFlag(JSON_PARSING_ERROR);
    Serial.println(err.c_str());
  }

  Serial.println(zoneFile.size());
  JsonObject testObj = zoneFile.as<JsonObject>();
  String obj;
  serializeJson(zoneFile, obj);
  Serial.println(obj);

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

  // Turn on onboard LEDs for status
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(LED_BUILTIN, !STATUS);
  digitalWrite(STATUS_LED, HIGH);
}

void loop() {
  idle();
  if(handleError()) {
    return;
  }
  runZones();
}
