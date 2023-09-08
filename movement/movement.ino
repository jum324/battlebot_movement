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

int LxVal;
int LyVal;
int RxVal;

int bound = 100; //joystick deadzone

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
  // put your main code here, to run repeatedly:

}

/**
 * @brief Controlling the speed and direction of the left and right wheels based on left joystick vertical displacement
 * 
 * @param ly Left joystick vertical value
 */
void vertical_Translation(int ly){
  
}

/**
 * @brief Controlling the speed and direction of the front and back wheels based on left joystick horizontal displacement
 * 
 * @param lx Left joystick horizontal value
 */
void horizontal_Translation(int lx){

}

/**
 * @brief Controlling the rotation of the robot based on right joystick horizontal displacement
 * 
 * @param rx Right joystickhorizontal value
 */
void rotation(int rx){

}

void motorprint(){

}