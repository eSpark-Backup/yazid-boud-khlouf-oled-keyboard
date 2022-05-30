#include "TI_TCA9548A.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Fonts/specialfont18pt7b.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

TwoWire WireDisplay1(PB9, PB8);
TwoWire WireDisplay2(PB11, PB10);
TwoWire WireDisplay3(PC9, PA8);

TI_TCA9548A i2c_mux1(&WireDisplay1);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay1, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay2, OLED_RESET);
Adafruit_SSD1306 display3(SCREEN_WIDTH, SCREEN_HEIGHT, &WireDisplay3, OLED_RESET);


void setup() {
  // put your setup code here, to run once:

  WireDisplay1.begin();


  display.setFont(&finalfont18pt7b);



  initDisplay1();
  initDisplay2();
  initDisplay3();
  initDisplay4();
  initDisplay5();
  initDisplay6();
  initDisplay7();
  initDisplay8();

  displayScreen1();
  displayScreen2();
  displayScreen3();
  displayScreen4();
  displayScreen5();
  displayScreen6();
  displayScreen7();
  displayScreen8();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initDisplay1()
{

  i2c_mux1.selectChannel(0);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay2()
{
  i2c_mux1.selectChannel(1);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay3()
{
  i2c_mux1.selectChannel(2);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay4()
{
  i2c_mux1.selectChannel(3);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay5()
{
  i2c_mux1.selectChannel(4);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay6()
{
  i2c_mux1.selectChannel(5);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay7()
{
  i2c_mux1.selectChannel(6);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void initDisplay8()
{
  i2c_mux1.selectChannel(7);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
}

void displayScreen1()
{
  i2c_mux1.selectChannel(0);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("a"));

  display.display();
}

void displayScreen2()
{
  i2c_mux1.selectChannel(1);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("b"));

  display.display();
}

void displayScreen3()
{
  i2c_mux1.selectChannel(2);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("c"));

  display.display();
}

void displayScreen4()
{
  i2c_mux1.selectChannel(3);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("d"));

  display.display();
}

void displayScreen5()
{
  i2c_mux1.selectChannel(4);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("e"));

  display.display();
}

void displayScreen6()
{
  i2c_mux1.selectChannel(5);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("f"));

  display.display();
}

void displayScreen7()
{
  i2c_mux1.selectChannel(6);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("g"));

  display.display();
}

void displayScreen8()
{
  i2c_mux1.selectChannel(7);

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 40);
  display.println(F("h"));

  display.display();
}
