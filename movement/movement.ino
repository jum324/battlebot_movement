#include <Servo.h>

#define motorRPin 5
#define motorLPin 6
#define motorBPin 9
#define motorTPin 10

int motorRFlip = 1;     //use these params to flip motor direction
int motorLFlip = 1;     // -1 or 1
int motorBFlip = 1;
int motorTFlip = 1;

Servo motorR;
Servo motorL;
Servo motorB;
Servo motorT;

#define LxPin A0 // left joystick (controls horizontal translation)
#define LyPin A1 // left joystick (controls vertical translation)
#define RxPin A2 // right joystick (controls rotation)
#define RevPin A3 //reverse toggle

int input_min = 1000;
int input_max = 2000;
int input_range = input_max-input_min;

int output_min = 1000;
int output_max = 2000;
int output_range = output_max-output_min;

int deadzone = 25; //input deadzone

int LxVal;
int LyVal;
int RxVal;
int RevVal;
int Rev;

int LmotorSpeed;
int RmotorSpeed;
int TmotorSpeed;
int BmotorSpeed;

bool off = false;

void setup() {
  motorR.attach(motorRPin);
  motorR.writeMicroseconds(1500);
  motorL.attach(motorLPin);
  motorL.writeMicroseconds(1500);
  motorB.attach(motorBPin);
  motorB.writeMicroseconds(1500);
  motorT.attach(motorTPin);
  motorT.writeMicroseconds(1500);

  pinMode(LxPin, INPUT);
  pinMode(LyPin, INPUT);
  pinMode(RxPin, INPUT);
  pinMode(RevPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  LxVal = pulseIn(LxPin, HIGH);         //receive signal from transmitter
  LyVal = pulseIn(LyPin, HIGH);
  RxVal = pulseIn(RxPin, HIGH);
  RevVal = pulseIn(RevPin, HIGH);
  Rev = (RevVal - 1500)/abs(RevVal - 1500);

  LxVal = deadzone_Remove(LxVal);       //remove deadzone from input and cast to output
  LyVal = deadzone_Remove(LyVal);
  RxVal = deadzone_Remove(RxVal);

  Serial.print("LxVal: ");
  Serial.println(LxVal);
  Serial.print("LyVal: ");
  Serial.println(LyVal);
  Serial.print("RxVal: ");
  Serial.println(RxVal);

  vertical_Translation(LyVal);  //calculate motor speed
  horizontal_Translation(LxVal);
  rotation(RxVal);
  
  motorprint();                 //adjust motor speed
  delay(250);
}

/**
 * @brief Controlling the speed and direction of the left and right wheels based on left joystick vertical displacement
 * 
 * @param ly Left joystick vertical value
 */
void vertical_Translation(int ly){
  LmotorSpeed = map(ly, -(input_range/2-deadzone), input_range/2-deadzone, output_min, output_max);
  RmotorSpeed = map(ly, -(input_range/2-deadzone), input_range/2-deadzone, output_min, output_max);
}

/**
 * @brief Controlling the speed and direction of the front and back wheels based on left joystick horizontal displacement
 * 
 * @param lx Left joystick horizontal value
 */
void horizontal_Translation(int lx){
  TmotorSpeed = map(lx, -(input_range/2-deadzone), input_range/2-deadzone, output_min, output_max);
  BmotorSpeed = map(lx, -(input_range/2-deadzone), input_range/2-deadzone, output_min, output_max);
}

/**
 * @brief Controlling the rotation of the robot based on right joystick horizontal displacement
 * 
 * @param rx Right joystick horizontal value
 */
void rotation(int rx){
  TmotorSpeed += map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -output_range/2, output_range/2);
  LmotorSpeed -= map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -output_range/2, output_range/2);
  BmotorSpeed -= map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -output_range/2, output_range/2);
  RmotorSpeed += map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -output_range/2, output_range/2);
}

void motorprint(){
  if(!off){
    Tmotor(TmotorSpeed);
    Lmotor(LmotorSpeed);
    Bmotor(BmotorSpeed);
    Rmotor(RmotorSpeed);
  }
  else{
    Tmotor((output_max+output_min)/2);
    Lmotor((output_max+output_min)/2);
    Bmotor((output_max+output_min)/2);
    Rmotor((output_max+output_min)/2);
  }
}

/**
 * @brief Remove deadzone from signal
 * 
 * @param val Joystick reading
 */
int deadzone_Remove(int val){
  if(val < input_min){                      //limit input to desire range
    val = input_min;
  }
  else if(val > input_max){
    val = input_max;
  }
  val = val - input_min - input_range/2;    //shifting middle value to 0
  if(val < -deadzone){                      //shifting the value below deadzone up
    val += deadzone;
  }
  else if(val > deadzone){                  //shifting the value above deadzone down
    val -= deadzone;
  }
  else{
    val = 0;                                //setting value within deadzone to 0
  }
  return val;
}

/**
 * @brief Adjust top motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Tmotor(int speed){
  if(speed > output_max){
    speed = output_max;
  }
  if(speed < output_min){
    speed = output_min;
  }
  speed = motorTFlip * Rev * (speed - (output_min+output_max)/2) + (output_min+output_max)/2;
  Serial.print("TmotorSpeed: ");
  Serial.println(speed);
  motorT.writeMicroseconds(speed);
}

/**
 * @brief Adjust left motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Lmotor(int speed){
  if(speed > output_max){
    speed = output_max;
  }
  if(speed < output_min){
    speed = output_min;
  }
  speed = motorLFlip * Rev * (speed - (output_min+output_max)/2) + (output_min+output_max)/2;
  Serial.print("LmotorSpeed: ");
  Serial.println(speed);
  motorL.writeMicroseconds(speed);
}

/**
 * @brief Adjust bottom motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Bmotor(int speed){
  if(speed > output_max){
    speed = output_max;
  }
  if(speed < output_min){
    speed = output_min;
  }
  speed = motorBFlip * Rev * (speed - (output_min+output_max)/2) + (output_min+output_max)/2;
  Serial.print("BmotorSpeed: ");
  Serial.println(speed);
  motorB.writeMicroseconds(speed);
}

/**
 * @brief Adjust right motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Rmotor(int speed){
  if(speed > output_max){
    speed = output_max;
  }
  if(speed < output_min){
    speed = output_min;
  }
  speed = motorRFlip * Rev * (speed - (output_min+output_max)/2) + (output_min+output_max)/2;
  Serial.print("RmotorSpeed: ");
  Serial.println(speed);
  motorR.writeMicroseconds(speed);
}
