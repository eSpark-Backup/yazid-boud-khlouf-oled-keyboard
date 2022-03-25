#include "TI_TCA9548A.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
//#include "Keyboard.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define CONSUMER_KEY 0x00
#define BLANK 0x00
#define SQUARE_KEY 0x02
#define CUBE_KEY 0x03
#define TRANSFORM 0x04
#define FN_KEY 0x05

#define INPUT1 PA0
#define INPUT2 PA1
#define INPUT3 PA2
#define INPUT4 PA3
#define INPUT5 PA5
#define INPUT6 PB0
#define INPUT7 PB1
#define INPUT8 PE8
#define INPUT9 PB3
#define INPUT10 PB4
#define INPUT11 PC5
#define INPUT12 PC1
#define INPUT13 PE7
#define INPUT14 PC3
#define INPUT15 PC4
#define INPUT16 PD0
#define INPUT17 PD1

#define OUTPUT1 PE0
#define OUTPUT2 PE1
#define OUTPUT3 PE2
#define OUTPUT4 PE3
#define OUTPUT5 PE4

#define KEY_DELAY 100
#define REPEAT_DELAY 30
#define REPEAT_DELAY_INITIAL 500

TwoWire WireDisplay1(PB9, PB8);
TwoWire WireDisplay2(PB11, PB10);
TwoWire WireDisplay3(PC9, PA8);

TI_TCA9548A i2c_mux1(&WireDisplay1);
TI_TCA9548A i2c_mux2(&WireDisplay2);
TI_TCA9548A i2c_mux3(&WireDisplay3);
TI_TCA9548A i2c_mux4(&WireDisplay1, 1);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay1, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay2, OLED_RESET);
Adafruit_SSD1306 display3(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay3, OLED_RESET);
Adafruit_SSD1306 display4(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay1, OLED_RESET);

char screens[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4'};
char screens2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4'};

//uint8_t keys[]  = {KEY_ESC, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, CONSUMER_KEY, KEY_DELETE,
//                   SQUARE_KEY, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', BLANK, BLANK, KEY_BACKSPACE,
//                   KEY_TAB, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', BLANK, BLANK, KEY_RETURN,
//                   TRANSFORM, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', BLANK, BLANK,
//                   KEY_LEFT_SHIFT, 'w', 'x', 'c', 'v', 'b', 'n', ',' , ';', ':', '.', KEY_RIGHT_SHIFT,
//                   KEY_LEFT_CTRL, FN_KEY, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW,
//                   KEY_DOWN_ARROW
//                  };

uint32_t output_pins[] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, OUTPUT5};
char key_selected = NULL;
char last_key_selected = NULL;
uint16_t repeat_delay = 0;
uint8_t repeat_first = false;
uint8_t shift_key = false;
uint8_t capslock_key = false;
uint8_t capitalized = false;
uint8_t uncapitalized = false;

uint32_t inputs = 0;

void setup()
// put your setup code here, to run once:
{
  WireDisplay1.begin();
  WireDisplay2.begin();
  WireDisplay3.begin();

  WireDisplay1.setClock(100000);
  WireDisplay2.setClock(100000);
  WireDisplay3.setClock(100000);

  pinMode(INPUT1, INPUT_PULLDOWN);
  pinMode(INPUT2, INPUT_PULLDOWN);
  pinMode(INPUT3, INPUT_PULLDOWN);
  pinMode(INPUT4, INPUT_PULLDOWN);
  pinMode(INPUT5, INPUT_PULLDOWN);
  pinMode(INPUT6, INPUT_PULLDOWN);
  pinMode(INPUT7, INPUT_PULLDOWN);
  pinMode(INPUT8, INPUT_PULLDOWN);
  pinMode(INPUT9, INPUT_PULLDOWN);
  pinMode(INPUT10, INPUT_PULLDOWN);
  pinMode(INPUT11, INPUT_PULLDOWN);
  pinMode(INPUT12, INPUT_PULLDOWN);
  pinMode(INPUT13, INPUT_PULLDOWN);
  pinMode(INPUT14, INPUT_PULLDOWN);
  pinMode(INPUT15, INPUT_PULLDOWN);
  pinMode(INPUT16, INPUT_PULLDOWN);
  pinMode(INPUT17, INPUT_PULLDOWN);

  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);
  pinMode(OUTPUT5, OUTPUT);

  //  for (int i = 0; i < 8; i++)
  //  {
  //    initDisplay(&i2c_mux1, &display , i);
  //    //    initDisplay(&i2c_mux2, &display2 , i);
  //    //    initDisplay(&i2c_mux3, &display3 , i);
  //  }

  //  for (int i = 24; i < 30; i++)
  //  {
  //    initDisplay(&i2c_mux4, &display4 , i);
  //  }

  //Keyboard.begin();

  //  capitalize();

}

