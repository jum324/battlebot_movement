#include <Servo.h>

#define servoPin 3
#define joystickPin A0
Servo servo;

void setup(){
    servo.attach(servoPin);
    servo.writeMicroseconds(1500);
    pinMode(joystickPin, INPUT);

    delay(7000);
    Serial.begin(9600);
}

void loop(){
    int input = analogRead(joystickPin);
    if(input < 462){
        input = input + 50;
    }
    else if(input > 562){
        input = input - 50;
    }
    else{
        input = 512;
    }
    
    int pwmVal = map(input, 50, 973, 1000, 2000);
    Serial.println(input);
    Serial.println(pwmVal);
    servo.writeMicroseconds(pwmVal);
}
