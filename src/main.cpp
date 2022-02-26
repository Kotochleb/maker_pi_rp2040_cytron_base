#include <Arduino.h>
#include <PID_v1.h>

#include "pio_rotary_encoder.h"

// initialise static encoder variables for both motors
int RotaryEncoder::rotation_motor_a = 0;
int RotaryEncoder::rotation_motor_b = 0;

// create motor object
RotaryEncoder my_encoder_a(2, 3,   MOTOR_A_SM);
RotaryEncoder my_encoder_b(26, 27, MOTOR_B_SM);

// variables to measure equal time between measurements
long previousMillis = 0;
long currentMillis = 0;
// print data every 0.1 s
int interval = 100;

// values to keep computing motor velocity
int last_rotation_a;
int last_rotation_b;


double Setpoint_a, Input_a, Output_a;
double Setpoint_b, Input_b, Output_b;
PID myPID_a(&Input_a, &Output_a, &Setpoint_a, 0.001, 0.001, 0.0, DIRECT);
PID myPID_b(&Input_b, &Output_b, &Setpoint_b, 0.001, 0.001, 0.0, DIRECT);


void setup() {
  // initialise serial port
  Serial.begin(115200); 
  
  // set initial reading of encoders to 0
  my_encoder_a.set_rotation(0);
  my_encoder_b.set_rotation(0); 

  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  myPID_a.SetMode(AUTOMATIC);
  myPID_b.SetMode(AUTOMATIC);
  Setpoint_a = 69.0;
  Setpoint_b = 420.0;
}
 
void loop() {
  // get current time
  currentMillis = millis();

  // check is measured interval has passed
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;

    // get encoder readings
    int current_rotation_a = my_encoder_a.get_rotation();
    int current_rotation_b = my_encoder_b.get_rotation();
    
    // print measurements
    printf("Motor A: %d\t", last_rotation_a - current_rotation_a);
    printf("Output:  %f\t", Output_a);
    printf("Motor B: %d\t", last_rotation_b- current_rotation_b);
    printf("Output:  %f",   Output_b);
    printf("\n");

    Input_a = double(last_rotation_a - current_rotation_a);
    myPID_a.Compute();
    analogWrite(10, int(Output_a*65535));

    Input_b = double(last_rotation_b - current_rotation_b);
    myPID_b.Compute();
    analogWrite(8, int(Output_b*65535));

    // update last values
    last_rotation_a = current_rotation_a;
    last_rotation_b = current_rotation_b;   

  }
}