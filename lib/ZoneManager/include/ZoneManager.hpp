#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <TimeLib.h>
#include <types.h>

struct Time {
  uint8_t hour;
  uint8_t minute;
  bool weekDays[6] = { 0 };
};

class ZoneManager {
private:
  enum _zones{ NO_ZONE, ZONE_1, ZONE_2, ZONE_3, ZONE_4 };
  inline static time_t startTime;
  inline static DynamicJsonDocument * zoneFile;
  inline static _zones activeZone = (_zones) 0;

public:
  static void initialize(const String configurationFile = ZONEFILE, uint16_t size = 4096);
  static void activateZone(uint8_t zoneNumber);
  static void deactivateZone(uint8_t zoneNumber);
  bool isActive(uint8_t zoneNumber);
  static void addTime(uint8_t zoneNumber, Time time);
  static void removeTime(uint8_t zoneNumber, Time time);
  static String getZoneName(uint8_t zoneNumber);
  static void idle();
  // virtual ~ZoneManager ();
};
