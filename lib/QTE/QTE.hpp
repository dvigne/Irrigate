#pragma once
#include <Arduino.h>
#include "LittleFS.h"

class TemplateEngine {
public:
  String renderTemplate(const String file, const String valueMap[][2] = NULL, size_t count = 0);
};
