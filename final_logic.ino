#include <Servo.h>          //Servo motor library. This is standard library

//our L298N/motor control  pins
const int LeftMotorForward = 9; 
const int LeftMotorBackward = 8; 
const int RightMotorForward = 11; 
const int RightMotorBackward = 10; 
// set speed if you use supported motor controll
//const int ena = 6; 
//const int enb = 5;

// ultra wave sensor
#define trigPin 2 
#define echoPin 3
#define angle 60

#define min_distance 40
boolean goesForward = false;
int distance;
// defines variables
long duration; // variable for the duration of sound wave travel

Servo servo_motor; //our servo name

void setup(){
  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
Serial.begin(9600);
  
// set speed if you use supported motor controll
// pinMode(ena, OUTPUT);
// pinMode(enb, OUTPUT);
//   analogWrite(ena, 200);  // chinh toc do dong co ben trai
// analogWrite(enb, 200); // chinh toc do dong co ben trai
  
  moveStop();
  delay(2000);
  servo_motor.attach(5); //our servo pin
  servo_motor.write(90);
  
  delay(4000); // help with failed code upload

  distance = readPing();

  
}

void loop(){
    distance = lookStraight();   
  if (distance <= min_distance){
    moveStop();
    findNewPath();
  } else {
    moveForward();
  }
 
}

void findNewPath() {
  int turned = 0; 
  
  while (turned == 0) {
    if (lookRight() > min_distance) {
      moveStop();  
      turnRight();
      moveStop();
      turned =1; 
    }
    else if (lookLeft() > min_distance) {
      
      moveStop();
      turnLeft();
      moveStop();
      turned = 1;
    }
    else { // in case you can't go left or right
      moveStop();
     moveBackward(); 
     lookStraight();
     moveStop(); 
    }
  }
   
}

int lookRight(){  
  servo_motor.write(90-angle);
  
  delay(500);
  int distance = readPing();
  
  return distance;
}

int lookLeft(){ 
  servo_motor.write(90+angle);
  delay(500);
  int distance = readPing();
  
  return distance;
}

int lookStraight(){
  int distance;
  if (servo_motor.read() == 90)
  {
   distance = readPing();
  } else {
   moveStop();
  servo_motor.write(90);
  
  delay(500);
  distance = readPing(); 
  }
  
  return distance;
}

int readPing(){
  // clear condition trigpin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  delay(100);
  // Calculating the distance
  distance = (duration+10) * 0.0343 / 2; // Speed of sound wave divided by 2 (go and back), 343m/s
  return distance;
}


void moveForward(){ 
  
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
    delay(200);
}

void moveBackward(){

  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(300);
  moveStop();
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(250); // tune this to arround 60 degree turning 
  //to match with servo turn degree
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250); 
}

void moveStop() {
    digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
