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
long wait=0;
int c=0;
const byte ir_right=18;
const byte ir_left=19;
long ir_turn=0;




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
  int right=get_destance(trig_r, echo_r);
  int left=get_destance(trig_l, echo_l);
  int forword=get_destance(trig_f, echo_f);
  int center=(right+left)/2;
  if(forword>40)
  { 
  if (center>right+5 && abs (center-right)<80)
    {
       myservo.write(23);
       wait=millis();
       while(millis()-wait<1000)
          {
            right=get_destance(trig_r, echo_r);
            left=get_destance(trig_l, echo_l);
            center=(right+left)/2;
            
            if (center<right && abs (center-right)<80) 
            {
              myservo.write(38);
              break;
              
              
            }
            if (digitalRead(ir_right)==0)
            {
              myservo.write(38);
             digitalWrite(motor_f,LOW);
             delay(15);
             digitalWrite(motor_b,HIGH);
              analogWrite(motor_s,100);
             ir_turn=millis();
             while(millis()-ir_turn<1000)
             {        
             }
             digitalWrite(motor_b,LOW);
             myservo.write(23);
             delay(15);
             digitalWrite(motor_f,HIGH);
             ir_turn=millis();
             while(millis()-ir_turn<700)
             {
              forword=get_destance(trig_f, echo_f);
              if ( forword<20)
              {
                break;     
              }
             }
              analogWrite(motor_s,85);
              myservo.write(38);
            }
            if (digitalRead(ir_left)==0)
            {
               myservo.write(38);
               digitalWrite(motor_f,LOW);
             delay(15);
             digitalWrite(motor_b,HIGH);
              analogWrite(motor_s,100);
             ir_turn=millis();
             while(millis()-ir_turn<1000)
             {
              }
             digitalWrite(motor_b,LOW);
             myservo.write(53);
             delay(15);
             digitalWrite(motor_f,HIGH);
             ir_turn=millis();
             while(millis()-ir_turn<700)
             {
              forword=get_destance(trig_f, echo_f);
              if ( forword<20)
              {
                break;     
              }
             }
              analogWrite(motor_s,85);
              myservo.write(38);
            }
            
            forword=get_destance(trig_f, echo_f);
            if (forword<20)
            {
              myservo.write(38);
              break;
            }
            
          }
      
    }
    else if (center>left+5 && abs (center-left)<80)
    {
       myservo.write(58);
       wait=millis();
       while(millis()-wait<1000)
          {
            right=get_destance(trig_r, echo_r);
            left=get_destance(trig_l, echo_l);
            center=(right+left)/2;
            if (center<left && abs (center-left)<80) 
            {
              myservo.write(38);
              break;
              
            }
             if (digitalRead(ir_right)==0)
            {
              myservo.write(38);
             digitalWrite(motor_f,LOW);
             delay(15);
             digitalWrite(motor_b,HIGH);
              analogWrite(motor_s,100);
             ir_turn=millis();
             while(millis()-ir_turn<1000)
             {
             }
             digitalWrite(motor_b,LOW);
             delay(15);
             digitalWrite(motor_f,HIGH);
             myservo.write(18);
             ir_turn=millis();
             while(millis()-ir_turn<700)
             {
              forword=get_destance(trig_f, echo_f);
              if ( forword<20)
              {
                break;     
              }
             }
              analogWrite(motor_s,85);
              myservo.write(38);
            }
            if (digitalRead(ir_left)==0)
            {
               digitalWrite(motor_f,LOW);
             delay(15);
             digitalWrite(motor_b,HIGH);
              analogWrite(motor_s,100);
             ir_turn=millis();
             while(millis()-ir_turn<700)
             {
             }
             digitalWrite(motor_b,LOW);
             delay(15);
             digitalWrite(motor_f,HIGH);
             myservo.write(60);
             ir_turn=millis();
             while(millis()-ir_turn<700)
             {
              forword=get_destance(trig_f, echo_f);
              if ( forword<20)
              {
                break;     
              }
             }
              analogWrite(motor_s,85);
              myservo.write(38);
            }
            forword=get_destance(trig_f, echo_f);
            if (forword<20)
            {
              myservo.write(38);
               digitalWrite(motor_f,LOW);
             delay(15);
             digitalWrite(motor_b,HIGH);
              analogWrite(motor_s,100);
             ir_turn=millis();
             while(millis()-ir_turn<1000)
             {        
             }
             digitalWrite(motor_b,LOW);
              break;
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
        if (forward < 20)
       
        {digitalWrite(motor_f,LOW);
         delay(15);
         digitalWrite(motor_b,HIGH);
          analogWrite(motor_s,100);
         delay(1000);
         digitalWrite(motor_b,LOW);
         delay(15);
         digitalWrite(motor_f,HIGH);
          analogWrite(motor_s,85);
 
          
         
         
      }
          
        
        myservo.write(0);
         analogWrite(motor_s,85);

        wait=millis();
        while(millis()-wait<=1500)
        {
          forward = get_destance(trig_f, echo_f);
          if(forward>120)
          {
            break;
          }
        }
        
        myservo.write(38);
        
        
       

        
  
          
      }


      else if (left < right)
      {
               if (forward < 20)
       
        {digitalWrite(motor_f,LOW);
         delay(15);
         digitalWrite(motor_b,HIGH);
          analogWrite(motor_s, 100);
         delay(500);
         digitalWrite(motor_b,LOW);
         delay(15);
          analogWrite(motor_s, 85);
         digitalWrite(motor_f,HIGH);
         analogWrite(motor_s,100);
          delay(300);
          analogWrite(motor_s,85);
         
         
         
      }

        myservo.write(90);
        analogWrite(motor_s,85);

        wait=millis();
        while(millis()-wait<=1500)
        {
          forward = get_destance(trig_f, echo_f);
          if(forward>130)
          {
            break;
          }
        }
        
        myservo.write(38);
        




      }

      counter_rotate++;

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
  pinMode( ir_right,INPUT);
  pinMode(ir_left,INPUT);

  Serial.begin(9600);
 

}


void loop() {
 
  if (digitalRead(start_Stop) == 0)

  { if (counter_rotate < 12)
    {
     
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
