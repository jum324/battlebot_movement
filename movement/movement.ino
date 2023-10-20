// use Nano 33
#define RSpeedPin 2
#define RMotorDir1 3 // right motor
#define RMotorDir2 4
#define LSpeedPin 7
#define LMotorDir1 5 // left motor
#define LMotorDir2 6
#define BSpeedPin 8
#define BMotorDir1 9 // bottom motor
#define BMotorDir2 10
#define TSpeedPin 13
#define TMotorDir1 11 // top motor
#define TMotorDir2 12

#define LxPin A0 // left joystick (controls horizontal translation)
#define LyPin A1 // left joystick (controls vertical translation)
#define RxPin A2 // right joystick (controls rotation)
int input_min = 1000;
int input_max = 2000;
int input_range = input_max-input_min;

int deadzone = 50; //joystick deadzone

int LxVal;
int LyVal;
int RxVal;

int LmotorSpeed;
int RmotorSpeed;
int TmotorSpeed;
int BmotorSpeed;

bool off = false;

void setup() {
  pinMode(LSpeedPin, OUTPUT);
  pinMode(LMotorDir1, OUTPUT);
  pinMode(LMotorDir2, OUTPUT);
  
  pinMode(RSpeedPin, OUTPUT);
  pinMode(RMotorDir1, OUTPUT);
  pinMode(RMotorDir2, OUTPUT);

  pinMode(TSpeedPin, OUTPUT);
  pinMode(TMotorDir1, OUTPUT);
  pinMode(TMotorDir2, OUTPUT);

  pinMode(BSpeedPin, OUTPUT);
  pinMode(BMotorDir1, OUTPUT);
  pinMode(BMotorDir2, OUTPUT);
  
  pinMode(LxPin, INPUT);
  pinMode(LyPin, INPUT);
  
  pinMode(RxPin, INPUT);

  Serial.begin(9600);
}

void loop() {
//  LxVal = analogRead(LxPin);    //reading joystick input
//  LyVal = analogRead(LyPin);
//  RxVal = analogRead(RxPin);
  LxVal = pulseIn(LxPin, HIGH);
  LyVal = pulseIn(LyPin, HIGH);
  RxVal = pulseIn(RxPin, HIGH);

  LxVal = deadzone_Remove(LxVal);       //convert joystick input range to [-512, 511] and then remove deadzone
  LyVal = deadzone_Remove(LyVal);
  RxVal = deadzone_Remove(RxVal);

//  Serial.print("LxVal: ");
//  Serial.println(LxVal);
//  Serial.print("LyVal: ");
//  Serial.println(LyVal);
//  Serial.print("RxVal: ");
//  Serial.println(RxVal);

  vertical_Translation(LyVal);  //calculate motor speed
  horizontal_Translation(LxVal);
  rotation(RxVal);
  
  motorprint();                 //adjust motor speed
  delay(0);
}

/**
 * @brief Controlling the speed and direction of the left and right wheels based on left joystick vertical displacement
 * 
 * @param ly Left joystick vertical value
 */
