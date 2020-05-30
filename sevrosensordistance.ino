  #include <Servo.h>

Servo servoRight;
Servo servoLeft;

int pos = 0;
byte pinFeedbackRight = 9;
byte pinFeedbackLeft = 10;
byte pinServoRight = 5;
byte pinServoLeft = 6;
unsigned long highRight = 0, highLeft = 0;
unsigned long lowRight = 0, lowLeft = 0;
char keyCommand;
double dutyCycleRight = 0.0, dutyCycleLeft = 0.0;
unsigned long cycleTimeRight, cycleTimeLeft;
double totalCycle = 1098.901;
double thetaRight = 0.0, thetaLeft = 0.0;
double thetaRightPrev = 0.0, thetaLeftPrev = 0.0;
int turnsRight = 0, turnsLeft = 0;
double deltaThetaRight = 0, deltaThetaLeft = 0   ;
double totalThetaRight = 0, totalThetaLeft = 0;
int PcontrolRight = 0, PcontrolLeft = 0;
int CW = 88; 
int CCW =96 ; 

void calculateThetaRight();
void calculateThetaLeft();
void Pcontroller(int dir);
void printInfos();

void setup(){
  Serial.begin(9600);
  pinMode(pinFeedbackRight, INPUT);
  pinMode(pinFeedbackLeft, INPUT);
  } 

void loop(){
   
  if (Serial.available() > 0){
    keyCommand = Serial.read();
    
    switch(keyCommand){
      case 'f': 
        servoRight.attach(pinServoRight);
        servoLeft.attach(pinServoLeft);
          servoRight.write(CW + PcontrolRight);
          servoLeft.write (CCW + PcontrolLeft);
          delay(9200);
          servoRight.detach();
          servoLeft.detach();
          Pcontroller(1);
           
        break;
      case 'b': 
        servoRight.attach(5);
        servoLeft.attach(6);
        servoRight.write(CCW+ PcontrolRight);
        servoLeft.write(CW + PcontrolLeft);
        delay(9625);
        servoRight.detach();
        servoLeft.detach();
        Pcontroller(-1);
        break;
      case 'l': 
        servoRight.attach(5);
        servoLeft.attach(6);
        servoRight.write(CCW + PcontrolRight);
        servoLeft.write (CCW + PcontrolLeft);
        delay(3050);
        servoRight.detach();
        servoLeft.detach();
        Pcontroller(-2);
         
        break;
      case 'r': 
        servoRight.attach(5);
        servoLeft.attach(6);
        servoRight.write(CW + PcontrolRight);
        servoLeft.write (CW + PcontrolLeft);
        delay(3050);
        servoRight.detach();
        servoLeft.detach();
        Pcontroller(2);
       
        break;
      case 'q':  
     for ( int x = 0 ; x < 8 ; x++){
      //Forwards
        servoRight.attach(pinServoRight);
        servoLeft.attach(pinServoLeft);
          servoRight.write(CW + PcontrolRight);
          servoLeft.write (CCW + PcontrolLeft);
          delay(9200);
 
          Pcontroller(1);
 
        servoRight.write(CCW + PcontrolRight);
        servoLeft.write (CCW + PcontrolLeft);
        delay(3050);
        servoRight.detach();
        servoLeft.detach();
        Pcontroller(-2);  
     }
      break; 

      case 's': 
        servoRight.attach(5);
        servoLeft.attach(6);
        servoRight.write(94);
        servoLeft.write(94);
        delay(500);
        servoRight.detach();
        servoLeft.detach();
        break;
      default: break;
      
    }   
  }

}

