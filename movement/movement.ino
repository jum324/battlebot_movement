// use Nano 33
#define RSpeedPin 3
#define RMotorDir1 2 // right motor
#define RMotorDir2 4
#define LSpeedPin 5
#define LMotorDir1 6 // left motor
#define LMotorDir2 7
#define TSpeedPin 9
#define TMotorDir1 8 // top motor
#define TMotorDir2 10
#define BSpeedPin 11
#define BMotorDir1 12 // bottom motor
#define BMotorDir2 13

#define LxPin A0 // left joystick (controls horizontal translation)
#define LyPin A1 // left joystick (controls vertical translation)
#define RxPin A2 // right joystick (controls rotation)

int deadzone = 100; //joystick deadzone

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
  LxVal = analogRead(LxPin);
  LyVal = analogRead(LyPin);
  RxVal = analogRead(RxPin);

  deadzone_Remove(LxVal);
  deadzone_Remove(LyVal);
  deadzone_Remove(RxVal);

}

/**
 * @brief Controlling the speed and direction of the left and right wheels based on left joystick vertical displacement
 * 
 * @param ly Left joystick vertical value
 */
void vertical_Translation(int ly){
  LmotorSpeed = ly*255/(511-deadzone);
  RmotorSpeed = ly*255/(511-deadzone);
}

/**
 * @brief Controlling the speed and direction of the front and back wheels based on left joystick horizontal displacement
 * 
 * @param lx Left joystick horizontal value
 */
void horizontal_Translation(int lx){
  TmotorSpeed = lx*255/(511-deadzone);
  BmotorSpeed = lx*255/(511-deadzone);
}

/**
 * @brief Controlling the rotation of the robot based on right joystick horizontal displacement
 * 
 * @param rx Right joystickhorizontal value
 */
void rotation(int rx){
  TmotorSpeed += rx*255/(511-deadzone);
  LmotorSpeed += rx*255/(511-deadzone);
  BmotorSpeed -= rx*255/(511-deadzone);
  RmotorSpeed -= rx*255/(511-deadzone);
}

void motorprint(){

}

/**
 * @brief Converting joystick reading to range [-512, 511], then remove middle deadzone
 * 
 * @param val Joystick reading
 */
void deadzone_Remove(int val){
  val -= 512;
  if(val < -deadzone){
    val += deadzone;
  }
  else if(val > deadzone){
    val -= deadzone;
  }
  else{
    val = 0;
  }
}

/**
 * @brief Adjust top motor speed and direction based on global variable TmotorSpeed
 * 
 */
void Tmotor(){
  analogWrite(TSpeedPin, abs(TmotorSpeed));
  if(TmotorSpeed > 0){
    digitalWrite(TMotorDir1, LOW);
    digitalWrite(TMotorDir2, HIGH);
  }
  else if(TmotorSpeed < 0){
    digitalWrite(TMotorDir1, HIGH);
    digitalWrite(TMotorDir2, LOW);
  }
  else{
    digitalWrite(TMotorDir1, LOW);
    digitalWrite(TMotorDir2, LOW);
  }
}

/**
 * @brief Adjust left motor speed and direction based on global variable LmotorSpeed
 * 
 */
void Lmotor(){
  analogWrite(LSpeedPin, abs(LmotorSpeed));
  if(LmotorSpeed > 0){
    digitalWrite(LMotorDir1, LOW);
    digitalWrite(LMotorDir2, HIGH);
  }
  else if(LmotorSpeed < 0){
    digitalWrite(LMotorDir1, HIGH);
    digitalWrite(LMotorDir2, LOW);
  }
  else{
    digitalWrite(LMotorDir1, LOW);
    digitalWrite(LMotorDir2, LOW);
  }
}

/**
 * @brief Adjust bottom motor speed and direction based on global variable BmotorSpeed
 * 
 */
void Bmotor(){
  analogWrite(BSpeedPin, abs(BmotorSpeed));
  if(BmotorSpeed > 0){
    digitalWrite(BMotorDir1, HIGH);
    digitalWrite(BMotorDir2, LOW);
  }
  else if(BmotorSpeed < 0){
    digitalWrite(BMotorDir1, LOW);
    digitalWrite(BMotorDir2, HIGH);
  }
  else{
    digitalWrite(BMotorDir1, LOW);
    digitalWrite(BMotorDir2, LOW);
  }
}

/**
 * @brief Adjust right motor speed and direction based on global variable RmotorSpeed
 * 
 */
void Rmotor(){
  analogWrite(RSpeedPin, abs(RmotorSpeed));
  if(RmotorSpeed > 0){
    digitalWrite(RMotorDir1, HIGH);
    digitalWrite(RMotorDir2, LOW);
  }
  else if(RmotorSpeed < 0){
    digitalWrite(RMotorDir1, LOW);
    digitalWrite(RMotorDir2, HIGH);
  }
  else{
    digitalWrite(RMotorDir1, LOW);
    digitalWrite(RMotorDir2, LOW);
  }
}