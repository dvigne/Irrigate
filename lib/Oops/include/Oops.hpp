#pragma once
#include <types.h>
#include <configuration.h>

class Oops
 {
private:
  // Global Flags
  inline static _errorFlags errorFlag;

  static void _defaultAlert() {
    bool f = true;
    for (size_t i = 0; i < 2; i++) {
      digitalWrite(STATUS_LED, f);
      digitalWrite(SPKR, f);
      delay(250);
      f ^= f;
    }
  }

  static bool _handleError() {
    switch(errorFlag) {
      case NO_ERRORS:
        digitalWrite(STATUS_LED, HIGH);
        return false;
      case TIME_NOT_SET:
        _defaultAlert();
        break;
      case JSON_PARSING_ERROR:
        _defaultAlert();
        break;
    }
    return true;
  }

public:
  static void initialize() {
    Serial.println("Oops Error Handler Initialized");
    errorFlag = TIME_NOT_SET;
  }

  static void setFlag(_errorFlags flag) {
    errorFlag = flag;
  }

  static _errorFlags getFlag() {
    return errorFlag;
  }

  static bool idle() {
    return _handleError();
  }
};