void Pcontroller(int dir){
   switch(dir){ 
   case 1 : 
   if (deltaThetaRight > deltaThetaLeft) {
      PcontrolRight = 0; 
      PcontrolLeft = 1 ; 
   }
   else if ( deltaThetaRight < deltaThetaLeft){
    PcontrolRight = -1; 
    PcontrolLeft = 0 ; 
   }
   else {
    PcontrolRight = 0; 
    PcontrolLeft  = 0 ; 
   } 
   break; 
   case -1 :
   if (deltaThetaRight > deltaThetaLeft) {
      PcontrolRight = 0; 
      PcontrolLeft = -1 ; 
   }
   else if ( deltaThetaRight < deltaThetaLeft){
    PcontrolRight = 1; 
    PcontrolLeft = 0 ; 
   }
   else {
    PcontrolRight = 0; 
    PcontrolLeft  = 0 ; 
   }  
   break;
     case 2 :
   if (deltaThetaRight > deltaThetaLeft) {
      PcontrolRight = 0; 
      PcontrolLeft = -1 ; 
   }
   else if ( deltaThetaRight < deltaThetaLeft){
    PcontrolRight = -1; 
    PcontrolLeft = 0 ; 
   }
   else {
    PcontrolRight = 0; 
    PcontrolLeft  = 0 ; 
   }  
   break;
     case -2 :
   if (deltaThetaRight > deltaThetaLeft) {
      PcontrolRight = 1; 
      PcontrolLeft =  0; 
   }
   else if ( deltaThetaRight < deltaThetaLeft){
    PcontrolRight = 1; 
    PcontrolLeft = 0 ; 
   }
   else {
    PcontrolRight = 0; 
    PcontrolLeft  = 0 ; 
   }  
   break;

   default : break; 
   }
   
   calculateThetaRight();
   calculateThetaLeft();
   printInfos();
   delay(1203); 
}

void printInfos(){
  Serial.print("ThetaRight: ");
  Serial.print(thetaRight);
  Serial.print(" , ThetaLeft: ");
  Serial.println(thetaLeft);
  Serial.print("deltaThetaRight: ");       
  Serial.print(deltaThetaRight);
  Serial.print(" , deltaThetaLeft: ");       
  Serial.println(deltaThetaLeft);
  Serial.print("totalThetaRight: ");         
  Serial.print(totalThetaRight);
  Serial.print(" , totalThetaLeft: ");       
  Serial.println(totalThetaLeft);
  Serial.print("PcontrolRight: ");         
  Serial.print(PcontrolRight);
  Serial.print(" , PcontrolLeft: ");       
  Serial.println(PcontrolLeft);
  Serial.print(" , turnsRight : ");       
  Serial.println(turnsRight);
  Serial.print(" , turnsLeft : ");       
  Serial.println(turnsLeft);

}
void calculateThetaRight(){ 
 
while(1)  {
  lowRight = pulseIn(pinFeedbackRight , 0);
  highRight = pulseIn(pinFeedbackRight , 1); // Measure high pulse
  lowRight = pulseIn(pinFeedbackRight , 0);
  cycleTimeRight = highRight + lowRight; 
  
  if ( cycleTimeRight > 900 && cycleTimeRight < 1200)
    {
      break; //valid tCycle;
    }
  }
  dutyCycleRight = 100 * highRight / cycleTimeRight ;
  thetaRight = (360.0 - 1.0) - ((dutyCycleRight - 2.9) * 360.0) / ( 97.1 - 2.9 + 1);
  if (thetaRight < 0 ) 
      thetaRight =0; 
  else if(thetaRight > 359.0) 
       thetaRight = 359.0; 


  deltaThetaRight = thetaRight - thetaRightPrev  ; 
  if ( deltaThetaRight < 0 ) { deltaThetaRight = -1 * deltaThetaRight ;}
  
  
   
  totalThetaRight = totalThetaRight + deltaThetaRight ;
  turnsRight = totalThetaRight/360.0; 
  thetaRightPrev = thetaRight ;
   
}
 
void calculateThetaLeft(){
    

   while(1)  
  {
       lowLeft = pulseIn(pinFeedbackLeft , 0);
       highLeft = pulseIn(pinFeedbackLeft , 1);  
       lowLeft = pulseIn(pinFeedbackLeft , 0);
       cycleTimeLeft = highLeft + lowLeft; 
    if ( cycleTimeLeft > 900 && cycleTimeLeft < 1200)
    {
      break; //valid tCycle;
    }
  }
  dutyCycleLeft = 100* highLeft/ cycleTimeLeft;
  thetaLeft = (360.0 - 1.0) - ((dutyCycleLeft - 2.9) * 360.0) / ( 97.1 - 2.9 + 1);
  if(thetaLeft < 0 ) 
      thetaLeft =0; 
  else if (thetaLeft > 359.0) 
       thetaLeft  = 359.0; 
 
deltaThetaLeft = thetaLeft - thetaLeftPrev  ;
 if ( deltaThetaLeft < 0 ) { deltaThetaLeft = -1 * deltaThetaLeft ;} 
 
totalThetaLeft = totalThetaLeft + deltaThetaLeft ; 
turnsLeft = totalThetaLeft / 360.0 ; 
thetaLeftPrev = thetaLeft  ;
}


