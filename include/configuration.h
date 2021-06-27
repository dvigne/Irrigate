#pragma once

/////////////////////////////////////////////////
/// General Configuration
/////////////////////////////////////////////////

// Turn Status LED On?
#define STATUS true


/////////////////////////////////////////////////
/// Wifi Configuration
/////////////////////////////////////////////////

// Set the Network Name
#define SSID "Irrigation"

// Set the network password (if blank open network)
#define PASSWORD "P@ssw0rd"

// Make the network hidden?
#define HIDDEN false

// Maximum number of simultaneous connected clients (0 - 8)
#define MAX_CLIENTS 4

// Set the wifi channel (Useful if in congested networks)
#define CHANNEL 6


/////////////////////////////////////////////////
/// Webserver Configuration
/////////////////////////////////////////////////

// Domain name of the webserver -- also used in DNS requests
#define DOMAIN_NAME "irrigate.io"

// Webserver Port
#define PORT 80


/////////////////////////////////////////////////
/// Pinout Configuration
/////////////////////////////////////////////////

// Pins D0-D4 Used for Zones
enum ZONE {
  ZONE_1 = 16,
  ZONE_2 = 5,
  ZONE_3 = 4,
  ZONE_4 = 0
};

// Buzzer Pin
#define SPKR 14
