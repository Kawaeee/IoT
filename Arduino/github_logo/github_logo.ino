//github_logo = draw Github icon in OLED 128*64 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,55);
  display.println("GitHub");
  display.setCursor(85,55);
  display.println("Arduino");
  
  display.fillCircle(64, 32, 28, WHITE); // center circle
  display.fillTriangle(45, 25, 47, 12, 70, 20, BLACK); // left ear
  display.fillTriangle(60, 25, 80, 12, 84, 30, BLACK); // right ear

  display.fillRoundRect(45, 16, 40, 30, 15, BLACK); // head
  display.fillRoundRect(55, 42, 20, 40, 30, BLACK); // body

  // hand
  display.drawLine(43, 42, 55, 50, BLACK);
  display.drawLine(43, 43, 55, 51, BLACK);
  display.drawLine(43, 44, 55, 52, BLACK);
  display.drawLine(43, 45, 55, 53, BLACK);

  display.display();
  delay(2000);
}

void loop() {

}
