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
#line 24 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
void loop(void);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_init();
#line 5 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_control(int state);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_open();
#line 13 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_lock();
#line 25 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_setting();
#line 32 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_ready();
#line 39 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_activate();
#line 46 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_void();
#line 49 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_Mopen();
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeopixelInit();
#line 6 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeoShowColor(int neo_code ,int color_code);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\rfid.ino"
void RfidInit();
#line 16 "c:\\Github\\HAS2_TR-EM_Lock\\rfid.ino"
void RfidLoop();
#line 31 "c:\\Github\\HAS2_TR-EM_Lock\\rfid.ino"
void Rfid_Identify(uint8_t data[32]);
#line 54 "c:\\Github\\HAS2_TR-EM_Lock\\rfid.ino"
void Rfid_PlayerData(uint8_t data[32]);
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\timer.ino"
void TimerInit();
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_connect();
#line 8 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_detect_change();
#line 13 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_state_update();
#line 18 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_Gstate_appl();
#line 37 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_Dstate_appl();
#line 70 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_Dstate_send(String Dstate);
#line 13 "c:\\Github\\HAS2_TR-EM_Lock\\HAS2_TR-EM_Lock.ino"
void setup(void) {
  Serial.begin(115200);
  Serial.println("=============================ESP SETUP=============================");
  wifi_connect();
  TimerInit();
  em_init();
  RfidInit();
  NeopixelInit();
  Serial.println("===================================================================");
}

void loop(void) {
  WifiTimer.run();
  game_ptr();
}

#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\emlock.ino"
void em_init(){
  pinMode(EM_MOSFET, OUTPUT);
}

void em_control(int state){             // 0 == LOCK, 1 == OPEN
  if(current_state != state){
    if(state == 0){
      digitalWrite(EM_MOSFET, LOW);
      NeoShowColor(EM_STATE, RED);
      Serial.println("EM LOCK [[[CLOSED]]]");
    }
    else if(state == 1){
      digitalWrite(EM_MOSFET, HIGH);
      NeoShowColor(EM_STATE, GREEN);
      Serial.println("EM LOCK [[[OPEN]]]");
    }
    current_state = state;
  }
}
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\game.ino"
void device_open(){
  if(current_Dstate != "open"){
    wifi_Dstate_send("open");
    current_Dstate = "open";
    Serial.println("STATE :: Device Open");
    em_control(1);
    delay(500);
  }
  Serial.println("RFID Detecting");
  game_ptr = RfidLoop;
}

void device_lock(){
  if(current_Dstate != "lock"){
    wifi_Dstate_send("lock");
    current_Dstate = "lock";
    Serial.println("STATE :: Device Locked");
    em_control(0);
    delay(500);
  }
  Serial.println("RFID Detecting");
  game_ptr = RfidLoop;
}

void device_setting(){
  Serial.println("STATE :: Device Set");
  em_control(1);
  NeoShowColor(INDICATOR, WHITE);
  game_ptr = device_void;
}

void device_ready(){
  Serial.println("STATE :: Device Ready");
  em_control(1);
  NeoShowColor(INDICATOR, RED);
  game_ptr = device_void;
}

void device_activate(){
  Serial.println("STATE :: Device Activate");
  em_control(0);
  NeoShowColor(INDICATOR, YELLOW);
  game_ptr = RfidLoop;
}

void device_void(){
}

void device_Mopen(){
  if(current_Dstate != "open"){
    wifi_Dstate_send("open");
    current_Dstate = "open";
    Serial.println("STATE :: Device Open");
    em_control(1);
    delay(500);
  }
  Serial.println("RFID Detecting");
  game_ptr = RfidLoop;
}


#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\neopixel.ino"
void NeopixelInit(){
  indicator_neo.begin();
  em_state_neo.begin();
}

void NeoShowColor(int neo_code ,int color_code){
  if(neo_code == INDICATOR){
    for(int i=0; i<INDICATOR_NEONUM; i++){
      indicator_neo.setPixelColor(i, 0, 0, 0);
    }
    for(int i=0; i<INDICATOR_NEONUM; i++){
      indicator_neo.lightColor(color[color_code]);
    }
  }
  else if(neo_code == EM_STATE){
    for(int i=0; i<EM_STATE_NEONUM; i++){
      em_state_neo.setPixelColor(i, 0, 0, 0);
    }
    for(int i=0; i<EM_STATE_NEONUM; i++){
      em_state_neo.lightColor(color[color_code]);
    }
  }
  indicator_neo.show();
  em_state_neo.show();
}
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\rfid.ino"
void RfidInit(){
  Serial.println("------------Rfid Initialized------------");
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();

  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  Serial.println("Found PN532");              // Got ok data, print it out!
  nfc.SAMConfig();                            // configure board to read RFID tags
  Serial.println("Waiting for Card ...");
}

