#include "Keyboard.h"

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.write(NUM_0);
  Keyboard.write(NUM_1);
  Keyboard.write(NUM_7);
  Keyboard.write(NUM_8);
  Keyboard.release(KEY_LEFT_ALT);

  delay(1000);

}