void loop() {
  // put your main code here, to run repeatedly:

  //  Keyboard.write('A');

  //  if (digitalRead(PA0) == LOW)
  //  {
  //    if (!capitalized)
  //    {
  //      capitalized = true;
  //      uncapitalized = false;
  //
  //      capitalize();
  //    }
  //  } else
  //  {
  //    if (!uncapitalized)
  //    {
  //      uncapitalized = true;
  //      capitalized = false;
  //
  //      uncapitalize();
  //    }
  //  }

  //  capitalize();
  //  delay(2000);
  //
  //  uncapitalize();
  //  delay(2000);

  checkKeys();
  //
  //  if (shift_key || capslock_key)
  //  {
  //    if (!capitalized)
  //    {
  //      capitalized = true;
  //      uncapitalized = false;
  //      capitalize();
  //    }
  //  } else
  //  {
  //    if (!uncapitalized)
  //    {
  //      uncapitalized = true;
  //      capitalized = false;
  //      uncapitalize();
  //    }
  //  }

}

void initDisplay(TI_TCA9548A* i2c_mux, Adafruit_SSD1306* Display, int channel)
{

  if ((channel >= 8) && (channel < 16)) channel -= 8;
  if ((channel >= 16) && (channel < 24))channel -= 16;
  if ((channel >= 24) && (channel < 30))channel -= 24;
  i2c_mux->selectChannel(channel);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!Display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  Display->display();
}

void displayScreen(TI_TCA9548A* i2c_mux, Adafruit_SSD1306* Display, int channel, char* screen_local)
{
  int screen_number = channel;
  if ((channel >= 8) && (channel < 16)) channel -= 8;
  if ((channel >= 16) && (channel < 24))channel -= 16;
  if ((channel >= 24) && (channel < 30))channel -= 24;
  i2c_mux->selectChannel(channel);

  // Clear the buffer
  Display->clearDisplay();

  Display->setTextSize(4); // Draw 2X-scale text
  Display->setTextColor(SSD1306_WHITE);
  Display->setCursor(10, 20);
  Display->println(screen_local[screen_number]);

  Display->display();
}

void capitalize()
{
  //  i2c_mux1.setChannelMask(0);
  //
  //  for (int i = 24; i < 30; i++)
  //  {
  //    displayScreen(&i2c_mux4, &display4 , i, screens);
  //  }

  //  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    displayScreen(&i2c_mux1, &display , i, screens);
  }

  //  for (int i = 8; i < 16; i++)
  //  {
  //    displayScreen(&i2c_mux2, &display2 , i, screens);
  //  }
  //
  //  for (int i = 16; i < 24; i++)
  //  {
  //    displayScreen(&i2c_mux3, &display3 , i, screens);
  //  }
}

void uncapitalize()
{

  //  i2c_mux1.setChannelMask(0);
  //
  //  for (int i = 24; i < 30; i++)
  //  {
  //    displayScreen(&i2c_mux4, &display4 , i, screens2);
  //  }
  //
  //  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    displayScreen(&i2c_mux1, &display , i, screens2);
  }

  //  for (int i = 8; i < 16; i++)
  //  {
  //    displayScreen(&i2c_mux2, &display2 , i, screens2);
  //  }
  //
  //  for (int i = 16; i < 24; i++)
  //  {
  //    displayScreen(&i2c_mux3, &display3 , i, screens2);
  //  }
}

