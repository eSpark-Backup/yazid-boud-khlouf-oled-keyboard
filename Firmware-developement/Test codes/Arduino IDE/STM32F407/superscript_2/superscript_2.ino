#include "Keyboard.h"

uint8_t last_num_lock_state = false;

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
  pinMode(PD14, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  last_num_lock_state = Keyboard.check_numlock();

  if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.write(NUM_0);
  Keyboard.write(NUM_1);
  Keyboard.write(NUM_7);
  Keyboard.write(NUM_8);
  Keyboard.release(KEY_LEFT_ALT);

  if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

  delay(1000);

}
