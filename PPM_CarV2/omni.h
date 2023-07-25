#ifndef OMNI_H
#define OMNI_H
#include <Arduino.h>
#include <InterruptHandler.h>
#include <PPMReader.h>


#define SPEED 100
#define speedPinR 9   
#define RightMotorDirPin1  22    
#define RightMotorDirPin2  24                                    
#define LeftMotorDirPin1  26    
#define LeftMotorDirPin2  28   
#define speedPinL 10   

#define speedPinRB 11   
#define RightMotorDirPin1B  5    
#define RightMotorDirPin2B 6    
#define LeftMotorDirPin1B 7    
#define LeftMotorDirPin2B 8  
#define speedPinLB 12
int var_maxPWM = 255; 
int one, two, three, four, five, six;
int pp1, pp2, pp3, pp4, pp5, pos, pulsewidth, duration, dist, val_L,val_R,val_M, avg;
bool ch1_gear, ch2_gear, ch3_gear, ch4_gear, ch5_gear, ch6_gear;

int interruptPin = 18;
int channelAmount = 6;
int ch[6];
PPMReader ppm(interruptPin, channelAmount);


void readPPMData()
{
  for (int channel = 1; channel <= channelAmount; ++channel) {
        unsigned long value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
    Serial.println();
    for (int channel = 1; channel <= channelAmount; ++channel)
  {
    unsigned long value = ppm.latestValidChannelValue(channel, 0);
    ch[channel - 1] = value;
  }
   one = ch[0];
   two = ch[1];
   three = ch[2];
   four = ch[3];
   five = ch[4];
   six = ch[5];
   Serial.flush();
}

void FR_fwd(int speed)
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}
void FR_bck(int speed)
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}
void FL_fwd(int speed)
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}
void FL_bck(int speed)
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}

void RR_fwd(int speed)
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
  analogWrite(speedPinRB,speed);
}
void RR_bck(int speed)
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
  analogWrite(speedPinRB,speed);
}
void RL_fwd(int speed)
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
  analogWrite(speedPinLB,speed);
}
void RL_bck(int speed)
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
  analogWrite(speedPinLB,speed);
}
void go_advance(int speed){
   RL_fwd(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_fwd(speed); 
}
void go_back(int speed){
   RL_bck(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_bck(speed); 
}
void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck) {
  FL_fwd(speed_fl_fwd); 
  RL_bck(speed_rl_bck); 
  RR_fwd(speed_rr_fwd);
  FR_bck(speed_fr_bck);
}
void left_shift(int speed_fl_bck,int speed_rl_fwd ,int speed_rr_bck,int speed_fr_fwd){
   FL_bck(speed_fl_bck);
   RL_fwd(speed_rl_fwd);
   RR_bck(speed_rr_bck);
   FR_fwd(speed_fr_fwd);
}

void left_turn(int speed){
   RL_bck(0);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(0); 
}
void right_turn(int speed){
   RL_fwd(speed);
   RR_bck(0);
   FR_bck(0);
   FL_fwd(speed); 
}
void left_back(int speed){
   RL_fwd(0);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(0); 
}
void right_back(int speed){
   RL_bck(speed);
   RR_fwd(0);
   FR_fwd(0);
   FL_bck(speed); 
}
void clockwise(int speed){
   RL_fwd(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(speed); 
}
void countclockwise(int speed){
   RL_bck(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(speed); 
}



 
void stop_Stop()
{
  analogWrite(speedPinLB,0);
  analogWrite(speedPinRB,0);
  analogWrite(speedPinL,0);
  analogWrite(speedPinR,0);
  ch1_gear = false;
  ch2_gear = false;
}



void init_GPIO()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);
   
  stop_Stop();
}
void mobilize(){
  //digitalWrite(LED_BUILTIN, HIGH);
  
  readPPMData();

  if(two > 1515 || two < 1485){
    ch1_gear = true;
  }
  else{
    ch1_gear = false;
  }
  if(one > 1515 || one < 1485){
    ch2_gear = true;
  }
  else{
    ch2_gear = false;
  }

  if (ch1_gear == false && ch2_gear == false) // stay idle
  {
    stop_Stop();
  }

  else if(ch1_gear == true && ch2_gear == true){

   if (two > 1515 && one > 1515)
  {
    //right diagonal front
    pp1 = abs(map(one, 1500, 2000, 0, var_maxPWM));
    pp2 = abs(map(two, 1500, 2000, 0, var_maxPWM));
    avg = (pp1 + pp2)/2;
    
    right_shift(avg,0,avg,0);
  }
  else if(two < 1485 && one < 1485){
    //left diagonal back
    pp1 = abs(map(one, 1500, 1000, 0, var_maxPWM));
    pp2 = abs(map(two, 1500, 1000, 0, var_maxPWM));
    avg = (pp1 + pp2)/2;
    left_shift(avg,0,avg,0);
  }
  else if(two < 1485 && one > 1515){
    //right diagonal back
    pp1 = abs(map(one, 1500, 2000, 0, var_maxPWM));
    pp2 = abs(map(two, 1500, 1000, 0, var_maxPWM));
    avg = (pp1 + pp2)/2;
    right_shift(0,avg,0,avg); 
  }
  else if(two > 1515 && one < 1485){
    //left diagonal front
    pp1 = abs(map(one, 1500, 1000, 0, var_maxPWM));
    pp2 = abs(map(two, 1500, 2000, 0, var_maxPWM));
    avg = (pp1 + pp2)/2;
    left_shift(0,avg,0,avg);
  }
}

else{
  if (two <= 1450) // move backward
  {
   
    pp1 = abs(map(two, 1500, 1000, 0, var_maxPWM));
    go_back(pp1);
    Serial.println("Backward");
    delayMicroseconds(200);
      }
  
  else if (two >= 1550) // move forward
  {
    pp1 = abs(map(two, 1500, 2000, 0, var_maxPWM)); // map PPM 
    go_advance(pp1);
    Serial.println("Forward");
    delayMicroseconds(200);
  }


  if (one <= 1450) // left shift/turn
  {
   
    pp1 = abs(map(one, 1500, 1000, 0, var_maxPWM));
    Serial.println("Left Shift");
    delayMicroseconds(200);

    //left_shift(pp1,pp1,pp1,pp1); //left shift
    left_turn(pp1); //left turn	
      }
  
  else if (one >= 1550) // right shift/turn
  {
    pp1 = abs(map(one, 1500, 2000, 0, var_maxPWM)); // map PPM 
    Serial.println("Right Shift");
    delayMicroseconds(200);

    //right_shift(pp1,pp1,pp1,pp1); //right shift
    right_turn(pp1); //right turn
  }
  }

  //digitalWrite(LED_BUILTIN, LOW);
}

#endif