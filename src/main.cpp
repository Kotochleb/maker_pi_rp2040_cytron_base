#include <Arduino.h>

#include "maker_pi_pins.h"

boolean Direction_right = true;
volatile long right_wheel_pulse_count = 0;

float ang_vel = 0;
 
int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

float tics_per_rotation = 100.0;

void right_wheel_pulse();
  
void setup() {
  Serial.begin(9600); 
 
  // Set pin states of the encoder
  pinMode(maker_pi::pins::GROOVE_1_A, INPUT);
  pinMode(maker_pi::pins::GROOVE_1_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(maker_pi::pins::GROOVE_1_A), right_wheel_pulse, RISING);
   
}
 
void loop() {
  currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    ang_vel = float(right_wheel_pulse_count) / tics_per_rotation;
     
    Serial.print("Angular velocity: ");
    Serial.println(ang_vel);
 
    right_wheel_pulse_count = 0;
   
  }
}

void right_wheel_pulse() {
  int val = digitalRead(maker_pi::pins::GROOVE_1_B);
 
  if(val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}