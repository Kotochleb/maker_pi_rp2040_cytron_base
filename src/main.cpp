#include <Arduino.h>
// #include <PID_v1.h>

#include "maker_pi_pins.h"
#include "pio_rotary_encoder.h"

 
// Initialize static member of class Rotary_encoder
int RotaryEncoder::rotation = 0;
RotaryEncoder my_encoder(16);

long previousMillis = 0;
long currentMillis = 0;
int interval = 100;

bool pin_state = 0;

int last_rotation;

void setup() {
  Serial.begin(115200); 
  
  my_encoder.set_rotation(0);

  pinMode(28, OUTPUT);
  digitalWrite(28, HIGH);
   
}
 
void loop() {
  currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;

    int current_rotation = my_encoder.get_rotation();
     
    printf("Angular velocity: %d\n", last_rotation - current_rotation);

    last_rotation = current_rotation;

    digitalWrite(28, pin_state);
    if (pin_state) {
      pin_state = false;
    }
    else {
      pin_state = true;
    }
   
  }
}