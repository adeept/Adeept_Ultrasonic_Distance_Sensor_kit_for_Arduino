/***********************************************************
File name: 17_ServoAndUltrasonicDistanceSensor.ino
Description: we program Arduino UNO to control a servo with
             ultrasonic distance sensor.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2015/05/02 
***********************************************************/
#include <Servo.h>
Servo myservo;          //create servo object to control a servo
const int pingPin = 5;  // Digital pin 5 connected to Echo(UltrasonicDistanceSensor) 
const int trigPin  = 7; // Digital pin 7 connected to Trig(UltrasonicDistanceSensor) 

int angle = 0;//Recorded the angle information of the servo
void setup()
{
  pinMode(pingPin, INPUT); //Set the pingPin to output mode 
  pinMode(trigPin, OUTPUT);//Set the trigPin to output mode 
  myservo.attach(9);//attachs the servo on pin 9 to servo object
  myservo.write(0); //back to 0 degrees 
  delay(1000);      //wait for a second
}

void loop()
{   
   int cm = ping(pingPin) ; //Read the distance information
   if(cm>=180){ //We set the distance for less than 180 cm
     cm = 180;
   }
   //Let the cat is gradually moved
   if(angle>cm){
     angle--;
   }else if(angle<cm){
     angle++;
   }else{
     angle = cm;
   }
   myservo.write(angle);//back to 'angle' degrees(0 to 180)
   delay(10);//control servo speed
}
int ping(int pingPin) 
{ 
   // establish variables for duration of the ping, 
   // and the distance result in inches and centimeters: 
   long duration, cm; 
   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds. 
   // Give a short LOW pulse beforehand to ensure a clean HIGH pulse: 
   pinMode(trigPin, OUTPUT); 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(5); 
   digitalWrite(trigPin, LOW); 
   pinMode(pingPin, INPUT); 
   duration = pulseIn(pingPin, HIGH); 
   // convert the time into a distance 
   cm = microsecondsToCentimeters(duration); 
   return cm ; 
} 

long microsecondsToCentimeters(long microseconds) 
{ 
   // The speed of sound is 340 m/s or 29 microseconds per centimeter. 
   // The ping travels out and back, so to find the distance of the 
   // object we take half of the distance travelled. 
   return microseconds / 29 / 2; 
} 