void RfidLoop(){
  Serial.println("RFID Loop");
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t data[32];

  if(nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A)){
    if (nfc.ntag2xx_ReadPage(7, data)) {
      Rfid_PlayerData(data);
      // Rfid_Identify(data);
    }
  }
  Serial.flush();    
  delay (50);
}

void Rfid_Identify(uint8_t data[32]){
  for(int i=0; i<4; i++){
    RfidID += (char)data[i];
  }
  Serial.print("Player tag Detected : ");
  if(RfidID == "G1P7")
  {
    Serial.println("G1P7");
    game_ptr = device_lock;
  }
  else if(RfidID == "G1P9")
  {
    Serial.println("G1P9");
    game_ptr = device_open;
  }
  else{
    Serial.print("Unidentified Chip :: ");
    Serial.println(RfidID);
    // game_ptr = RfidLoop;
  }
  RfidID = "";
}

void Rfid_PlayerData(uint8_t data[32]){
  for(int i=0; i<4; i++){
    RfidID += (char)data[i];
  }
  if(RfidID == "MMMM"){
    Serial.println("Master Card Detected");
    game_ptr = device_open;
  }

  Serial.println("Player tag Detected : " + RfidID);
  HAS2wifi.Receive(RfidID);  
  if((String)(const char*)tag["role"] == "player"){
    Serial.println("Role :: Player");
    NeoShowColor(INDICATOR, GREEN);
    game_ptr = device_lock;
  }
  else if((String)(const char*)tag["role"] == "tagger"){
    Serial.println("Role :: Tagger");
    NeoShowColor(INDICATOR, PURPLE);
    game_ptr = device_open;
  }
  else if((String)(const char*)tag["role"] == "ghost"){
    Serial.println("Role :: Ghost");
    NeoShowColor(INDICATOR, BLUE);
    game_ptr = device_open;
  }
  else{
    Serial.println("Unidentified Chip");
  }

  RfidID = "";
}
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\timer.ino"
void TimerInit(){
  WifiTimer_ID = WifiTimer.setInterval(1000, wifi_detect_change);
}
#line 1 "c:\\Github\\HAS2_TR-EM_Lock\\wifi.ino"
void wifi_connect(){
  HAS2wifi.Setup("KT_GiGA_6C64", "ed46zx1198");
  // HAS2wifi.Setup("city");
  // HAS2wifi.ReceiveMine();
  wifi_state_update();
}

void wifi_detect_change(){
  Serial.println("----Timer----");
  HAS2wifi.Loop(wifi_state_update);
}

void wifi_state_update(){
  wifi_Gstate_appl();
  wifi_Dstate_appl();
}

void wifi_Gstate_appl(){
  if((String)(const char*)my["game_state"] != current_Gstate){
    Serial.print("Game State :: ");
    if((String)(const char*)my["game_state"] == "setting"){
      Serial.println("Setting");
      game_ptr = device_setting;
    }
    else if((String)(const char*)my["game_state"] == "ready"){
      Serial.println("Ready");
      game_ptr = device_ready;
    }
    else if((String)(const char*)my["game_state"] == "activate"){
      Serial.println("Activate");
      game_ptr = device_activate;
    }
    current_Gstate = (String)(const char*)my["game_state"];
  }
}

void wifi_Dstate_appl(){
  if((String)(const char*)my["device_state"] != current_Dstate){
    Serial.print("Device State :: ");
    if((String)(const char*)my["device_state"] == "setting"){
      Serial.println("Setting");
      game_ptr = device_setting;
    }
    else if((String)(const char*)my["device_state"] == "ready"){
      Serial.println("Ready");
      game_ptr = device_ready;
    }
    else if((String)(const char*)my["device_state"] == "activate"){
      Serial.println("Activate");
      game_ptr = device_activate;
    }
    else if((String)(const char*)my["device_state"] == "open"){
      Serial.println("Open");
      game_ptr = device_open;
    }
    else if((String)(const char*)my["device_state"] == "lock"){
      Serial.println("Lock");
      game_ptr = device_lock;
    }
    else if((String)(const char*)my["device_state"] == "player_win"){
      
    }
    else if((String)(const char*)my["device_state"] == "player_lose"){
      
    }
    current_Dstate = (String)(const char*)my["device_state"];
  }
}

void wifi_Dstate_send(String Dstate){
  HAS2wifi.Send("BD", "device_state", Dstate);
}
