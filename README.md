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

The assembly and connection of the L298N motor controller to the Arduino Micro and to the car chassis is relatively simple. Refer to the below schematic for the details:

![alt text][image2]

First, start by connecting the car's motor and steering servo to the H-bridge. Secondly, add an external power sources here represented by a 9V battery. Please notice that any power source between 6V and 12V works with the motor. Thirdly, connect the Arduino Micro to the H-bridge using pin 6, pin 7 and pin 8 and to the steering servo through pin 10.

## 04. L298N Motor Controller Arduino code

Below is a simple Arduino code that once uploaded to the Arduino Micro will activate the motor and the steering servo.

There are two loops in the code. The first loop will increase through different steps:
1. the throttle of the motors from zero to full throttle; and
2. the steering angle from left to right.

The second loop will decrease through different steps:
1. the throttle of the motors from full to zero throttle; and
2. the steering angle from right to left.


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

In the **void setup()** function we set up the speed of the serial port to 9600 baud, we connect the motor to the appropriate pins (pin 6, 7 and 8), and we connect the servo to its pin (pin 10).

Before the **void loop()** function we define a series of variables that are later used to determine the increases of the throttle and of the steering angle.

In the **void loop()** function we send the signal to the motor and to the steering servo.

The **analogWrite()** function send the throttle value to the motor. The two **digitalWrite()** functions determine the rotational direction of the motor.

The **steeringServo.write()** function sends the steering angle value to the servo.

## 05. Purchases

L298N motor controller can be purchased online on the major online stores. I have purchased mine from ebay:
[Purchase a car chassis here](https://store.arduino.cc/)

## Author

**Massimo Passamonti**: [email me](me@massimoslab.com)

## License

This project and its source code are licensed under the MIT License. [See MIT License](https://github.com/github/choosealicense.com/blob/gh-pages/LICENSE.md) file for more details.
