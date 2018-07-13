#include <Servo.h>

//Sets up the servos
Servo joint[4]; //Creates 4 servos (0-3).
int pos[4];    //Create 4 variables that will store the position of each servo. 

byte firstByte; //Stores the first byte sent from Raspberry Pi. 
byte secondByte; //Stores the second byte sent from the Raspberry Pi
int endloop=1; //1 starts loop. 0 ends loop

void setup() {
  joint[0].attach(9); //y-axis 1
  joint[0].write(13); //default position for y-axis 1
  joint[1].attach(10); //y-axis 2
  joint[1].write(13); //default position for y-axis 2
  joint[2].attach(12); //x-axis
  joint[2].write(90); //default position for the x-axis motor
  joint[3].attach(11); //claw
  //need to set the default position to open once prongs are connected

  
 // Initalizes position variables
pos[0] = 13; //Position for y-axis (1) motor
pos[1] = 13; //Position for y-axis (2) motor
pos[2] = 13; //Position for x-axis motor
pos[3] = 180; //Position for claw
  
// sets the baud rate
Serial.begin(9600);
}



void loop() {
  //Checks to see if a byte has been sent
  if(Serial.available()){
    //Stores byte sent from Raspberry Pi 
    firstByte=Serial.read();
      //Test the byte sent from Raspberry Pi
      switch(firstByte){
        //moves y-axis (1) up.
        case '1':
        moveServoUp(1,0);
        break;
        //moves y-axis (1) up
        case '2':
        moveServoDown(1,0);
        break;
        //moves y-axis (2) up
        case '3':
        moveServoUp(1,1);
        break;
        case '4':
        moveServoDown(1,1);
        break;
        case '5':
        //make function to move x-axix right
        moveServoUp(1,2);
        break;
        case '6':
        //make function to move x-axis left
        moveServoDown(1,2);
        break;
        case '7':
        //make function to move claw
        openClaw();
        break;
        case '8':
        closeClaw();
        break;
      }
  }
}



void moveServoUp(int endloop, int x){
  //endloop=1; //Take out endloop parameter and replace with this TEST
  while(endloop==1){
      if(pos[x]<=120){
      pos[x]+=1;
      joint[x].write(pos[x]);
      delay(20);
        if(Serial.available()){
        secondByte=Serial.read();
        if(secondByte=='0'){
          endloop=0;
        }
      }
    }else{
      //Ends the loop if the servo reaches the max position (120)
      endloop=0;
    }
  }
}


void moveServoDown(int endloop, int x){
  //endloop=1; //Take out endloop parameter and replace with this TEST
  while(endloop==1){
      if(pos[x]>=13){
      pos[x]-=1;
      joint[x].write(pos[x]);
      delay(20);
        if(Serial.available()){
        secondByte=Serial.read();
        if(secondByte=='0'){
          endloop=0;
        }
      }
    }else{
      //Stops loop if the servo reaches the lowest position (13)
      endloop=0;
    }
  }
}





//A function that allows the servo to open completely so it can grip larger objects
void openClaw(){
  //endloop=1; //Take out endloop parameter and replace with this TEST
  while(endloop==1){
      if(pos[3]<=180){
      pos[3]+=1;
      joint[3].write(pos[3]);
      delay(20);
        if(Serial.available()){
        secondByte=Serial.read();
        if(secondByte=='0'){
          endloop=0;
        }
      }
    }else{
      //Ends the loop if the servo reaches the max position (180)
      endloop=0;
    }
  }
}
//A function that allows the claw servo to close completely so it can grip smaller objects
void closeClaw(){
  //endloop=1; //Take out endloop parameter and replace with this TEST
  while(endloop==1){
      if(pos[3]>=1){
      pos[3]-=1;
      joint[3].write(pos[3]);
      delay(20);
        if(Serial.available()){
        secondByte=Serial.read();
        if(secondByte=='0'){
          endloop=0;
        }
      }
    }else{
      //Stops loop if the servo reaches the lowest position (1)
      endloop=0;
    }
  }
}







//TEST
void servoTest(){
  for(int x=0; x<=180; x++){
        joint[2].write(x);
        Serial.println(x);
        delay(10);
     }
}
void serialTest2(){
  if(Serial.available()){
    firstByte = Serial.read();
    Serial.write(firstByte);
    Serial.println("");
  }
}






