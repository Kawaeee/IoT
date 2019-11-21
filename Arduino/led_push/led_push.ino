//led_push = one press on button -> LED on -> one more pressed -> LED off
#include "pitches.h"

const int buttonPin = 3;     // push button pin
const int ledPin =  13;      // LED pin
const int buzzerPin = 8;

// Push button state - both released
int stateNow = 0;
int stateBefore = 0;

// LED state - ready to push/release
bool LED_on = false;
bool LED_off = false;

// 1,HIGH= released
// 0,LOW = pushed

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  stateNow = digitalRead(buttonPin);
  //  Serial.println(stateNow);

  if (stateNow != stateBefore) {
    // released 1 0 1
    if (stateNow == HIGH and LED_on == false) {
      digitalWrite (ledPin, HIGH);
      LED_off = true;
      Serial.println("ON");
    }
    // pushed 0 1 0
    else if (stateNow == LOW and LED_off == true) {
      LED_on = true;
    }
    else if (stateNow == HIGH and LED_on == true) {
      digitalWrite (ledPin, LOW);
      LED_off = false;
      Serial.println("OFF");
    }
    else if (stateNow == LOW and LED_off == false) {
      LED_on = false;
    }
  }
  stateBefore = stateNow;
}
