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
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
 
  if (success) {
    if (uidLength == 7)
    {
      uint8_t data[32];

      Serial.print("NTAG2xx tag Detected : ");     

      success = nfc.ntag2xx_ReadPage(7, data); 

      if (success) 
      {
        Rfid_Identify(data);
      }
    }
    else
    {
      Serial.println("This doesn't seem to be an NTAG203 tag");
    }
    Serial.flush();    
  }
  delay (50);
}

void Rfid_Identify(uint8_t data[32]){
  for(int i=0; i<4; i++){
    RfidID += (char)data[i];
  }

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

void RfidCheckLoop(){
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    if (uidLength == 7)
    {
      uint8_t data[32];
      success = nfc.ntag2xx_ReadPage(7, data); 
      if (success) 
      {
        Serial.print("NTAG2xx tag Detected");

        //
      }
    }
    else
    {
      Serial.println("This doesn't seem to be an NTAG203 tag");
    }
    Serial.flush();    
  }
  delay (50);
}