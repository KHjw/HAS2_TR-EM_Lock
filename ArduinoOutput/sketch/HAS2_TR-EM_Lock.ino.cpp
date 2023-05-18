#include <Arduino.h>
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
 /*
 * @file HAS2_TR-EM_Lock.ino
 * @author 홍진우 KH.jinu (kevinlike@naver.com)
 * @brief
 * @version 1.0
 * @date 2023-05-18
 *
 * @copyright Copyright (c) 2023
 */

#include "EM_Lock.h"

#line 13 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
void setup(void);
#line 18 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
void loop(void);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_init();
#line 5 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_control(int state);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_init();
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeopixelInit();
#line 6 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeoShowColor(int color_code);
#line 13 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
void setup(void) {
  Serial.begin(115200);
  em_init();
}

void loop(void) {
  game_ptr();
}

#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_init(){
  pinMode(EM_MOSFET, OUTPUT);
}

void em_control(int state){             // 0 == LOCK, 1 == OPEN
  if(state == 0){
    digitalWrite(EM_MOSFET, LOW);
    NeoShowColor(RED);
    Serial.println("EM LOCK [[[CLOSED]]]");
  }
  else if(state == 1){
    digitalWrite(EM_MOSFET, HIGH);
    NeoShowColor(GREEN);
    Serial.println("EM LOCK [[[OPEN]]]");
  }
}
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_init(){
  Serial.println("Device Initialized");
  em_control(0);

}

// void device_activate(){

// }

// void device_activate(){

// }
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeopixelInit(){
  indicator_neo.begin();
  em_state_neo.begin();
}

void NeoShowColor(int color_code){
  for(int i=0; i<INDICATOR_NEONUM; i++){
    indicator_neo.setPixelColor(i, 0, 0, 0);
  }
  for(int i=0; i<INDICATOR_NEONUM; i++){
    indicator_neo.lightColor(color[color_code]);
  }
  indicator_neo.show();
}
