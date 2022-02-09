#include <Servo.h>

Servo Switch;

const int LED0 = 2;
const int LED_COUNT = 9;

const int SERVO_PIN = 11;

const int BUTTON1 = 12;
const int BUTTON2 = 13;

int Button1Counter = 0;

int Hours = 0;
int Minutes = 0;

long long tick = 0;

void setup() {
  //Serial.begin(9600);
 
  // LEDs
  for (int i = LED0; i < LED0+LED_COUNT; i++) {
    pinMode(i,OUTPUT);
  }
 
  // Servo
  pinMode(SERVO_PIN,OUTPUT);
  Switch.attach(SERVO_PIN);
  Switch.write(30);

 
  // Buttons
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);

  IntroAnimation();
}

void IntroAnimation() {
  for (int i = LED0; i < LED0+LED_COUNT; i++) {
    digitalWrite(i,HIGH);
    delay(50);
  }
  for (int i = LED0; i < LED0+LED_COUNT; i++) {
    digitalWrite(i,LOW);
    delay(50);
  }
}

const unsigned long SECOND = 1000;
const unsigned long MINUTE = 60*SECOND;
const unsigned long HOUR = 60*MINUTE;

void StartDelay() {
  for (int i = LED0; i < LED0+LED_COUNT; i++) {
    digitalWrite(i,LOW);
    for (int j = 0; j < 5; j++) {
      UpdateLEDs();
      delay(10);
    }
  }
 
  delay(MINUTE*15*Minutes + HOUR*Hours);
 
  Switch.write(170);

  delay(3000);
 
  // reset
  Button1Counter = 0;
  Hours = 0;
  Minutes = 0;
  Switch.write(30);

}

void UpdateLEDs(){
  tick++;
  for (int i = LED0; i < LED0+Hours; i++) {
    digitalWrite(i,HIGH);
  }
  if (tick/10 % 4 < Minutes) {
    digitalWrite(LED0+Hours,HIGH);
  } else {
    digitalWrite(LED0+Hours,LOW);
  }
  for (int i = LED0+Hours+1; i < LED0+LED_COUNT; i++) {
    digitalWrite(i,LOW);
  }
}

void loop() {
  Switch.write(30);
 
  if (digitalRead(BUTTON1) == HIGH) {
    Button1Counter++;
  } else {
    Button1Counter = 0;
  }
 
  if (digitalRead(BUTTON2) == HIGH) {
    StartDelay();
  }
 
  if (Button1Counter == 10) {
    if (Hours == LED_COUNT) {
      Hours = 0;
    } else {
      Hours++;
    }
  } else if (Button1Counter == 100) {
    Hours--;
    if (Minutes == 3) {
      Minutes = 0;
    } else {
      Minutes++;
    }
  }
 
  UpdateLEDs();
  delay(10);
}
