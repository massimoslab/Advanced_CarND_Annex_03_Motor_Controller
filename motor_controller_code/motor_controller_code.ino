#include <Servo.h>
Servo steeringServo;

int enA = 6;
int in1 = 8;
int in2 = 7;
int servoPIN = 10;


void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  steeringServo.attach(servoPIN);
  steeringServo.write(90);
}

int step_total = 20;
int step_count = 0;

int throttle_max = 255;
int throttle_min = 0;
int throttle_step = (throttle_max - throttle_min) / step_total;

int steering_max = 130;
int steering_min = 50;
int steering_step = (steering_max - steering_min) / step_total;

int throttle_val = throttle_min;
int steering_val = steering_min;



void loop() {

  while(step_count < step_total) {
    analogWrite(enA, throttle_val);
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    throttle_val += throttle_step;

    steeringServo.write(steering_val);
    steering_val += steering_step;

    step_count += 1;
    delay(500);
  }


  while(step_count > 0) {
    analogWrite(enA, throttle_val);
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    throttle_val -= throttle_step;

    steeringServo.write(steering_val);
    steering_val -= steering_step;

    step_count -= 1;
    delay(500);
  }
}
