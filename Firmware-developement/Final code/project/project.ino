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
#define SQUARE_KEY 0x01
#define CUBE_KEY 0x02
#define TRANSFORM 0x03
#define FN_KEY 0x04
#define DEGREE_KEY 0x05
#define EURO_KEY 0x06
#define POUND_KEY 0x07
#define YEN_KEY 0x08
#define DIAERESIS_KEY 0x09

#define HID_DEC_BRIGHTNESS_MEDIA 0x0A
#define HID_INC_BRIGHTNESS_MEDIA 0x0B
#define HID_MEDIA_VOL_DOWN_MEDIA 0x0C
#define HID_MEDIA_VOL_UP_MEDIA 0x0D
#define HID_MIC_MEDIA 0x0E
#define HID_CAMERA_MEDIA 0x0F
#define HID_RADIO_WIRELESS_MEDIA 0x10
#define KEY_CANCEL 0x11
#define KEY_SCREEN_RECORD 0x12
#define KEY_SCREENSHOT 0x13
#define KEY_PRINT 0x14
#define KEY_SHARE 0x15

const uint16_t A_GRAVE = 0xA000;
const uint16_t A_ACUTE = 0xA100;
const uint16_t A_CIRC = 0xA200;
const uint16_t A_TILDE = 0xA300;
const uint16_t A_UML = 0xA400;
const uint16_t A_RING = 0xA500;
const uint16_t A_MACRON = 0xA600;
const uint16_t A_ELIG = 0xA700;

const uint16_t E_GRAVE = 0xB000;
const uint16_t E_ACUTE = 0xB100;
const uint16_t E_CIRC = 0xB200;
const uint16_t E_TILDE = 0xB300;
const uint16_t E_UML = 0xB400;
const uint16_t E_BREVE = 0xB500;
const uint16_t E_MACRON = 0xB600;
const uint16_t E_ELIG = 0xB700;
const uint16_t E_DOT = 0xB800;
const uint16_t E_OGON = 0xB900;
const uint16_t E_CARON = 0xBA00;

const uint16_t Y_UML = 0xC101;

const uint16_t U_GRAVE = 0xC000;
const uint16_t U_ACUTE = 0xC100;
const uint16_t U_CIRC = 0xC200;
const uint16_t U_TILDE = 0xC300;
const uint16_t U_UML = 0xC400;
const uint16_t U_BREVE = 0xC500;
const uint16_t U_MACRON = 0xC600;
const uint16_t U_ELIG = 0xC700;
const uint16_t U_DOT = 0xC800;
const uint16_t U_OGON = 0xC900;
const uint16_t U_CARON = 0xCA00;
const uint16_t U_DBLAC = 0xCB00;
const uint16_t U_RING = 0xCC00;

const uint16_t I_GRAVE = 0xD000;
const uint16_t I_ACUTE = 0xD100;
const uint16_t I_CIRC = 0xD200;
const uint16_t I_TILDE = 0xD300;
const uint16_t I_UML = 0xD400;
const uint16_t I_BREVE = 0xD500;
const uint16_t I_MACRON = 0xD600;
const uint16_t I_ELIG = 0xD700;
const uint16_t I_DOT = 0xD800;
const uint16_t I_OGON = 0xD900;
const uint16_t I_CARON = 0xDA00;
const uint16_t I_DBLAC = 0xDB00;
const uint16_t I_RING = 0xDC00;

const uint16_t C_GRAVE = 0xE000;
const uint16_t C_ACUTE = 0xE100;
const uint16_t C_CIRC = 0xE200;
const uint16_t C_TILDE = 0xE300;
const uint16_t C_UML = 0xE400;
const uint16_t C_BREVE = 0xE500;
const uint16_t C_MACRON = 0xE600;
const uint16_t C_ELIG = 0xE700;
const uint16_t C_DOT = 0xE800;
const uint16_t C_OGON = 0xE900;
const uint16_t C_CARON = 0xEA00;
const uint16_t C_DBLAC = 0xEB00;
const uint16_t C_RING = 0xEC00;

const uint16_t O_GRAVE = 0xF000;
const uint16_t O_ACUTE = 0xF100;
const uint16_t O_CIRC = 0xF200;
const uint16_t O_TILDE = 0xF300;
const uint16_t O_UML = 0xF400;
const uint16_t O_BREVE = 0xF500;
const uint16_t O_MACRON = 0xF600;
const uint16_t O_ELIG = 0xF700;
const uint16_t O_DOT = 0xF800;
const uint16_t O_OGON = 0xF900;
const uint16_t O_CARON = 0xFA00;
const uint16_t O_DBLAC = 0xFB00;
const uint16_t O_RING = 0xFC00;

