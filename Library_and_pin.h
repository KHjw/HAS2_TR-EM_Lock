#include <Arduino.h>

#include <Adafruit_PN532.h>
#include <Adafruit_NeoPixel.h>

#include <HAS2_Wifi.h>
#include <SimpleTimer.h>

#define PN532_SCK     18
#define PN532_MISO    19
#define PN532_MOSI    23
#define PN532_SS      5

#define INDICATOR_NEOPIN  25
#define INDICATOR_NEONUM  10    // INDICATOR 네오픽셀 갯수
#define EM_STATE_NEOPIN  26
#define EM_STATE_NEONUM  3     // INDICATOR 네오픽셀 갯수

#define EM_MOSFET     33