void vertical_Translation(int ly){
  LmotorSpeed = map(ly, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
  RmotorSpeed = map(ly, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
}

/**
 * @brief Controlling the speed and direction of the front and back wheels based on left joystick horizontal displacement
 * 
 * @param lx Left joystick horizontal value
 */
void horizontal_Translation(int lx){
  TmotorSpeed = map(lx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
  BmotorSpeed = map(lx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
}

/**
 * @brief Controlling the rotation of the robot based on right joystick horizontal displacement
 * 
 * @param rx Right joystickhorizontal value
 */
void rotation(int rx){
  TmotorSpeed -= map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
  LmotorSpeed -= map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
  BmotorSpeed += map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
  RmotorSpeed += map(rx, -(input_range/2-deadzone), input_range/2-deadzone, -255, 255);
}

void motorprint(){
  if(!off){
    Tmotor(TmotorSpeed);
    Lmotor(LmotorSpeed);
    Bmotor(BmotorSpeed);
    Rmotor(RmotorSpeed);
  }
  else{
    Tmotor(0);
    Lmotor(0);
    Bmotor(0);
    Rmotor(0);
  }
}

/**
 * @brief Converting joystick reading to range [-512, 511], then remove middle deadzone
 * 
 * @param val Joystick reading
 */
int deadzone_Remove(int val){
  if(val < input_min){              //limit output
    val = input_min;
  }
  else if(val > input_max){
    val = input_max;
  }
  val = val - input_min - input_range/2;
  if(val < -deadzone){
    val += deadzone;
  }
  else if(val > deadzone){
    val -= deadzone;
  }
  else{
    val = 0;
  }
  return val;
}

/**
 * @brief Adjust top motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Tmotor(int speed){
  if(abs(speed) > 255){
    analogWrite(TSpeedPin, 255);
    Serial.print("TmotorSpeed: ");
    Serial.println(255);
  }
  else{
    analogWrite(TSpeedPin, abs(speed));
    Serial.print("TmotorSpeed: ");
    Serial.println(speed);
  }
  if(speed > 0){
    digitalWrite(TMotorDir1, HIGH);
    digitalWrite(TMotorDir2, LOW);
  }
  else if(speed < 0){
    digitalWrite(TMotorDir1, LOW);
    digitalWrite(TMotorDir2, HIGH);
  }
  else{
    digitalWrite(TMotorDir1, LOW);
    digitalWrite(TMotorDir2, LOW);
  }
}

/**
 * @brief Adjust left motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Lmotor(int speed){
  if(abs(speed) > 255){
    analogWrite(LSpeedPin, 255);
    Serial.print("LmotorSpeed: ");
    Serial.println(255);
  }
  else{
    analogWrite(LSpeedPin, abs(speed));
    Serial.print("LmotorSpeed: ");
    Serial.println(speed);
  }
  if(speed < 0){
    digitalWrite(LMotorDir1, LOW);
    digitalWrite(LMotorDir2, HIGH);
  }
  else if(speed > 0){
    digitalWrite(LMotorDir1, HIGH);
    digitalWrite(LMotorDir2, LOW);
  }
  else{
    digitalWrite(LMotorDir1, LOW);
    digitalWrite(LMotorDir2, LOW);
  }
}

/**
 * @brief Adjust bottom motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Bmotor(int speed){
  if(abs(speed) > 255){
    analogWrite(BSpeedPin, 255);
    Serial.print("BmotorSpeed: ");
    Serial.println(255);
  }
  else{
    analogWrite(BSpeedPin, abs(speed));
    Serial.print("BmotorSpeed: ");
    Serial.println(speed);
  }
  if(speed > 0){
    digitalWrite(BMotorDir1, LOW);
    digitalWrite(BMotorDir2, HIGH);
  }
  else if(speed < 0){
    digitalWrite(BMotorDir1, HIGH);
    digitalWrite(BMotorDir2, LOW);
  }
  else{
    digitalWrite(BMotorDir1, LOW);
    digitalWrite(BMotorDir2, LOW);
  }
}

/**
 * @brief Adjust right motor speed and direction based on param speed
 * 
 * @param speed motor speed
 */
void Rmotor(int speed){
  if(abs(speed) > 255){
    analogWrite(RSpeedPin, 255);
    Serial.print("RmotorSpeed: ");
    Serial.println(255);
  }
  else{
    analogWrite(RSpeedPin, abs(speed));
    Serial.print("RmotorSpeed: ");
    Serial.println(speed);
  }
  if(speed < 0){
    digitalWrite(RMotorDir1, HIGH);
    digitalWrite(RMotorDir2, LOW);
  }
  else if(speed > 0){
    digitalWrite(RMotorDir1, LOW);
    digitalWrite(RMotorDir2, HIGH);
  }
  else{
    digitalWrite(RMotorDir1, LOW);
    digitalWrite(RMotorDir2, LOW);
  }
}
