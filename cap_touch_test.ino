#include <CapacitiveSensor.h>

// resistor between pins 4 and 2, foil connected to wire which is connected to pin 2
// wiring diagram for hand is in separate diagram

int MOTOR_1 = 12;
int MOTOR_2 = 11;
int MOTOR_3 = 10;
int MOTOR_4 = 9;
int ALARM_PIN = 8;
int BUTTON_PIN = 13;

//resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);

// threshold that determines when sensor is touched; depends on value of resistor
int delta = 2000;
int baseline;
boolean LEDon;
int lastButtonVal;

void setup() {
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_3, OUTPUT);
  pinMode(MOTOR_4, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  LEDon = false;
  reset();
  lastButtonVal = digitalRead(BUTTON_PIN);
}

void loop() {
  if (true) {
//  if (checkButton()) {
    Serial.println("button on");
      long sensor =  cs_4_2.capacitiveSensor(30);
    Serial.println(sensor);
    if (sensor > baseline + delta) {
      if (!LEDon) {
        digitalWrite(ALARM_PIN, LOW);
        digitalWrite(MOTOR_1, HIGH);
        digitalWrite(MOTOR_2, HIGH);
        digitalWrite(MOTOR_3, HIGH);
        digitalWrite(MOTOR_4, HIGH);
        LEDon = true;
      } else {
        digitalWrite(ALARM_PIN, HIGH);
        digitalWrite(MOTOR_1, LOW);
        digitalWrite(MOTOR_2, LOW);
        digitalWrite(MOTOR_3, LOW);
        digitalWrite(MOTOR_4, LOW);
        LEDon = false;
      }
      delay(500);
    } else {
      digitalWrite(ALARM_PIN, LOW);
      digitalWrite(MOTOR_1, LOW);
      digitalWrite(MOTOR_2, LOW);
      digitalWrite(MOTOR_3, LOW);
      digitalWrite(MOTOR_4, LOW);
      LEDon = false;
      delay(100);
    }
  }
}

void reset() {
  int sum = 0;
  for (int i = 0; i < 20; i++) {
    sum = sum + cs_4_2.capacitiveSensor(30);
    delay(100);
  }
  baseline = (int) (sum / 20.0);
}

boolean checkButton() {
  int val = digitalRead(BUTTON_PIN);
   Serial.println(val);
  if (val != lastButtonVal) {
    if (val == HIGH) { // just turned on
      reset();
    } else { // just turned off
      digitalWrite(ALARM_PIN, LOW);
       digitalWrite(MOTOR_1, LOW);
       digitalWrite(MOTOR_2, LOW);
       digitalWrite(MOTOR_3, LOW);
       digitalWrite(MOTOR_4, LOW);
        LEDon = false;
    }
  }
  lastButtonVal = val;
  return (val == HIGH);
}

