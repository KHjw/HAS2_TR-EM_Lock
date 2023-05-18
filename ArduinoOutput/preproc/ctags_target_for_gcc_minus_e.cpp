# 1 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
 /*

 * @file HAS2_TR-EM_Lock.ino

 * @author 홍진우 KH.jinu (kevinlike@naver.com)

 * @brief

 * @version 1.0

 * @date 2023-05-18

 *

 * @copyright Copyright (c) 2023

 */
# 11 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
# 12 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino" 2

void setup(void) {
  Serial.begin(115200);
  em_init();
}

void loop(void) {
  game_ptr();
}
# 1 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_init(){
  pinMode(33, 0x03);
}

void em_control(int state){ // 0 == LOCK, 1 == OPEN
  if(state == 0){
    digitalWrite(33, 0x0);
    NeoShowColor(RED);
    Serial.println("EM LOCK [[[CLOSED]]]");
  }
  else if(state == 1){
    digitalWrite(33, 0x1);
    NeoShowColor(GREEN);
    Serial.println("EM LOCK [[[OPEN]]]");
  }
}
# 1 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_init(){
  Serial.println("Device Initialized");
  em_control(0);

}

// void device_activate(){

// }

// void device_activate(){

// }
# 1 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeopixelInit(){
  indicator_neo.begin();
  em_state_neo.begin();
}

void NeoShowColor(int color_code){
  for(int i=0; i<10 /* INDICATOR 네오픽셀 갯수*/; i++){
    indicator_neo.setPixelColor(i, 0, 0, 0);
  }
  for(int i=0; i<10 /* INDICATOR 네오픽셀 갯수*/; i++){
    indicator_neo.lightColor(color[color_code]);
  }
  indicator_neo.show();
}
