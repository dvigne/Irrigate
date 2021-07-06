#include "../include/ZoneManager.hpp"
#include <configuration.h>
#include <Oops.hpp>

void ZoneManager::initialize(const String configurationFile, uint16_t size) {
  zoneFile = new DynamicJsonDocument(size);

  // Setup Pinmodes
  for (size_t i = 0; i < 4; i++) {
    pinMode(ZONES[i], OUTPUT);
  }

  Serial.println("Reading Flash Configuration");

  File jsonFile = LittleFS.open(configurationFile, "r+");
  DeserializationError err = deserializeJson(*zoneFile, jsonFile.readString());
  if (err) {
    Oops::setFlag(JSON_PARSING_ERROR);
    Serial.println("An Error Occured:");
    Serial.println(err.c_str());
  }

  serializeJsonPretty(*zoneFile, Serial);

  Serial.println("\nZone Manager Initialized");
}

void ZoneManager::activateZone(uint8_t zoneNumber) {
  if (activeZone) {
    deactivateZone(zoneNumber);
  }
  // TODO: Set ZoneManager::startTime from TimeLib on DS1307
  digitalWrite(ZONES[zoneNumber - 1], HIGH);
  activeZone = (_zones) zoneNumber;
}

void ZoneManager::deactivateZone(uint8_t zoneNumber) {
  if (activeZone == zoneNumber) {
    digitalWrite(ZONES[zoneNumber - 1], LOW);
    activeZone = NO_ZONE;
  }
}

bool ZoneManager::isActive(uint8_t zoneNumber) {
  return activeZone;
}

void ZoneManager::addTime(uint8_t zoneNumber, Time time) {
  return;
}

void ZoneManager::removeTime(uint8_t zoneNumber, Time time) {
  return;
}

String ZoneManager::getZoneName(uint8_t zoneNumber) {
  return (*zoneFile)["zones"][zoneNumber - 1]["name"];
}


void ZoneManager::idle() {
  return;
}