const uint16_t N_GRAVE = 0x1000;
const uint16_t N_ACUTE = 0x1100;
const uint16_t N_CIRC = 0x1200;
const uint16_t N_TILDE = 0x1300;
const uint16_t N_UML = 0x1400;
const uint16_t N_BREVE = 0x1500;
const uint16_t N_MACRON = 0x1600;
const uint16_t N_ELIG = 0x1700;
const uint16_t N_DOT = 0x1800;
const uint16_t N_OGON = 0x1900;
const uint16_t N_CARON = 0x1A00;
const uint16_t N_DBLAC = 0x1B00;
const uint16_t N_RING = 0x1C00;

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

#define TEST_LED PD13
#define TEST_LED2 PD14

#define KEY_DELAY 100
#define REPEAT_DELAY 30
#define REPEAT_DELAY_INITIAL 500

TwoWire WireDisplay1(PB9, PB8);
//TwoWire WireDisplay2(PB11, PB10);
//TwoWire WireDisplay3(PC9, PA8);

TI_TCA9548A i2c_mux1(&WireDisplay1);
//TI_TCA9548A i2c_mux2(&WireDisplay2);
//TI_TCA9548A i2c_mux3(&WireDisplay3);
TI_TCA9548A i2c_mux4(&WireDisplay1, 1);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay1, OLED_RESET);
//Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay2, OLED_RESET);
//Adafruit_SSD1306 display3(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay3, OLED_RESET);
Adafruit_SSD1306 display4(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay1, OLED_RESET);

char screens[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4'};
char screens2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4'};
char special_screens[] = {'\'', '\"', '(', ')', '{', '}', '[', ']', '<', '>', '+', '-', '&', '#', '@', '€', '$', '£', '¥', '¨', '^', '*', '/',  '~', '\\', '|', '-', '_', ';', ':', ',', '.', '?', '!'};

uint16_t keys[]  = {KEY_ESC, KEY_CANCEL, HID_DEC_BRIGHTNESS_MEDIA, HID_INC_BRIGHTNESS_MEDIA, HID_MEDIA_VOL_DOWN_MEDIA, HID_MEDIA_VOL_UP_MEDIA, HID_MIC_MEDIA, HID_CAMERA_MEDIA, KEY_SCREEN_RECORD, KEY_SCREENSHOT, KEY_PRINT, KEY_SHARE, HID_RADIO_WIRELESS_MEDIA, KEY_DELETE,
                    SQUARE_KEY, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', BLANK, BLANK, KEY_BACKSPACE,
                    KEY_TAB, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', BLANK, BLANK, KEY_RETURN,
                    TRANSFORM, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', BLANK, BLANK,
                    KEY_LEFT_SHIFT, 'w', 'x', 'c', 'v', 'b', 'n', ',' , ';', ':', '.', KEY_RIGHT_SHIFT,
                    KEY_LEFT_CTRL, FN_KEY, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW,
                    KEY_DOWN_ARROW
                   };

uint8_t function_keys[] = {KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12};

uint8_t special_keys[]  = {KEY_ESC, KEY_CANCEL, HID_DEC_BRIGHTNESS_MEDIA, HID_INC_BRIGHTNESS_MEDIA, HID_MEDIA_VOL_DOWN_MEDIA, HID_MEDIA_VOL_UP_MEDIA, HID_MIC_MEDIA, HID_CAMERA_MEDIA, KEY_SCREEN_RECORD, KEY_SCREENSHOT, KEY_PRINT, KEY_SHARE, HID_RADIO_WIRELESS_MEDIA, KEY_DELETE,
                           DEGREE_KEY, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '%', '=', KEY_BACKSPACE,
                           KEY_TAB, '\'', '\"', '(', ')', '{', '}', '[', ']', '<', '>', '+', '-', KEY_RETURN,
                           TRANSFORM, '&', '#', '@', EURO_KEY, '$', POUND_KEY, YEN_KEY, '~', DIAERESIS_KEY, '^', '*', '/',
                           KEY_LEFT_SHIFT, '\\', '|', '-', '_', ';', ':', ',', '.', '?', '!', KEY_RIGHT_SHIFT,
                           KEY_LEFT_CTRL, FN_KEY, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW,
                           KEY_DOWN_ARROW
                          };

uint16_t a_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, 'a', A_GRAVE, A_ACUTE, A_CIRC, A_TILDE, A_UML, A_RING, A_MACRON, A_ELIG, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t e_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK,  E_GRAVE, E_ACUTE, 'e', E_CIRC, E_UML, E_MACRON, E_DOT, E_OGON, E_BREVE, BLANK, BLANK, BLANK, KEY_RETURN,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t y_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, 'y', Y_UML, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t u_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, U_GRAVE, U_ACUTE, U_CIRC, U_UML, U_TILDE, U_MACRON, 'u', U_BREVE, U_DBLAC, U_OGON, U_RING, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t i_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, I_GRAVE, I_ACUTE, I_CIRC, I_UML, I_TILDE, I_MACRON, 'i', I_BREVE, I_OGON, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t c_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, C_DOT, C_CARON, 'c', C_OGON, C_ACUTE, C_CIRC, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t o_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, O_GRAVE, O_ACUTE, O_CIRC, O_UML, O_TILDE, O_MACRON, O_BREVE, O_DBLAC, 'o', O_ELIG, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };

