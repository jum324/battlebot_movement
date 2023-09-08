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
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void vertical_Translation(int ly){
  
}

void horizontal_Translation(int ly){

}

void rotation(int rx){

}

void motorprint(){
  
}