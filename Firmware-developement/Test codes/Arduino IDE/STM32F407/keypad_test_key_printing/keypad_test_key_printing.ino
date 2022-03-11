#include "Keyboard.h"

#define INPUT1 PD9
#define INPUT2 PD10
#define INPUT3 PD11
#define INPUT4 PD12

#define OUTPUT1 PB4
#define OUTPUT2 PB5
#define OUTPUT3 PB6
#define OUTPUT4 PB7

uint32_t output_pins[] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4};

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

        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        Keyboard.write('1');
      }

      if (digitalRead(INPUT2) == 1)
      {

        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        Keyboard.write('2');


      }

      if (digitalRead(INPUT3) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        Keyboard.write('3');

      }

      if (digitalRead(INPUT4) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        Keyboard.write('4');

      }

      continue;
    }

    if (output == 1)
    {

      if (digitalRead(INPUT1) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        Keyboard.write('A');

      }

      if (digitalRead(INPUT2) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        Keyboard.write('B');

      }

      if (digitalRead(INPUT3) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        Keyboard.write('C');

      }

      if (digitalRead(INPUT4) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        Keyboard.write('D');

      }

      continue;
    }

    if (output == 2)
    {

      if (digitalRead(INPUT1) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        Keyboard.write('E');

      }

      if (digitalRead(INPUT2) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        Keyboard.write('F');

      }

      if (digitalRead(INPUT3) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));

        Keyboard.write('G');

      }

      if (digitalRead(INPUT4) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        Keyboard.write('H');

      }

      continue;
    }

    if (output == 3)
    {

      if (digitalRead(INPUT1) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(1 + (output * 4));

        Keyboard.write('I');

      }

      if (digitalRead(INPUT2) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(2 + (output * 4));

        Keyboard.write('J');
      }

      if (digitalRead(INPUT3) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(3 + (output * 4));
        Keyboard.write('K');

      }

      if (digitalRead(INPUT4) == 1)
      {
        delay(50);

        //        Serial.print("Button pressed: ");
        //        Serial.println(4 + (output * 4));

        Keyboard.write('L');

      }

      continue;

    }

  }

}
