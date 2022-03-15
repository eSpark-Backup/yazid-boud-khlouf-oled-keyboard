/*
   USB Composite device consisting of keyboard and consumer HID
   Extends the features of Keyboard library by adding
   multimedia keys support. Depends on MediaKeyboard library.

   A rotary encoder and four push buttons are required. See the schematic at
   https://www.onetransistor.eu/2020/03/usb-multimedia-keys-on-arduino-stm32.html

   RotaryEncoder library by Matthias Hertel is required for successful compilation.
   You can find it in Library Manager or at:
   http://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx

   USB HID support must be enabled from Tools menu.

   Copyright (C) 2020 One Transistor (https://www.onetransistor.eu).
*/

#include <MediaKeyboard.h>

void setup() {

  MediaKeyboard.begin();
}

void loop() {
  MediaKeyboard.press(0x6F);
  MediaKeyboard.release();

  delay(500);

  MediaKeyboard.press(0x6F);
  MediaKeyboard.release();

  delay(500);

  MediaKeyboard.press(0x70);
  MediaKeyboard.release();

  delay(500);

  MediaKeyboard.press(0x70);
  MediaKeyboard.release();

  delay(500);

}
