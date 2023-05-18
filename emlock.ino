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