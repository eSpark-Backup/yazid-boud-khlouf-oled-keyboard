/*
   Modifier keys mapping

   Left shift key => row3, input8
   Right shift key => row4, input11
*/


#include "TI_TCA9548A.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Keyboard.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


#define BLANK 0x00
#define SQUARE_KEY 0x02
#define CUBE_KEY 0x03
#define TRANSFORM 0x04
#define FN_KEY 0x05

#define KEY_RETURN 10
#define KEY_SCREEN_RECORD 11
#define KEY_SCREENSHOT 12
#define KEY_PRINT 13
#define KEY_SHARE 14

#define INPUT1 PD0
#define INPUT2 PD1
#define INPUT3 PD2
#define INPUT4 PD3
#define INPUT5 PD4
#define INPUT6 PA2
#define INPUT7 PD6
#define INPUT8 PA1
#define INPUT9 PC1
#define INPUT10 PC2
#define INPUT11 PC3
#define INPUT12 PC4
#define INPUT13 PC5
#define INPUT14 PC6
#define INPUT15 PC7
#define INPUT16 PC8

#define OUTPUT1 PB0
#define OUTPUT2 PB1
#define OUTPUT3 PB2
#define OUTPUT4 PB3
#define OUTPUT5 PB4

#define KEY_DELAY 100
#define REPEAT_DELAY 30
#define REPEAT_DELAY_INITIAL 500

#define HID_DEC_BRIGHTNESS_MEDIA 20
#define HID_INC_BRIGHTNESS_MEDIA 21
#define HID_MEDIA_VOL_DOWN_MEDIA 22
#define HID_MEDIA_VOL_UP_MEDIA 23
#define HID_MIC_MEDIA 24
#define HID_CAMERA_MEDIA 25
#define HID_RADIO_WIRELESS_MEDIA 26

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

uint8_t keys[]  = {KEY_ESC, KEY_RETURN, HID_DEC_BRIGHTNESS_MEDIA, HID_INC_BRIGHTNESS_MEDIA, HID_MEDIA_VOL_DOWN_MEDIA, HID_MEDIA_VOL_UP_MEDIA, HID_MIC_MEDIA, HID_CAMERA_MEDIA, KEY_SCREEN_RECORD, KEY_SCREENSHOT, KEY_PRINT, KEY_SHARE, HID_RADIO_WIRELESS_MEDIA, KEY_DELETE,
                   SQUARE_KEY, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', BLANK, BLANK, KEY_BACKSPACE,
                   KEY_TAB, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', BLANK, BLANK, KEY_RETURN,
                   TRANSFORM, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', BLANK, BLANK,
                   KEY_LEFT_SHIFT, 'w', 'x', 'c', 'v', 'b', 'n', ',' , ';', ':', '.', KEY_RIGHT_SHIFT,
                   KEY_LEFT_CTRL, FN_KEY, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW,
                   KEY_DOWN_ARROW
                  };

uint32_t output_pins[] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, OUTPUT5};
char key_selected = NULL;
char last_key_selected = NULL;
uint16_t repeat_delay = 0;
uint8_t repeat_first = false;
uint8_t shift_key_right = false;
uint8_t shift_key_left = false;
uint8_t ctrl_key_right = false;
uint8_t ctrl_key_left = false;
uint8_t alt_key_right = false;
uint8_t alt_key_left = false;
uint8_t fn_key = false;
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

  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);
  pinMode(OUTPUT5, OUTPUT);

  for (int i = 0; i < 8; i++)
  {
    initDisplay(&i2c_mux1, &display , i);
    initDisplay(&i2c_mux2, &display2 , i);
  }

  //  for (int i = 24; i < 30; i++)
  //  {
  //    initDisplay(&i2c_mux4, &display4 , i);
  //  }

  Keyboard.begin();

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
  if (shift_key_left || capslock_key)
  {
    if (!capitalized)
    {
      capitalized = true;
      uncapitalized = false;
      capitalize();
    }
  } else
  {
    if (!uncapitalized)
    {
      uncapitalized = true;
      capitalized = false;
      uncapitalize();
    }
  }

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
    displayScreen(&i2c_mux2, &display2 , i, screens);
  }

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

  for (int i = 8; i < 16; i++)
  {
    displayScreen(&i2c_mux2, &display2 , i, screens2);
  }
  //
  //  for (int i = 16; i < 24; i++)
  //  {
  //    displayScreen(&i2c_mux3, &display3 , i, screens2);
  //  }
}