uint16_t n_variants[]  = {KEY_ESC, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, N_ACUTE, N_TILDE, N_BREVE, 'n', N_OGON , BLANK, BLANK, BLANK, BLANK,
                          BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
                          BLANK
                         };


uint32_t output_pins[] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, OUTPUT5};

uint32_t track_shift_time = 0;
uint32_t track_transform_time = 0;

uint32_t track_a_key_pressed_time = 0;
uint32_t track_e_key_pressed_time = 0;
uint32_t track_y_key_pressed_time = 0;
uint32_t track_u_key_pressed_time = 0;
uint32_t track_i_key_pressed_time = 0;
uint32_t track_c_key_pressed_time = 0;
uint32_t track_o_key_pressed_time = 0;
uint32_t track_n_key_pressed_time = 0;

uint16_t key_selected = NULL;
uint16_t last_key_selected = NULL;
uint16_t repeat_delay = 0;
uint8_t repeat_first = false;
uint8_t shift_key_right = false;
uint8_t shift_key_left = false;
uint8_t ctrl_key_right = false;
uint8_t ctrl_key_left = false;
uint8_t alt_key_right = false;
uint8_t alt_key_left = false;
uint8_t transform_key = false;
uint8_t toggle_capslock = false;
uint8_t toggle_transform = false;

uint8_t a_key_pressed = false;
uint8_t initial_a_key = false;
uint8_t e_key_pressed = false;
uint8_t initial_e_key = false;
uint8_t y_key_pressed = false;
uint8_t initial_y_key = false;
uint8_t u_key_pressed = false;
uint8_t initial_u_key = false;
uint8_t i_key_pressed = false;
uint8_t initial_i_key = false;
uint8_t c_key_pressed = false;
uint8_t initial_c_key = false;
uint8_t o_key_pressed = false;
uint8_t initial_o_key = false;
uint8_t n_key_pressed = false;
uint8_t initial_n_key = false;

uint8_t long_key_press =  false;

uint8_t special_a = false;
uint8_t special_e = false;
uint8_t special_y = false;
uint8_t special_u = false;
uint8_t special_i = false;
uint8_t special_c = false;
uint8_t special_o = false;
uint8_t special_n = false;

uint8_t fn_key = false;
uint8_t capslock_key = false;
uint8_t capitalized = false;
uint8_t uncapitalized = false;
uint8_t transformed =  false;

uint16_t pressed_key;
uint8_t key_pressed = false;
uint32_t rows1, rows2, rows3, rows4, rows5 = 0;

uint32_t inputs = 0;

void setup()
// put your setup code here, to run once:
{
  WireDisplay1.begin();
  //  WireDisplay2.begin();
  //  WireDisplay3.begin();

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

  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_LED2, OUTPUT);

  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    initDisplay(&i2c_mux1, &display , i);
  }

  i2c_mux1.setChannelMask(0);

  for (int i = 24; i < 32; i++)
  {
    initDisplay(&i2c_mux4, &display4 , i);
  }

  // display.setFont(&FreeSans9pt7b);
  // display4.setFont(&FreeSans9pt7b);

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

  //uncapitalize();
  //  delay(2000);

  checkKeys();

  digitalWrite(TEST_LED2, toggle_capslock);
  //

  if ((shift_key_right) || (shift_key_left) || (toggle_capslock))
  {
    if (!capitalized)
    {
      capitalized = true;
      uncapitalized = false;
      capitalize();
    }
  }
  else
  {
    if (!uncapitalized)
    {
      uncapitalized = true;
      transformed = false;
      capitalized = false;
      uncapitalize();
    }
  }

  if ((!shift_key_right) && (!shift_key_left) && (!toggle_capslock))
  {
    if (toggle_transform || transform_key)
    {
      if (!transformed)
      {
        digitalWrite(TEST_LED, HIGH);
        transformed = true;
        transform();
      }
    }
    else
    {
      if (transformed)
      {
        digitalWrite(TEST_LED, LOW);
        transformed = false;
        uncapitalize();
      }
    }
  }


  digitalWrite(TEST_LED, n_key_pressed);
  digitalWrite(TEST_LED2, c_key_pressed);


  if (((rows1 == 0) && (rows2 == 0) && (rows3 == 0) && (rows4 == 0) && (rows5 == 0)) && (key_pressed == true))
  {
    Keyboard.release(pressed_key);
    key_pressed = false;
  }

}

