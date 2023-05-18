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