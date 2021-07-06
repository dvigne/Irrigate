#pragma once

/////////////////////////////////////////////////
/// Global Defines
/////////////////////////////////////////////////

#define STATUS_LED 16

const String statusClasses[] = { "text-primary", "text-warning" };
const String statusMessages[] = { "Everything is Good", "Needs Your Attention" };

enum _errorFlags { NO_ERRORS, TIME_NOT_SET, JSON_PARSING_ERROR };