void initDisplay(TI_TCA9548A* i2c_mux, Adafruit_SSD1306* Display, int channel)
{

  if ((channel >= 8) && (channel < 16)) channel -= 8;
  if ((channel >= 16) && (channel < 24))channel -= 16;
  if ((channel >= 24) && (channel < 32))channel -= 24;
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
  if ((channel >= 24) && (channel < 32))channel -= 24;
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

  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    displayScreen(&i2c_mux1, &display , i, screens);
  }

  i2c_mux1.setChannelMask(0);

  for (int i = 8; i < 16; i++)
  {
    displayScreen(&i2c_mux4, &display4 , i, screens);
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

  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    displayScreen(&i2c_mux1, &display , i, screens2);
  }

  i2c_mux1.setChannelMask(0);

  for (int i = 8; i < 16; i++)
  {
    displayScreen(&i2c_mux4, &display4 , i, screens2);
  }

  //
  //  for (int i = 16; i < 24; i++)
  //  {
  //    displayScreen(&i2c_mux3, &display3 , i, screens2);
  //  }
}

void transform()
{


  i2c_mux4.setChannelMask(0);

  for (int i = 0; i < 8; i++)
  {
    displayScreen(&i2c_mux1, &display , i, special_screens);
  }

  i2c_mux1.setChannelMask(0);

  for (int i = 8; i < 16; i++)
  {
    displayScreen(&i2c_mux4, &display4 , i, special_screens);
  }

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

      // assign inputs to rows to detect change
      rows1 = inputs;

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          if ((fn_key) && (i < 12))
          {
            key_selected = function_keys[i];
          }
          else if (a_key_pressed)
          {
            key_selected = a_variants[i + 16 * output];
          }
          else if (e_key_pressed)
          {
            key_selected = e_variants[i + 16 * output];
          }
          else if (y_key_pressed)
          {
            key_selected = y_variants[i + 16 * output];
          }
          else if (u_key_pressed)
          {
            key_selected = u_variants[i + 16 * output];
          }
          else if (i_key_pressed)
          {
            key_selected = i_variants[i + 16 * output];
          }
          else if (c_key_pressed)
          {
            key_selected = c_variants[i + 16 * output];
          }
          else if (o_key_pressed)
          {
            key_selected = o_variants[i + 16 * output];
          }
          else if ((transform_key) || (toggle_transform))
          {
            key_selected = special_keys[i + 16 * output];
          }
          else
          {
            key_selected = keys[i + 16 * output];
            //          Serial.println("key pressed");
            //          Serial.println(i + 16 * output);
          }
        }
      }

    }

    if (output == 1)
    {

      inputs = (digitalRead(INPUT2) << 14) |
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

      if ((u_key_pressed) || (y_key_pressed) || (a_key_pressed) || (i_key_pressed) || (c_key_pressed) || (o_key_pressed) || (n_key_pressed))
      {
        inputs |= digitalRead(INPUT1) << 15;
      }

      if ((u_key_pressed) || (y_key_pressed) || (e_key_pressed) || (i_key_pressed) || (c_key_pressed) || (o_key_pressed) || (n_key_pressed))
      {
        inputs |= digitalRead(INPUT3) << 13;
      }

      // assign inputs to rows to detect change
      rows2 = inputs;

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          if ((transform_key) || (toggle_transform))
          {
            key_selected = special_keys[i + 16 * output];
          }
          else if (a_key_pressed)
          {
            key_selected = a_variants[i + 16 * output];
          }
          else if (e_key_pressed)
          {
            key_selected = e_variants[i + 16 * output];
          }
          else if (y_key_pressed)
          {
            key_selected = y_variants[i + 16 * output];
          }
          else if (u_key_pressed)
          {
            key_selected = u_variants[i + 16 * output];
          }
          else if (i_key_pressed)
          {
            key_selected = i_variants[i + 16 * output];
          }
          else if (c_key_pressed)
          {
            key_selected = c_variants[i + 16 * output];
          }
          else if (o_key_pressed)
          {
            key_selected = o_variants[i + 16 * output];
          }
          else
          {
            key_selected = keys[i + 16 * output];
            //          Serial.println("key pressed");
            //          Serial.println(i uu+ 16 * output);
          }
        }
      }

      if ((!u_key_pressed) && (!y_key_pressed) && (!e_key_pressed) && (!i_key_pressed) && (!c_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'a' key pressed?
        if ((digitalRead(INPUT3) == HIGH))
        {
          if (initial_a_key == false)
          {
            track_a_key_pressed_time = millis();
            initial_a_key = true;
            special_a = false;
          }

          if (((millis() - track_a_key_pressed_time) >= 1000) && ((millis() - track_a_key_pressed_time) < 3000))
          {
            a_key_pressed = true;
            long_key_press =  false;
          }
          else if ((millis() - track_a_key_pressed_time) >= 3000)
          {
            if (!special_a)
            {
              long_key_press = true;
              a_key_pressed =  false;
              Keyboard.press('a');
            }
          }

        }
        else if ((digitalRead(INPUT3) == LOW) && (initial_a_key == true))
        {
          a_key_pressed = false;
          initial_a_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('a');
          }
          else if (!special_a)
          {
            key_selected = 'a';

            // for adding info to rows variable to detect change
            rows2 |= 1;
          }
        }
      }

      if ((!u_key_pressed) && (!a_key_pressed) && (!y_key_pressed) && (!i_key_pressed) && (!c_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'e' key pressed?
        if ((digitalRead(INPUT1) == HIGH))
        {
          if (initial_e_key == false)
          {
            track_e_key_pressed_time = millis();
            initial_e_key = true;
            special_e = false;
          }

          if (((millis() - track_e_key_pressed_time) >= 1000) && ((millis() - track_e_key_pressed_time) < 3000))
          {
            e_key_pressed = true;
            long_key_press =  false;
          }
          else if ((millis() - track_e_key_pressed_time) >= 3000)
          {
            if (!special_e)
            {
              long_key_press = true;
              e_key_pressed =  false;
              Keyboard.press('e');
            }
          }
        }

        else if ((digitalRead(INPUT1) == LOW) && (initial_e_key == true))
        {
          e_key_pressed = false;
          initial_e_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('e');
          }
          else if (!special_e)
          {
            key_selected = 'e';

            // for adding info to rows variable to detect change
            rows2 |= 1;
          }
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
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT9) <<  7) |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      // u key
      if (y_key_pressed || a_key_pressed || e_key_pressed || i_key_pressed || c_key_pressed || o_key_pressed || n_key_pressed)
      {
        inputs |= digitalRead(INPUT13) << 3;
      }

      // y key
      if (u_key_pressed || a_key_pressed || e_key_pressed || i_key_pressed || c_key_pressed || o_key_pressed || n_key_pressed)
      {
        inputs |= digitalRead(INPUT14) << 2;
      }

      // i key
      if (u_key_pressed || a_key_pressed || e_key_pressed || y_key_pressed || c_key_pressed || o_key_pressed || n_key_pressed)
      {
        inputs |= digitalRead(INPUT12) << 4;
      }

      // o key
      if (u_key_pressed || a_key_pressed || e_key_pressed || y_key_pressed || c_key_pressed || i_key_pressed || n_key_pressed)
      {
        inputs |= (digitalRead(INPUT11) << 5);
      }

      // assign inputs to rows to detect change
      rows3 = inputs;

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          if ((transform_key) || (toggle_transform))
          {
            key_selected = special_keys[i + 16 * output];
          }
          else if (a_key_pressed)
          {
            key_selected = a_variants[i + 16 * output];
          }
          else if (e_key_pressed)
          {
            key_selected = e_variants[i + 16 * output];
          }
          else if (y_key_pressed)
          {
            key_selected = y_variants[i + 16 * output];
          }
          else if (u_key_pressed)
          {
            key_selected = u_variants[i + 16 * output];
          }
          else if (i_key_pressed)
          {
            key_selected = i_variants[i + 16 * output];
          }
          else if (c_key_pressed)
          {
            key_selected = c_variants[i + 16 * output];
          }
          else if (o_key_pressed)
          {
            key_selected = o_variants[i + 16 * output];
          }
          else
          {
            key_selected = keys[i + 16 * output];
            //          Serial.println("key pressed");
            //          Serial.println(i + 16 * output);
          }
        }
      }

      if ((!u_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!i_key_pressed) && (!c_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'y' key pressed?
        if ((digitalRead(INPUT14) == HIGH))
        {
          if (initial_y_key == false)
          {
            track_y_key_pressed_time = millis();
            initial_y_key = true;
            special_y = false;
          }

          if (((millis() - track_y_key_pressed_time) >= 1000) && (((millis() - track_y_key_pressed_time) < 3000)))
          {
            y_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_y_key_pressed_time) >= 3000)
          {
            if (!special_y)
            {
              long_key_press = true;
              y_key_pressed =  false;
              Keyboard.press('y');
            }
          }
        }

        else if ((digitalRead(INPUT14) == LOW) && (initial_y_key == true))
        {
          y_key_pressed = false;
          initial_y_key =  false;

          if (long_key_press)
          {
            long_key_press = false;
            Keyboard.release('y');
          }

          if (!special_y)
          {
            key_selected = 'y';

            // for adding info to rows variable to detect change
            rows3 |= 1;
          }
        }
      }

      if ((!y_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!i_key_pressed) && (!c_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'u' key pressed?
        if ((digitalRead(INPUT13) == HIGH))
        {
          if (initial_u_key == false)
          {
            track_u_key_pressed_time = millis();
            initial_u_key = true;
            special_u = false;
          }

          if (((millis() - track_u_key_pressed_time) >= 1000) && ((millis() - track_u_key_pressed_time) < 3000))
          {
            u_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_u_key_pressed_time) >= 3000)
          {
            if (!special_u)
            {
              long_key_press = true;
              u_key_pressed =  false;
              Keyboard.press('u');
            }
          }
        }
        else if ((digitalRead(INPUT13) == LOW) && (initial_u_key == true))
        {
          u_key_pressed = false;
          initial_u_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('u');
          }
          else if (!special_u)
          {
            key_selected = 'u';

            // for adding info to rows variable to detect change
            rows3 |= 1;
          }
        }
      }

      if ((!y_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!u_key_pressed) && (!c_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'i' key pressed?
        if ((digitalRead(INPUT12) == HIGH))
        {
          if (initial_i_key == false)
          {
            track_i_key_pressed_time = millis();
            initial_i_key = true;
            special_i = false;
          }

          if (((millis() - track_i_key_pressed_time) >= 1000) && ((millis() - track_i_key_pressed_time) < 3000))
          {
            i_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_i_key_pressed_time) >= 3000)
          {
            if (!special_i)
            {
              long_key_press = true;
              i_key_pressed =  false;
              Keyboard.press('i');
            }
          }
        }
        else if ((digitalRead(INPUT12) == LOW) && (initial_i_key == true))
        {
          i_key_pressed = false;
          initial_i_key =  false;

          if (long_key_press)
          {
            long_key_press = false;
            Keyboard.release('i');
          }
          else if (!special_i)
          {
            key_selected = 'i';

            // for adding info to rows variable to detect change
            rows3 |= 1;
          }

        }

        if ((digitalRead(INPUT6) == HIGH) && (transform_key == false))
        {
          transform_key = true;
          track_transform_time = millis();
        }
        else if ((digitalRead(INPUT6) == LOW) && (transform_key == true))
        {
          transform_key = false;

          if ((millis() - track_transform_time) < 1000)
          {
            track_transform_time = millis();
            toggle_transform = !toggle_transform;
          }
        }

      }

      if ((!y_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!u_key_pressed) && (!c_key_pressed) && (!i_key_pressed) && (!n_key_pressed))
      {
        // 'o' key pressed?
        if ((digitalRead(INPUT11) == HIGH))
        {
          if (initial_o_key == false)
          {
            track_o_key_pressed_time = millis();
            initial_o_key = true;
            special_o = false;
          }

          if (((millis() - track_o_key_pressed_time) >= 1000) && ((millis() - track_o_key_pressed_time) < 3000))
          {
            o_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_o_key_pressed_time) >= 3000)
          {
            if (!special_o)
            {
              long_key_press = true;
              o_key_pressed =  false;
              Keyboard.press('o');
            }
          }
        }
        else if ((digitalRead(INPUT11) == LOW) && (initial_o_key == true))
        {
          o_key_pressed = false;
          initial_o_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('o');
          }
          else if (!special_o)
          {
            key_selected = 'o';

            // for adding info to rows variable to detect change
            rows3 |= 1;
          }

        }

        if ((digitalRead(INPUT6) == HIGH) && (transform_key == false))
        {
          transform_key = true;
          track_transform_time = millis();
        }
        else if ((digitalRead(INPUT6) == LOW) && (transform_key == true))
        {
          transform_key = false;

          if ((millis() - track_transform_time) < 1000)
          {
            track_transform_time = millis();
            toggle_transform = !toggle_transform;
          }
        }

      }
    }

    if (output == 3)
    {

      inputs = (digitalRead(INPUT1) << 15) |
               //(digitalRead(INPUT2) << 14) |
               (digitalRead(INPUT4) << 12) |
               (digitalRead(INPUT5) << 11) |
               (digitalRead(INPUT7) << 9)  |
               (digitalRead(INPUT8) << 8)  |
               (digitalRead(INPUT10) << 6) |
               (digitalRead(INPUT11) << 5) |
               (digitalRead(INPUT12) << 4) |
               (digitalRead(INPUT13) << 3) |
               (digitalRead(INPUT14) << 2) |
               (digitalRead(INPUT15) << 1) |
               (digitalRead(INPUT16) << 0);

      if (u_key_pressed || a_key_pressed || e_key_pressed || y_key_pressed || i_key_pressed || o_key_pressed || n_key_pressed)
      {
        inputs |= digitalRead(INPUT6) << 10;
      }

      if (u_key_pressed || a_key_pressed || e_key_pressed || y_key_pressed || i_key_pressed || o_key_pressed || c_key_pressed)
      {
        inputs |= (digitalRead(INPUT3) << 13) ;
      }

      // assign inputs to rows to detect change
      rows4 = inputs;



      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          if ((transform_key) || (toggle_transform))
          {
            key_selected = special_keys[i + 16 * output];
          }
          else if (a_key_pressed)
          {
            key_selected = a_variants[i + 16 * output];
          }
          else if (e_key_pressed)
          {
            key_selected = e_variants[i + 16 * output];
          }
          else if (y_key_pressed)
          {
            key_selected = y_variants[i + 16 * output];
          }
          else if (u_key_pressed)
          {
            key_selected = u_variants[i + 16 * output];
          }
          else if (i_key_pressed)
          {
            key_selected = i_variants[i + 16 * output];
          }
          else if (c_key_pressed)
          {
            key_selected = c_variants[i + 16 * output];
          }
          else if (o_key_pressed)
          {
            key_selected = o_variants[i + 16 * output];
          }
          else if (n_key_pressed)
          {
            key_selected = n_variants[i + 16 * output];
          }
          else
          {
            key_selected = keys[i + 16 * output];
            //          Serial.println("key pressed");
            //          Serial.println(i + 16 * output);
          }
        }
      }

      if ((!u_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!i_key_pressed) && (!y_key_pressed) && (!o_key_pressed) && (!n_key_pressed))
      {
        // 'c' key pressed?
        if ((digitalRead(INPUT6) == HIGH))
        {
          if (initial_c_key == false)
          {
            track_c_key_pressed_time = millis();
            initial_c_key = true;
            special_c = false;
          }

          if (((millis() - track_c_key_pressed_time) >= 1000) && ((millis() - track_c_key_pressed_time) < 3000))
          {
            c_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_c_key_pressed_time) >= 3000)
          {
            if (!special_c)
            {
              long_key_press = true;
              c_key_pressed =  false;
              Keyboard.press('c');
            }
          }
        }

        else if ((digitalRead(INPUT14) == LOW) && (initial_c_key == true))
        {
          c_key_pressed = false;
          initial_c_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('c');
          }
          else if (!special_c)
          {
            key_selected = 'c';

            // for adding info to rows variable to detect change
            rows4 |= 1;
          }
        }
      }

      if ((!u_key_pressed) && (!a_key_pressed) && (!e_key_pressed) && (!i_key_pressed) && (!y_key_pressed) && (!o_key_pressed) && (!c_key_pressed))
      {
        // 'n' key pressed?
        if ((digitalRead(INPUT3) == HIGH))
        {
          if (initial_n_key == false)
          {
            track_n_key_pressed_time = millis();
            initial_n_key = true;
            special_n = false;
            digitalWrite(TEST_LED2, HIGH);
          }

          if (((millis() - track_n_key_pressed_time) >= 1000) && ((millis() - track_n_key_pressed_time) < 3000))
          {
            n_key_pressed = true;
            long_key_press = false;
          }
          else if ((millis() - track_n_key_pressed_time) >= 3000)
          {
            if (!special_n)
            {
              long_key_press = true;
              n_key_pressed =  false;
              Keyboard.press('n');
            }
          }
        }

        else if ((digitalRead(INPUT3) == LOW) && (initial_n_key == true))
        {
          n_key_pressed = false;
          initial_n_key =  false;

          if (long_key_press)
          {
            long_key_press =  false;
            Keyboard.release('n');
          }
          else if (!special_n)
          {
            key_selected = 'n';

            // for adding info to rows variable to detect change
            rows4 |= 1;
          }
        }
      }

      // Left shift key
      if ((digitalRead(INPUT9) == HIGH) && (shift_key_left == false))
      {
        shift_key_left = true;
        //Keyboard.press(KEY_LEFT_SHIFT);

        track_shift_time = millis();
      }
      else if ((digitalRead(INPUT9) == LOW) && (shift_key_left == true))
      {
        shift_key_left = false;
        //Keyboard.release(KEY_LEFT_SHIFT);

        if ((millis() - track_shift_time) < (1000))
        {
          track_shift_time = millis();
          toggle_capslock = !toggle_capslock;
          //Keyboard.write(KEY_CAPS_LOCK);
        }
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

      // assign inputs to rows to detect change
      rows5 = inputs;

      for (int i = 0; i < 16; i++)
      {
        if ((inputs >> i) & 0b01)
        {
          if ((transform_key) || (toggle_transform))
          {
            key_selected = special_keys[i + 16 * output];
          }
          else if (a_key_pressed)
          {
            key_selected = a_variants[i + 16 * output];
          }
          else if (e_key_pressed)
          {
            key_selected = e_variants[i + 16 * output];
          }
          else if (y_key_pressed)
          {
            key_selected = y_variants[i + 16 * output];
          }
          else if (u_key_pressed)
          {
            key_selected = u_variants[i + 16 * output];
          }
          else if (i_key_pressed)
          {
            key_selected = i_variants[i + 16 * output];
          }
          else if (c_key_pressed)
          {
            key_selected = c_variants[i + 16 * output];
          }
          else if (o_key_pressed)
          {
            key_selected = o_variants[i + 16 * output];
          }
          else
          {
            key_selected = keys[i + 16 * output];
            //          Serial.println("key pressed");
            //          Serial.println(i + 16 * output);
          }
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

    case KEY_CANCEL:
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

    case DEGREE_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_6);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case EURO_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case POUND_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case YEN_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case DIAERESIS_KEY:
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // A key variants

    case A_GRAVE:
      special_a = true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_ACUTE:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_CIRC:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_6);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_TILDE:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_UML:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_RING:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_MACRON:
      special_a =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case A_ELIG:
      special_a =  true;

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_0);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // E key variants

    case E_GRAVE:
      special_e = true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_2);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_ACUTE:
      special_e = true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_CIRC:
      special_e = true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_4);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_TILDE:
      special_e =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_UML:
      special_e =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_MACRON:
      special_e =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_BREVE:
      special_e =  true;

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_DOT:
      special_e =  true;

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_OGON:
      special_e =  true;

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_8);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case E_CARON:
      special_e =  true;

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_8);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // y key variants

    case Y_UML:
      special_y =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // u key variants

    case U_GRAVE:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_ACUTE:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.write(NUM_0);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_CIRC:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_TILDE:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_MACRON:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_BREVE:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_DBLAC:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_OGON:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_7);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_RING:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case U_UML:
      special_u =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_5);
      Keyboard.write(NUM_2);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // i key variants

    case I_GRAVE:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_6);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_ACUTE:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_CIRC:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_TILDE:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_9);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_MACRON:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_9);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_BREVE:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case I_OGON:
      special_i =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // c key variants

    case C_DOT:
      special_c =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case C_CARON:
      special_c =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case C_ACUTE:
      special_c =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case C_OGON:
      special_c =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case C_CIRC:
      special_c =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_6);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    // o key variants
    case O_GRAVE:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_2);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_ACUTE:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_CIRC:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_4);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_UML:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_6);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_TILDE:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_MACRON:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_BREVE:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_5);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_DBLAC:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_7);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case O_ELIG:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_9);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;


    // n key variants
    case N_ACUTE:
      special_n =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case N_TILDE:
      special_o =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_4);
      Keyboard.write(NUM_1);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case N_CARON:
      special_n =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_2);
      Keyboard.write(NUM_8);
      Keyboard.release(KEY_LEFT_ALT);

      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);
      break;

    case N_OGON:
      special_n =  true;
      if (!last_num_lock_state)Keyboard.write(KEY_NUM_LOCK);

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write(NUM_0);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_3);
      Keyboard.write(NUM_1);
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
      //Keyboard.write(key_selected);
      if (((rows1) || (rows2) || (rows3) || (rows4) || (rows5)) && (key_pressed == false))
      {
        digitalWrite(TEST_LED2, HIGH);
        Keyboard.press(key_selected);
        pressed_key = key_selected;
        key_pressed = true;
      }

      break;

  }
}
