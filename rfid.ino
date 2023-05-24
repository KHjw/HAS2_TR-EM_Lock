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