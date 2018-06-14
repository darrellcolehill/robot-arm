#include "PushButtons.h"
#include <Servo.h>

Servo joint[4]; //create 4 servos (0-3)
byte digitalPins[] = {5, 6, 7, 8}; //You can select other digital pins, if you like
byte firstPush;
byte secondPush;
int endloop;
int degree;
PushButtons buttons(digitalPins, sizeof(digitalPins));

void moveServo(int endloop, int axis){
  endloop=0;
 while(endloop==0){
      /* //Converts the analog value (which goes from 0 - 1023) to a degree (0 - 180) rounded to the nearest hundreth
      float degree = sensorValue * (180.0 / 1023.0);
       int sensorValue = analogRead(A0);
       */
       //Converts the analog value (which goes from 0 - 1023) to a degree (0 - 180) rounded to the nearest one
          degree = analogRead(A0);
          degree = map(degree, 0.00, 1023.00, 0, 180.00);
        Serial.println(degree);
        joint[axis].write(degree);
        delay(15);
        
        secondPush=buttons.checkButtons();
        if(secondPush==firstPush){
          endloop = 1;
          Serial.println("stopped");
        }
    }
}





void setup() {  
  buttons.init();
  joint[0].attach(9);  //y-axis 1
  joint[0].write(13);  //default position for y-axis 1
  joint[1].attach(10); //y-axis 2
  joint[1].write(13);  //default position for y-axis 2
  joint[2].attach(11); //claw
  joint[3].attach(12); //x-axis 1
  
  // Sets baud rate for comunication with the serial monitor
  Serial.begin(9600);
}



void loop() {

  endloop = 0;  
  firstPush=buttons.checkButtons();

  switch(firstPush){
    case 1:
      moveServo(0, 0);
    break;

    case 2:
      moveServo(0, 1);
    break;

    case 3:
      moveServo(0, 2);
    break;
  }
}