void checkKeys()
{

  // right shift key
  //  if (digitalRead(INPUT13) == HIGH)
  //  {
  //    shift_key_right = true;
  //    Keyboard.press(KEY_RIGHT_SHIFT);
  //  }
  //  else if ((digitalRead(INPUT13) == LOW))
  //  {
  //    shift_key_right = false;
  //    Keyboard.release(KEY_RIGHT_SHIFT);
  //  }


  // Other than modifier keys
  for (int output = 0; output < 5; output++)
  {
    // Delay for scan voltage to settle
    delay(5);

    digitalWrite(output_pins[0], output == 0);
    digitalWrite(output_pins[1], output == 1);
    digitalWrite(output_pins[2], output == 2);
    digitalWrite(output_pins[3], output == 3);
    digitalWrite(output_pins[4], output == 4);

    if (output == 0)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               (digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT3) << 13) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT6) << 10) |
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT9) <<  7) |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT12) << 4) |
               (digitalRead(INPUT13) << 3) |
               (digitalRead(INPUT14) << 2) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          key_selected = keys[i + 16 * output];
          //          Serial.println("key pressed");
          //          Serial.println(i + 16 * output);
        }
      }

    }

    if (output == 1)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               (digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT3) << 13) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT6) << 10) |
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT9) <<  7) |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT12) << 4) |
               (digitalRead(INPUT13) << 3) |
               (digitalRead(INPUT14) << 2) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          key_selected = keys[i + 16 * output];
          //          Serial.println("key pressed");
          //          Serial.println(i + 16 * output);
        }
      }

    }

    if (output == 2)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               (digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT3) << 13) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT6) << 10) |
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT9) <<  7) |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT12) << 4) |
               (digitalRead(INPUT13) << 3) |
               (digitalRead(INPUT14) << 2) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          key_selected = keys[i + 16 * output];
          //          Serial.println("key pressed");
          //          Serial.println(i + 16 * output);
        }
      }

    }

    if (output == 3)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               (digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT3) << 13) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT6) << 10) |
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT12) << 4) |
               (digitalRead(INPUT13) << 3) |
               (digitalRead(INPUT14) << 2) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          key_selected = keys[i + 16 * output];
          //          Serial.println("key pressed");
          //          Serial.println(i + 16 * output);
        }
      }

      if (digitalRead(INPUT9) == HIGH)
      {
        shift_key_right = true;
        Keyboard.press(KEY_LEFT_SHIFT);
      }
      else if ((digitalRead(INPUT9) == LOW))
      {
        shift_key_right = false;
        Keyboard.release(KEY_LEFT_SHIFT);
      }

    }

    if (output == 4)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               (digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT3) << 13) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT6) << 10) |
               (digitalRead(INPUT9) <<  7) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          key_selected = keys[i + 16 * output];
          //          Serial.println("key pressed");
          //          Serial.println(i + 16 * output);
        }
      }

      // Press and release responses

      // Right Shift key
      if (digitalRead(INPUT14) == HIGH)
      {
        shift_key_right = true;
        Keyboard.press(KEY_RIGHT_SHIFT);
      }
      else if ((digitalRead(INPUT14) == LOW))
      {
        shift_key_right = false;
        Keyboard.release(KEY_RIGHT_SHIFT);
      }

      // Left Ctrl
      if (digitalRead(INPUT13) == HIGH)
      {
        ctrl_key_left = true;
        Keyboard.press(KEY_LEFT_CTRL);
      }
      else if ((digitalRead(INPUT13) == LOW))
      {
        ctrl_key_left = false;
        Keyboard.release(KEY_LEFT_CTRL);
      }

      // fn key
      if (digitalRead(INPUT12) == HIGH)
      {
        fn_key = true;
      }
      else if ((digitalRead(INPUT12) == LOW))
      {
        fn_key = false;
      }

      // Left Alt
      if (digitalRead(INPUT10) == HIGH)
      {
        alt_key_left = true;
        Keyboard.press(KEY_LEFT_ALT);
      }
      else if ((digitalRead(INPUT10) == LOW))
      {
        alt_key_left = false;
        Keyboard.release(KEY_LEFT_ALT);
      }

      // Right Alt
      if (digitalRead(INPUT8) == HIGH)
      {
        alt_key_right = true;
        Keyboard.press(KEY_RIGHT_ALT);
      }
      else if ((digitalRead(INPUT8) == LOW))
      {
        alt_key_right = false;
        Keyboard.release(KEY_RIGHT_ALT);
      }

      // Right Ctrl
      if (digitalRead(INPUT7) == HIGH)
      {
        ctrl_key_right = true;
        Keyboard.press(KEY_RIGHT_CTRL);
      }
      else if ((digitalRead(INPUT7) == LOW))
      {
        ctrl_key_right = false;
        Keyboard.release(KEY_RIGHT_CTRL);
      }

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


  if (key_selected != NULL)
  {

    // Key delay except for modifier keys
    if ((!shift_key_right) && (!shift_key_left) && (!ctrl_key_left) && (!ctrl_key_right)  /
        (!alt_key_left) && (!alt_key_right))
    {
      delay(repeat_delay);
    }


    //    Serial.println("hello");
    //    Serial.println(key_selected);
    print_key(key_selected);

    key_selected = NULL;
  }
}

