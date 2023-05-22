void TimerInit(){
  WifiTimer_ID = WifiTimer.setInterval(1000, wifi_state_update);
}