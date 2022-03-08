#include "TI_TCA9548A.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

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

char screens[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Z', '1', '2', '3', '4', '5', '6', '7'};

void setup() {
  // put your setup code here, to run once:

  WireDisplay1.begin();
  WireDisplay2.begin();
  WireDisplay3.begin();

  for (int i = 0; i < 8; i++)
  {
    initDisplay(&i2c_mux1, &display , i);
    displayScreen(&i2c_mux1, &display , i);
  }

  for (int i = 8; i < 16; i++)
  {
    initDisplay(&i2c_mux2, &display2 , i);
    displayScreen(&i2c_mux2, &display2 , i);
  }

  for (int i = 16; i < 24; i++)
  {
    initDisplay(&i2c_mux3, &display3 , i);
    displayScreen(&i2c_mux3, &display3 , i);
  }


  //  for (int i = 24; i < 30; i++)
  //  {
  //    initDisplay(&i2c_mux4, &display4 , i);
  //    displayScreen(&i2c_mux4, &display4 , i);
  //  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initDisplay(TI_TCA9548A* i2c_mux, Adafruit_SSD1306* Display, int channel)
{

  if ((channel >= 8) && (channel < 16)) channel -= 8;
  if ((channel >= 16) && (channel < 24))channel -= 16;
  i2c_mux->selectChannel(channel);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!Display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  Display->display();
}

void displayScreen(TI_TCA9548A* i2c_mux, Adafruit_SSD1306* Display, int channel)
{
  int screen_number = channel;
  if ((channel >= 8) && (channel < 16)) channel -= 8;
  if ((channel >= 16) && (channel < 24))channel -= 16;
  i2c_mux->selectChannel(channel);

  // Clear the buffer
  Display->clearDisplay();

  Display->setTextSize(4); // Draw 2X-scale text
  Display->setTextColor(SSD1306_WHITE);
  Display->setCursor(10, 20);
  Display->println(screens[screen_number]);

  Display->display();
}
