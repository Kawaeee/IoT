//oled_weather = connect ESP8266 to internet and use openweathermap API to get realtime data and display it in OLED 128*64
// Kawae Weather Station with OLED
// pin configuration
// connect scl,sda to pin 1,pin 2
// connect gnd,3v3 to pin gnd,pin vcc

#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ArduinoJson.h>

const char *ssid =  "-";     // Replace with your wifi ssid and wpa2 key
const char *pass =  "-";

String API_KEY = "-"; // This API key should be generated from openweather
String CITY_ID = "1609350"; // This ID is for Bangkok city
String API = "http://api.openweathermap.org/data/2.5/weather?id=" + CITY_ID + "&APPID=" + API_KEY;

WiFiClient client;

#define OLED_RESET LED_BUILTIN  // 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height Incorrect!!, Please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println("Connecting to ");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay(); // Clear the display buffer

  // Instantiate Screen
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Kawae Weather Station");
  display.display();

  WiFi.begin(ssid, pass);

  Serial.print("Connecting.");
  display.setCursor(0, 12);
  display.println("Connecting...");
  display.display();

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected!!!");
  display.print("Connected!!!");
  display.display();
  delay(1000);
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(API);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString(); // Get the request response payload

      DynamicJsonDocument jsonBuffer(1024); // JSON Buffer

      auto error = deserializeJson(jsonBuffer, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
      }

      // Get data from JSON
      String weather = jsonBuffer["weather"][0]["main"];
      float temp = (float)(jsonBuffer["main"]["temp"]) - 273.15; // get temperature in °C
      int humidity = jsonBuffer["main"]["humidity"]; // get humidity in %
      int visibility = jsonBuffer["visibility"]; // get visibility
      String names = jsonBuffer["name"];
      String country = jsonBuffer["sys"]["country"]; // get state and country
      float wind_speed = jsonBuffer["wind"]["speed"]; // get wind speed in m/s

      // Print data
      Serial.printf("Weather: %s \r\n", weather.c_str());
      Serial.printf("Temperature = %.2f C\r\n", temp);
      Serial.printf("Humidity = %d %%\r\n", humidity);
      Serial.printf("Visibility = %d \r\n", visibility);
      Serial.printf("Wind speed = %.1f m/s\r\n", wind_speed);
      Serial.printf("Location: %s,", names.c_str());
      Serial.printf("%s \r\n", country.c_str());

      // Display to screen
      display.setCursor(0, 12);
      display.printf("Weather: %s \r\n", weather.c_str());
      display.printf("Temperature: %5.2f C\r\n", temp);
      display.printf("Humidity: %d %%\r\n", humidity);
      display.printf("Visibility: %d \r\n", visibility);
      display.printf("Wind speed: %.1f m/s\r\n", wind_speed);
      display.printf("Location: %s,", names.c_str());
      display.printf("%s \r\n", country.c_str());

      display.display();
    }
    http.end();
  }
  delay(600000); // delays 10 minutes
}
