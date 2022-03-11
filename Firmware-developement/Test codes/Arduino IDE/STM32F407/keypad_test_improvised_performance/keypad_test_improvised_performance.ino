#include "Keyboard.h"

#define INPUT1 PD9
#define INPUT2 PD10
#define INPUT3 PD11
#define INPUT4 PD12

#define OUTPUT1 PB4
#define OUTPUT2 PB5
#define OUTPUT3 PB6
#define OUTPUT4 PB7

#define KEY_DELAY 100
#define REPEAT_DELAY 30
#define REPEAT_DELAY_INITIAL 500

uint32_t output_pins[] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4};
char key_selected = NULL;
char last_key_selected = NULL;
uint16_t repeat_delay = 0;
uint8_t repeat_first = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT1, INPUT_PULLDOWN);
  pinMode(INPUT2, INPUT_PULLDOWN);
  pinMode(INPUT3, INPUT_PULLDOWN);
  pinMode(INPUT4, INPUT_PULLDOWN);

  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);


  Serial.begin(115200);

  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int output = 0; output < 4; output++)
  {
    digitalWrite(output_pins[0], output == 0);
    digitalWrite(output_pins[1], output == 1);
    digitalWrite(output_pins[2], output == 2);
    digitalWrite(output_pins[3], output == 3);

    if (output == 0)
    {

      if (digitalRead(INPUT1) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        key_selected = '1';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT2) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        key_selected = '2';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT3) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        key_selected = '3';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT4) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        key_selected = '4';
        //        Keyboard.write(key_selected);

      }

      continue;
    }

    if (output == 1)
    {

      if (digitalRead(INPUT1) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        key_selected = 'A';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT2) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        key_selected = 'B';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT3) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        key_selected = 'C';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT4) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        key_selected = 'D';
        //        Keyboard.write(key_selected);

      }

      continue;
    }

    if (output == 2)
    {

      if (digitalRead(INPUT1) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        key_selected = 'E';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT2) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        key_selected = 'F';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT3) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        key_selected = 'G';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT4) == 1)
      {
        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        key_selected = 'H';
        //        Keyboard.write(key_selected);

      }

      continue;
    }

    if (output == 3)
    {

      if (digitalRead(INPUT1) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        key_selected = 'I';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT2) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        key_selected = 'J';
        //        Keyboard.write(key_selected);
      }

      if (digitalRead(INPUT3) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));
        key_selected = 'K';
        //        Keyboard.write(key_selected);

      }

      if (digitalRead(INPUT4) == 1)
      {

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        key_selected = 'L';
        //        Keyboard.write(key_selected);

      }

      continue;

    }

  }

  if (last_key_selected == key_selected)
  {
    if (!repeat_first)
    {
      repeat_delay = REPEAT_DELAY_INITIAL;
      repeat_first = true;
    } else
    {
      repeat_delay = REPEAT_DELAY;
    }
  }
  else
  {
    repeat_first = false;
    repeat_delay = KEY_DELAY;
  }

  last_key_selected = key_selected;

  if (key_selected != -1)
  {
    delay(repeat_delay);
    
    Keyboard.write(key_selected);
    key_selected = -1;
  }

}
