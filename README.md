[image1]: ./images/motor_controller.jpg
[image2]: ./images/L298N_simple.jpg

# Annex 04 : Motor Controller

As mentioned in Annex 01 and Annex 02, it is possible to connect motors directly to the pins of either an Arduino or a Raspberry Pi. The big issue with this solution is that the current that you can provide to the motor is limited to the current that the Arduino or the Raspberry Pi can provide and this limits a lot the motors that you can use. More specifically if you need to use a motor that requires higher voltage (9 volts for example), the you need to use a so-called motor controller.

You can think of a motor controller as a button that can close or open the circuit and between the motor and an external battery. The activation of the button can be controller through an Arduino for example.

## 01. The L298N Motor Controller

The L298N motor controller is a commonly used motor controller, also called H-bridge motor controller. The below image shows how a typical L298N motor controller looks like:

![alt text][image1]

The blue connectors are used to connect the external battery and the motor, whereas the black pins are used to connect the Arduino.

## 02. Arduino versus Raspberry Pi

Please notice that the H-bridge could have also been connected to a Raspberry Pi. The drawbacks of using the Raspberry Pi is that you only have one so-called PWM pin. A PWM pin is a pin that allows you to define output values in a certain range and not only output values of type 0 and 1. If a motor needs to be controlled with discrete values between full power and no power you need a PWM output. The other issue is that if used without external hardware you might experience jittering of the servo.

An Arduino on the other hand has more than one PWM and is extremely stable when controlling the L298N.

## 03. L298N Motor Controller assembly

![alt text][image2]

## 04. L298N Motor Controller Arduino code

What things you need to install the software and how to install them

```
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
```

#### Understanding the code

The **void setup()** function is run first with its content between brackets. The **Serial.begin(9600)** sets up the speed of the serial port to 9600 baud. The baud setting in the serial monitor window must match this value so that the Arduino and serial monitor window are communicating at the same speed.

The **void loop()** function is run second with all its content between brackets.
The **Serial.println("Hello, world!")** sends the text *Hello World!* to the serial / USB port for display in the serial monitor window.

## 05. Purchases and Downloads
The Arduino can be purchased from the following link:
[Purchase an Arduino here](https://store.arduino.cc/)

## Author

**Massimo Passamonti**: [email me](me@massimoslab.com)

## License

This project and its source code are licensed under the MIT License. [See MIT License](https://github.com/github/choosealicense.com/blob/gh-pages/LICENSE.md) file for more details.
