// pot_led = Potentiometer with LED 
const int potPin = A0;    // select the input pin for the potentiometer
const int ledPin = 11;   // select the pin for the LED
int val = 0; 
int mapper = 0;

void setup() {
  Serial.begin(9600);
}


void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  mapper = map(val,0,1023,0,255);
  analogWrite(ledPin, mapper);  // turn the ledPin on
  Serial.println(val);
  delay(100);   
}            
