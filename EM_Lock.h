#ifndef _DONE_EMLOCK_CODE_
#define _DONE_EMLOCK_CODE_

#include "Library_and_pin.h"

//****************************************Rfid SETUP****************************************
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

void RfidInit();
void RfidLoop();
void Rfid_Identify(uint8_t data[32]);
void RfidCheckLoop();

String RfidID = "";


//****************************************Neopixel SETUP**************************************************
void NeopixelInit();
void NeoShowColor(int neo_code ,int color_code);

Adafruit_NeoPixel indicator_neo(INDICATOR_NEONUM,INDICATOR_NEOPIN,NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel em_state_neo(EM_STATE_NEONUM,EM_STATE_NEOPIN,NEO_GRB + NEO_KHZ800);

enum {WHITE = 0, RED, YELLOW, GREEN, BLUE, PURPLE, BLACK, BLUE0, BLUE1, BLUE2, BLUE3};     // Neopixel 색상정보

int color[11][3] = {    {20, 20, 20},   //WHITE
                        {40, 0, 0},     //RED        
                        {40, 40, 0},    //YELLOW
                        {0, 40, 0},     //GREEN
                        {0, 0, 40},     //BLUE
                        {40, 0, 40},    //PURPLE
                        {0, 0, 0},      //BLACK
                        {0, 0, 20},     //ENCODERBLUE0
                        {0, 0, 40},     //ENCODERBLUE1
                        {0, 0, 60},     //ENCODERBLUE2
                        {0, 0, 80}};    //ENCODERBLUE3
                        
//****************************************EMlock SETUP**************************************************
void em_control(int state);
void em_init();

int EM_state = 0;

enum {LOCK = 0, OPEN};     // EM 정보
enum {INDICATOR = 0, EM_STATE};     // EM 정보

//****************************************Game System SETUP**************************************************
void device_open();
void device_lock();
void device_setting();
void device_ready();
void device_void();

int current_state = 7;

void (*game_ptr)() = device_setting;

//****************************************WiFi SETUP**************************************************
HAS2_Wifi HAS2wifi;

String current_Gstate = "";
String current_Dstate = "";

void wifi_connect();
void wifi_detect_change();
void wifi_state_update();

void wifi_Gstate_appl();
void wifi_Dstate_appl();
void wifi_Dstate_send(String Dstate);

//****************************************Timer SETUP**************************************************
SimpleTimer WifiTimer; 

int WifiTimer_ID;

#endif