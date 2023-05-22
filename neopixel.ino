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