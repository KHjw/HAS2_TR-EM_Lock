#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\EM_Lock.h"
#ifndef _DONE_EMLOCK_CODE_
#define _DONE_EMLOCK_CODE_

#include "Library_and_pin.h"

//****************************************Rfid SETUP****************************************
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

void RfidInit();
void RfidLoop();
void Rfid_Identify();
void RfidCheckLoop();

String RfidID = "";


//****************************************Neopixel SETUP**************************************************
void NeopixelInit();
void NeoShowColor(int color_code);

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


//****************************************Game System SETUP**************************************************
void device_init();

void (*game_ptr)() = &device_init;



#endif