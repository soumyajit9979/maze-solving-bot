
#include <Servo.h>          //Servo motor library
#include <NewPing.h>        //Ultrasonic sensor function library

//our L298N control pins

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2
#define RM1 6 
#define RM2 7
#define LM1 8
#define LM2 9
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  pinMode(RM1, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){     //if obstacle detected
    moveStop();
    delay(200);
    moveBackward();       //go back
    delay(400);
    moveStop();           //stop
    delay(200);
    distanceRight = lookRight();      //look at right and take the distance
    delay(300);
    distanceLeft = lookLeft();        //look at left and take the distance
    delay(300);

    if (distanceRight >= distanceLeft){    //if right disctance is more then it will turn right and stop 
      turnRight();
      moveStop();
    }
    else{                                   // or else it will turn left and then it will stop
      turnLeft();
      moveStop();
    }
  }
  else{                               //will continue moving forward
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){                //defining looking right and reading function
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){                 //defining looking left and reading function
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){               //defining reading distance function
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){            //stop function
  
  digitalWrite(RM1, LOW);
  digitalWrite(LM1, LOW);
  digitalWrite(RM2, LOW);
  digitalWrite(LM2, LOW);
}

void moveForward(){         //move forward function

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LM1, HIGH);
    digitalWrite(RM1, HIGH);
  
    digitalWrite(LM2, LOW);
    digitalWrite(RM2, LOW); 
  }
}

void moveBackward(){        //move backward function

  goesForward=false;

  digitalWrite(LM2, HIGH);
  digitalWrite(RM2, HIGH);
  
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  
}

void turnRight(){           //turn right function

  digitalWrite(LM1, HIGH);
  digitalWrite(RM2, HIGH);
  
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  
  delay(500);
  
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, HIGH);
  
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
 
  
  
}

void turnLeft(){          //turn left function

  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  
  digitalWrite(LM1, LOW);
  digitalWrite(RM2, LOW);

  delay(500);
  
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, HIGH);
  
  digitalWrite(LM2, LOW);
  digitalWrite(RM2, LOW);
}

 
