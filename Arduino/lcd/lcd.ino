//lcd = display text in LiquidCrystal_I2C lcd
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const int ldr = A5;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

char * message = "Zzz";

int light = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  light = analogRead(ldr);
  Serial.println(light);
  lcd.setCursor(0, 0);

  lcd.print("LDR value = ");
  lcd.print(light);
  lcd.setCursor(0, 1);
  
  for (int printStart = 15; printStart >= 0; printStart--)  //scroll on from right
  {
    showLetters(printStart, 0);
  }

  for (int letter = 1; letter <= strlen(message); letter++)  //scroll off to left
  {
    showLetters(0, letter);
  }

  delay(1000);
}

void showLetters(int printStart, int startLetter)
{
  lcd.setCursor(printStart, 1);
  for (int currentLetter = startLetter; currentLetter < strlen(message); currentLetter++)
  {
    lcd.print(message[currentLetter]);
  }
  lcd.print(" ");
  delay(250);
}