void print_key(uint32_t key)
{
  uint8_t last_num_lock_state = Keyboard.check_numlock();

  switch (key)
  {

    // Row 1
    case KEY_ESC:
      Keyboard.write(KEY_ESC);
      break;

    case KEY_RETURN:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      Keyboard.releaseAll();
      break;

    case HID_DEC_BRIGHTNESS_MEDIA:
      Keyboard.writeConsumer(HID_DEC_BRIGHTNESS);
      break;

    case HID_INC_BRIGHTNESS_MEDIA:
      Keyboard.writeConsumer(HID_INC_BRIGHTNESS);
      break;

    case HID_MEDIA_VOL_DOWN_MEDIA:
      Keyboard.writeConsumer(HID_MEDIA_VOL_DOWN);
      break;

    case HID_MEDIA_VOL_UP_MEDIA:
      Keyboard.writeConsumer(HID_MEDIA_VOL_UP);
      break;

    case HID_MIC_MEDIA:
      // Mute mic not working
      Keyboard.writeConsumer(HID_MIC);
      break;

    case HID_CAMERA_MEDIA:
      Keyboard.writeConsumer(HID_CAMERA);
      break;

    case KEY_SCREEN_RECORD:
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('r');
      Keyboard.releaseAll();
      break;

    case KEY_SCREENSHOT:
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      Keyboard.releaseAll();
      break;

    case KEY_PRINT:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('p');
      Keyboard.releaseAll();
      break;

    case KEY_SHARE:
      // To be decided
      break;

    case HID_RADIO_WIRELESS_MEDIA:
      Keyboard.writeWireless(HID_RADIO_WIRELESS);
      break;

    case KEY_DELETE:
      Keyboard.write(KEY_DELETE);
      break;

    // Row 2
    case SQUARE_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // Row 3
    // Printing Keys are printed in default block

    // Row 4
    // Printing Keys are printed in default block

    // Row 5
    // Skipping left shift key, implemented in matrix keypad code to implement release key
    // Printing Keys are printed in default block

    // Row 6
    // Printing Keys are printed in default block

    // Row 7
    // Down Arrow key

    default:
      Keyboard.write(key_selected);
      break;

  }

}
