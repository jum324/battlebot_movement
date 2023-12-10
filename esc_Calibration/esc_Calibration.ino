#include <Servo.h>

#define servoPin 3
#define joystickPin A0
Servo servo;

void setup(){
    servo.attach(servoPin);
    servo.writeMicroseconds(1500);
    pinMode(joystickPin, INPUT);

    delay(7000);
}

void loop(){
    int pwmVal = map(analogRead(joystickPin), 0, 1023, 1000, 2000);
    servo.writeMicroseconds(pwmVal);
}
