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