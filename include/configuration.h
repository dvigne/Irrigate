#pragma once

/////////////////////////////////////////////////
/// General Configuration
/////////////////////////////////////////////////

// Turn Status LED On?
#define STATUS true

// Number of Zones
#define NUM_ZONES 4

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
const uint8_t ZONES[NUM_ZONES] = { 14, 12, 13, 15 }; // Zone 1, Zone 2, Zone 3, Zone 4

// Buzzer Pin
#define SPKR 0
