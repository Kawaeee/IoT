//ldr_led = LDR sensor with LED to manage led light
const int ldrPin = A5;    // select the input pin for the LDR
const int ledPin = 9;   // select the pin for the LED
int val = 0;
int mapper = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}


void loop() {
  val = analogRead(ldrPin);
  if (val >= 800) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.println(val);
  delay(100);
}
