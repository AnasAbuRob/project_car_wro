
#include <Servo.h>

Servo myservo;

const byte echo_b=33;
const byte trig_b=32;
const byte echo_f=41;
const byte trig_f=40;
const byte echo_r=37;
const byte trig_r=36;
const byte echo_l=35;
const byte trig_l=34;

const byte motor_f = 6;
const byte motor_b = 7;
const byte motor_s = 9;
const byte servo = 10;
int counter_rotate = 0;
const byte start_Stop=3;



void stopProgram() {
    

      digitalWrite(motor_f, LOW);
      digitalWrite(motor_b, LOW);
      counter_rotate=0;
      myservo.write(38);
   
    
}

int get_destance(int pin_Trig, int pin_Echo)
{
  long Time;
  int Distance;
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);
  Time = pulseIn(pin_Echo, HIGH);
  Time = Time / 2;
  Distance = Time * 0.034;
  return Distance;


}
void right_or_left()
{
  int right=get_destance(trig_r, echo_r);
  delay(2);
  int left=get_destance(trig_l, echo_l);
  delay(2);
  int forward=get_destance(trig_f, echo_f);
  delay(2);
  if ( forward< 40)
  {
 
    if (( right+left ) > 200)
    {
      if (left > right)
      { if (counter_rotate<1){
         myservo.write(0);
          delay(1800);
          myservo.write(38);
      }
      else{
          myservo.write(0);
          delay(1500);
          myservo.write(38);}
      }

      else if (left < right)
      {
        if (counter_rotate<1){
       
          myservo.write(90);
          
        delay(1800);
         myservo.write(38);
        }
        else{
          myservo.write(90);
          
        delay(1500);
         myservo.write(38);
        }
          
    
      
        }
        


      }
   else
        {
   
          if (get_destance(trig_f, echo_f)<15)
          {
            digitalWrite(motor_f, LOW);
              delay(20);
            if (get_destance(trig_r, echo_r)>get_destance(trig_l, echo_l))
            {
              
              myservo.write(0);
              delay(100);
              digitalWrite(motor_b, HIGH);
              delay(1500);
               myservo.write(90);
               delay(100);
               digitalWrite(motor_f, HIGH);
               delay(1500);
               digitalWrite(motor_f,LOW);
               delay(100);
               myservo.write(38);
                delay(100);
               digitalWrite(motor_f,HIGH);
               
               
              
              
            
            
           
          }
          
           else
          {
            myservo.write(90);
              delay(100);
              digitalWrite(motor_b, HIGH);
              delay(1500);
               myservo.write(0);
               delay(100);
               digitalWrite(motor_f, HIGH);
               delay(1500);
               digitalWrite(motor_f,LOW);
               delay(100);
               myservo.write(38);
                delay(100);
               digitalWrite(motor_f,HIGH);
            
          }
          }
        }
    
      counter_rotate += 1;
    }
  }


void turn_right()
{
              myservo.write(0);
              delay(100);
              digitalWrite(motor_b, HIGH);
              delay(1500);
               myservo.write(90);
               delay(100);
               digitalWrite(motor_f, HIGH);
               delay(1500);
               digitalWrite(motor_f,LOW);
               delay(100);
               myservo.write(38);
                delay(100);
               digitalWrite(motor_f,HIGH);
               if(get_destance(trig_f, echo_f)<15){
                turn_left();
               }
}
void turn_left()
{
  myservo.write(90);
              delay(100);
              digitalWrite(motor_b, HIGH);
              delay(1500);
               myservo.write(0);
               delay(100);
               digitalWrite(motor_f, HIGH);
               delay(1500);
               digitalWrite(motor_f,LOW);
               delay(100);
               myservo.write(38);
                delay(100);
               digitalWrite(motor_f,HIGH);
               if(get_destance(trig_f, echo_f)<15){
                turn_right();
               }
  
}




void setup() {
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 100);
  myservo.attach(servo);
  myservo.write(38);

  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_b, OUTPUT);
  pinMode(echo_b, INPUT);
  pinMode(start_Stop, INPUT_PULLUP);
  Serial.begin(9600);

}


void loop() {
  
    if(digitalRead(start_Stop)==0)
    {   if (counter_rotate < 12)
      {
  
      digitalWrite(motor_f, HIGH);
      delay(100);
      right_or_left();
      if(Serial.available()>0)
        {
          String path=Serial.readStringUntil("\n");
          if (path=="red")
          {
            if (get_destance(trig_r, echo_r)<15){}
            else{turn_right();}
              
            }
           else if (path=="green")
          {
            if (get_destance(trig_l, echo_l)<15){}
            else{turn_left();}
          }
          }
            
          }
        
     
      if(digitalRead(start_Stop)==1)
      {
      stopProgram();
      }
    
   
           
      }
      else{

      stopProgram();
   
    }
    }
  
   
     
