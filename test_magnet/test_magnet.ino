#include <CapacitiveSensor.h>

// resistor between pins 4 and 2, foil connected to wire which is connected to pin 2
// wiring diagram for hand is in separate diagram

int ALARM_PIN = 8;
int MAGNET = 7;

//resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);

// threshold that determines when sensor is touched; depends on value of resistor
int delta = 2000;
int baseline;
boolean on;
int lastButtonVal;

void setup() {
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(MAGNET, OUTPUT);
  digitalWrite(MAGNET, HIGH);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  on = false;
  reset();
}

void loop() {
  if (true) {
    long sensor =  cs_4_2.capacitiveSensor(30);
    Serial.println(sensor);
    if (sensor > baseline + delta) {
      
      digitalWrite(MAGNET, LOW);
      if (!on) {
        digitalWrite(ALARM_PIN, HIGH);
        on = true;
      } else {
        digitalWrite(ALARM_PIN, LOW);
        on = false;
      }
      
      delay(1000);
    } else {
      digitalWrite(ALARM_PIN, LOW);    
       digitalWrite(MAGNET, HIGH);
      on = false;
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



