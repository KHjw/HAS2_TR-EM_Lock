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

void setup(void) {
  Serial.begin(115200);
  em_init();
}

void loop(void) {
  game_ptr();
}