void checkKeys()
{
  for (int output = 0; output < 5; output++)
  {
    digitalWrite(output_pins[0], output == 0);
    digitalWrite(output_pins[1], output == 1);
    digitalWrite(output_pins[2], output == 2);
    digitalWrite(output_pins[3], output == 3);
    digitalWrite(output_pins[4], output == 4);

    if (output == 0)
    {

      inputs = (digitalRead(INPUT1) << 16) |
               (digitalRead(INPUT2) << 15) |
               (digitalRead(INPUT3) << 14) |
               (digitalRead(INPUT4) << 13) |
               (digitalRead(INPUT5) << 12) |
               (digitalRead(INPUT6) << 11) |
               (digitalRead(INPUT7) << 10) |
               (digitalRead(INPUT8) <<  9) |
               (digitalRead(INPUT9) <<  8) |
               (digitalRead(INPUT10) << 7) |
               (digitalRead(INPUT11) << 6) |
               (digitalRead(INPUT12) << 5) |
               (digitalRead(INPUT13) << 4) |
               (digitalRead(INPUT14) << 3) |
               (digitalRead(INPUT15) << 2) |
               (digitalRead(INPUT16) << 1) |
               (digitalRead(INPUT17) << 0);

      for (int i = 0; i < 17; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          //          key_selected = keys[i + output * i];
          Serial.println("key pressed");
          Serial.println(i + i * output);
        }
      }

      continue;
    }
    if (output == 1)
    {

      inputs = (digitalRead(INPUT1) << 16) |
               (digitalRead(INPUT2) << 15) |
               (digitalRead(INPUT3) << 14) |
               (digitalRead(INPUT4) << 13) |
               (digitalRead(INPUT5) << 12) |
               (digitalRead(INPUT6) << 11) |
               (digitalRead(INPUT7) << 10) |
               (digitalRead(INPUT8) <<  9) |
               (digitalRead(INPUT9) <<  8) |
               (digitalRead(INPUT10) << 7) |
               (digitalRead(INPUT11) << 6) |
               (digitalRead(INPUT12) << 5) |
               (digitalRead(INPUT13) << 4) |
               (digitalRead(INPUT14) << 3) |
               (digitalRead(INPUT15) << 2) |
               (digitalRead(INPUT16) << 1) |
               (digitalRead(INPUT17) << 0);

      for (int i = 0; i < 17; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          //          key_selected = keys[i + output * i];
          Serial.println("key pressed");
          Serial.println(i + i * output);
        }
      }

      continue;
    }

    if (output == 2)
    {

      inputs = (digitalRead(INPUT1) << 16) |
               (digitalRead(INPUT2) << 15) |
               (digitalRead(INPUT3) << 14) |
               (digitalRead(INPUT4) << 13) |
               (digitalRead(INPUT5) << 12) |
               (digitalRead(INPUT6) << 11) |
               (digitalRead(INPUT7) << 10) |
               (digitalRead(INPUT8) <<  9) |
               (digitalRead(INPUT9) <<  8) |
               (digitalRead(INPUT10) << 7) |
               (digitalRead(INPUT11) << 6) |
               (digitalRead(INPUT12) << 5) |
               (digitalRead(INPUT13) << 4) |
               (digitalRead(INPUT14) << 3) |
               (digitalRead(INPUT15) << 2) |
               (digitalRead(INPUT16) << 1) |
               (digitalRead(INPUT17) << 0);

      for (int i = 0; i < 17; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          //          key_selected = keys[i + output * i];
          Serial.println("key pressed");
          Serial.println(i + i * output);
        }
      }

      continue;
    }

    if (output == 3)
    {

      inputs = (digitalRead(INPUT1) << 16) |
               (digitalRead(INPUT2) << 15) |
               (digitalRead(INPUT3) << 14) |
               (digitalRead(INPUT4) << 13) |
               (digitalRead(INPUT5) << 12) |
               (digitalRead(INPUT6) << 11) |
               (digitalRead(INPUT7) << 10) |
               (digitalRead(INPUT8) <<  9) |
               (digitalRead(INPUT9) <<  8) |
               (digitalRead(INPUT10) << 7) |
               (digitalRead(INPUT11) << 6) |
               (digitalRead(INPUT12) << 5) |
               (digitalRead(INPUT13) << 4) |
               (digitalRead(INPUT14) << 3) |
               (digitalRead(INPUT15) << 2) |
               (digitalRead(INPUT16) << 1) |
               (digitalRead(INPUT17) << 0);

      for (int i = 0; i < 17; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          //          key_selected = keys[i + output * i];
          Serial.println("key pressed");
          Serial.println(i + i * output);
        }
      }

      continue;

    }

    if (output == 4)
    {

      inputs = (digitalRead(INPUT1) << 16) |
               (digitalRead(INPUT2) << 15) |
               (digitalRead(INPUT3) << 14) |
               (digitalRead(INPUT4) << 13) |
               (digitalRead(INPUT5) << 12) |
               (digitalRead(INPUT6) << 11) |
               (digitalRead(INPUT7) << 10) |
               (digitalRead(INPUT8) <<  9) |
               (digitalRead(INPUT9) <<  8) |
               (digitalRead(INPUT10) << 7) |
               (digitalRead(INPUT11) << 6) |
               (digitalRead(INPUT12) << 5) |
               (digitalRead(INPUT13) << 4) |
               (digitalRead(INPUT14) << 3) |
               (digitalRead(INPUT15) << 2) |
               (digitalRead(INPUT16) << 1) |
               (digitalRead(INPUT17) << 0);

      for (int i = 0; i < 17; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          //          key_selected = keys[i + output * i];
          Serial.println("key pressed");
          Serial.println(i + i * output);
        }
      }

      continue;

    }

  }

  //  if (last_key_selected == key_selected)
  //  {
  //    if (!repeat_first)
  //    {
  //      repeat_delay = REPEAT_DELAY_INITIAL;
  //      repeat_first = true;
  //    } else
  //    {
  //      repeat_delay = REPEAT_DELAY;
  //    }
  //  }
  //  else
  //  {
  //    repeat_first = false;
  //    repeat_delay = KEY_DELAY;
  //  }
  //
  //  last_key_selected = key_selected;
  //
  //  if (key_selected != -1)
  //  {
  //    if (!shift_key)
  //    {
  //      delay(repeat_delay);
  //    }
  //
  //    if (key_selected == SQUARE_KEY)
  //    {
  //      Keyboard.press(KEY_LEFT_ALT);
  //      Keyboard.write(NUM_0);
  //      Keyboard.write(NUM_1);
  //      Keyboard.write(NUM_7);
  //      Keyboard.write(NUM_8);
  //      Keyboard.release(KEY_LEFT_ALT);
  //    } else
  //    {
  //      Keyboard.write(key_selected);
  //    }
  //    key_selected = -1;
  //  }
}
