#include <Servo.h>

Servo myservo;

const byte echo_b = 33;
const byte trig_b = 32;
const byte echo_f = 41;
const byte trig_f = 40;
const byte echo_r = 37;
const byte trig_r = 36;
const byte echo_l = 35;
const byte trig_l = 34;

const byte motor_f = 6;
const byte motor_b = 7;
const byte motor_s = 9;
const byte servo = 10;
int counter_rotate = 0;
const byte start_Stop = 3;
int right1;
int left1;
int c=0;



void stopProgram() {


  digitalWrite(motor_f, LOW);
  digitalWrite(motor_b, LOW);
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

void Correct_path()
{
  int right2=get_destance(trig_r, echo_r);
  int left2=get_destance(trig_l, echo_l);
  int forword=get_destance(trig_f, echo_f);
 
  if ((right2+left2)<120){
    if(forword>65){
    if ((right1-right2)>5 || (left1-left2<-5 ))
        {
          myservo.write(25);
          delay(100);
           myservo.write(38);
           delay(15);
           if (get_destance(trig_f, echo_f)<20){
                digitalWrite(motor_f,LOW);
                 delay(15);
                 digitalWrite(motor_b,HIGH);
                  analogWrite(motor_s,100);
                 delay(2000);
                 digitalWrite(motor_b,LOW);
                 delay(15);
                 digitalWrite(motor_f,HIGH);
                 
                  analogWrite(motor_s,85);
      }
          
        }
        else if ((right1-right2)<-5 || (left1-left2>5))
        {
          myservo.write(51);
          delay(100);
           myservo.write(38);
           delay(15);
           if (get_destance(trig_f, echo_f)<20){
                digitalWrite(motor_f,LOW);
                 delay(15);
                 digitalWrite(motor_b,HIGH);
                  analogWrite(motor_s,100);
                 delay(2000);
                 digitalWrite(motor_b,LOW);
                 delay(15);
                 digitalWrite(motor_f,HIGH);
                 
                  analogWrite(motor_s,85);
        }

       
    
    }

}
}
}


void right_or_left()
{
  int right = get_destance(trig_r, echo_r);
  int left = get_destance(trig_l, echo_l);
  int forward = get_destance(trig_f, echo_f);

    if (( right + left ) > 200)
    {  
      if (left > right)
      { 
        if (60>forward >30)
       
        {
          myservo.write(0);
         analogWrite(motor_s,100);

        delay(1500);
        
        myservo.write(38);
        analogWrite(motor_s,85);
        delay(1000);
        
          
         
         
      }
      else if (forward<20){
        digitalWrite(motor_f,LOW);
         delay(15);
         digitalWrite(motor_b,HIGH);
          analogWrite(motor_s,100);
         delay(2000);
         digitalWrite(motor_b,LOW);
         delay(15);
         digitalWrite(motor_f,HIGH);
         
          analogWrite(motor_s,85);
      }
          
        
        
        
        
       

        
  
          
      }


      else if (left < right)
      {
         
        if (60>forward >30)
       
        {
          myservo.write(90);
         analogWrite(motor_s,100);

        delay(1500);
        
        myservo.write(38);
        analogWrite(motor_s,85);
        delay(1000);
        
          
         
         
      }
      else if (forward<20){
        digitalWrite(motor_f,LOW);
         delay(15);
         digitalWrite(motor_b,HIGH);
          analogWrite(motor_s,100);
         delay(2000);
         digitalWrite(motor_b,LOW);
         delay(15);
         digitalWrite(motor_f,HIGH);
         
          analogWrite(motor_s,85);
      }



    }
  
    counter_rotate += 1;
  }
}









void setup() {
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 90);
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

  if (digitalRead(start_Stop) == 0)

  { 
    if (counter_rotate < 12)
    {
      if (c==0){
           right1= get_destance(trig_r, echo_r);
            left1 = get_destance(trig_l, echo_l);
            c+=1;
      }
      digitalWrite(motor_f,HIGH);
     right_or_left();
     Correct_path();
     
      

      if (digitalRead(start_Stop) == 1)
      {
        
        stopProgram();
      
      }



    }
    else {

      stopProgram();
      if (digitalRead(start_Stop) == 0)
      {
        counter_rotate=0;
        
      }
        

    }
  }

  else {

    stopProgram();
      if (digitalRead(start_Stop) == 0)
      {
        counter_rotate=0;
        
      }

  }






}
