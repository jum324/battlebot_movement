#include <Servo.h>

byte servoPin 3;
byte joystickPin A0;
Servo servo;

void setup(){
    servo.attach(servoPin);
    servo.writeMicroseconds(1500);
    pinMode(joystickPin, INPUT);

    delay(7000);
}

void loop(){
    int pwmVal = map(analogRead(joystickPin), 0, 1023, 1100, 1900);
    servo.writeMicroseconds(pwmVal);
}