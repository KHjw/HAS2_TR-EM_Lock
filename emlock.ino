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