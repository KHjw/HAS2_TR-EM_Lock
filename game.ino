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

