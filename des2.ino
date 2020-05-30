+#include <Servo.h>
Servo myservo;
long duration;
float distancecm;
int pos = 0 ; 
int usPin = 2;
void setup(){
 pinMode(usPin, OUTPUT);
 digitalWrite(usPin, LOW);
 Serial.begin(9600);
 myservo.attach(3);
 myservo.write(0); 
 delay(1000);
}
void loop(){
 //Trigger the sensor with a 2 microsec HIGH pulse
 digitalWrite(usPin, HIGH);
 delayMicroseconds(2);
 digitalWrite(usPin, LOW);

 //21set pin as input to read pulse from sensor
 pinMode(usPin, INPUT);
 //obtain length of HIGH pulse in microseconds
 duration = pulseIn(usPin, HIGH);
 //Ping sensor returns HIGH output pulse that gives
 //the time required for the burst echo to return
 //back to the sensor
 //speed of sound travels at 340 (m/s) (0.034 cm/s)
 //Must divide by 2 since time received is time for
 //30sound wave to travel to and from object

 //Calculate distance in cms
 distancecm = duration*0.034/2.0; 
 if(distancecm <=60){
    Serial.write("Distance: ");
     Serial.println(distancecm);
     delay(200);
     pinMode(usPin, OUTPUT);
     digitalWrite(usPin,LOW); 
 if (0 < distancecm &&  distancecm<= 10) { 
     myservo.write(30);
     delay(200);

   }
 else if (10 < distancecm && distancecm <= 20){
     myservo.write(60);
     delay(200);  }
 else if (20 < distancecm && distancecm <= 30){
     myservo.write(90);
     delay(200); }
 else if (30 < distancecm  && distancecm <= 40){
     myservo.write(120);
     delay(200); }
 else if (40 < distancecm && distancecm <= 50){
     myservo.write(150);
     delay(200); }
 else if (50 < distancecm && distancecm <= 60){

     myservo.write(180);
     delay(200);    
 }
  
 }
   


}





 

