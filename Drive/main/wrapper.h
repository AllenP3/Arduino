//************************************************************************
/*
 keyestudio 4wd BT Car
 lesson 8.2
 Motor driver
 http://www.keyestudio.com
*/ 
#include <PPMReader.h>
#define ML_Ctrl 2     //define the direction control pins of group B motor
#define ML_PWM 5   //define the PWM control pins of group B motor
#define MR_Ctrl 4    //define the direction control pins of group A motor
#define MR_PWM 6   //define the PWM control pins of group A motor
int interruptPin = 3;
int channelAmount = 6;
int ch[6];
int pp1, pp2, pp3, pp4;
boolean ch2_neutral = true, ch3_neutral =  true;
int var_maxPWM = 255, var_maxPWMTurn = 0;
PPMReader ppm(interruptPin, channelAmount);

void setup()
{
  Serial.begin(9600);
  /*pinMode(ML_Ctrl, OUTPUT);//set direction control pins of group B motor to output
  pinMode(ML_PWM, OUTPUT);//set PWM control pins of group B motor to output
  pinMode(MR_Ctrl, OUTPUT);//set direction control pins of group A motor to output
  pinMode(MR_PWM, OUTPUT);//set PWM control pins of group A motor to output
  digitalWrite(ML_Ctrl, HIGH);//set the direction control pins of group B motor to HIGH
  analogWrite(ML_PWM,105);//set the PWM control speed of group B motor to 55*/

  delay(255);//delay in 2000ms
  digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  analogWrite(ML_PWM,0);//set the PWM control speed of group B motor to 0
  digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group A motor to LOW level
  analogWrite(MR_PWM,0);//set the PWM control speed of group A motor to 0
  delay(1000);// delay in 2000ms
 
}
/*void loop()
{ 
  //front
   // Print latest valid values from all channels
    for (int channel = 1; channel <= channelAmount; ++channel) {
        unsigned long value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
  
   unsigned long drivevalue = ppm.latestValidChannelValue(2, 0);
  //int teresa = map(drivevalue, 1000, 2000, 0, 255);
  int forbac = map(drivevalue, 1000, 2000, 0, 255);
    if(forbac <= 120){
    int rawback = map(forbac, 127, 0, 0, 255);
      digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
      analogWrite(ML_PWM, rawback);//set the PWM control speed of group B motor to 0
      digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group A motor to LOW level
      analogWrite(MR_PWM,rawback);//set the PWM control speed of group A motor to 0
    }
    else if(forbac >= 140){
    int rawfront = map(forbac, 127, 255, 0, 255);
      digitalWrite(ML_Ctrl, HIGH);// set the direction control pins of group B motor to LOW level
      analogWrite(ML_PWM, rawfront);//set the PWM control speed of group B motor to 0
      digitalWrite(MR_Ctrl, HIGH);// set the direction control pins of group A motor to LOW level
      analogWrite(MR_PWM,rawfront);//set the PWM control speed of group A motor to 0
    }
    else {
      digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  analogWrite(ML_PWM,0);//set the PWM control speed of group B motor to 0
  digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group A motor to LOW level
  analogWrite(MR_PWM,0);//set the PWM control speed of group A motor to 0
    }
  //digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  //analogWrite(ML_PWM, teresa);//set the PWM control speed of group B motor to 0
    Serial.println(String(forbac));
    Serial.println();
}*/

void readPPMData() // Read all the channel values
{
  for (int channel = 1; channel <= channelAmount; ++channel)
  {
    unsigned long value = ppm.latestValidChannelValue(channel, 0);
    ch[channel - 1] = value;
  }
}

void move_forward()
{
  digitalWrite(ML_Ctrl, HIGH);// set the direction control pins of group B motor to LOW level
  digitalWrite(MR_Ctrl, HIGH);// set the direction control pins of group B motor to LOW level
  Serial.println("FORWARD");
  analogWrite(ML_Ctrl, pp1);
  analogWrite(MR_Ctrl, pp2);
}
void move_backward()
{
  digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  Serial.println("BACKWARD");
  analogWrite(ML_Ctrl, pp1);
  analogWrite(MR_Ctrl, pp2);
}
/*void move_left()
{
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(pwm1, pp3);
  analogWrite(pwm2, pp4);
  Serial.println("LEFT");
}

void move_right()
{
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  analogWrite(pwm1, pp3);
  analogWrite(pwm2, pp4);
  Serial.println("RIGHT");
}*/

void neutral() // neutral gear activation
{
   digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  analogWrite(ML_Ctrl, 0);
  analogWrite(MR_Ctrl, 0);
  Serial.println("NEUTRAL");
}

void mobilize() // move the bot according to the command received
{
  if (ch[2] > 1485 && ch[2] < 1515) // stay idle
  {
    ch2_neutral = true;
  }
  else if (ch[2] < 1485) // move backward
  {
    ch2_neutral = false;
    pp1 = abs(map(ch[2], 1000, 1485, 0, var_maxPWM));
    pp2 = pp1;
    move_backward();
    Serial.println("Moving Backward");
  }
  else if (ch[2] > 1515) // move forward
  {
    ch2_neutral = false;
    pp1 = abs(map(ch[2], 1515, 2000, 0, var_maxPWM)); // map the PPM values to PWM value
    pp2 = pp2;
    move_forward();
    Serial.println("Moving Forward");

  }
  /*if (ch[3] > 1485 && ch[3] < 1515) // used to stop the when chl_neutral and ch3_neutral are true
  {
    ch3_neutral = true;
  }
  else if (ch[3] > 1515) // move right
  {
    ch3_neutral = false;
    pp3 = abs(map(ch[3], 1515, 2000, 0, var_maxPWMTurn ));
    pp4 = abs(map(ch[3], 1515, 2000, 0, var_maxPWMTurn ));
    move_right();
  }
  else if (ch[3] < 1485) // move left
  {
    ch3_neutral = false;
    pp3 = abs(map(ch[3], 1000, 1485, var_maxPWMTurn , 0));
    pp4 = abs(map(ch[3], 1000, 1485, var_maxPWMTurn , 0));
    move_left();
  }*/
  if (ch2_neutral && ch3_neutral) // Stop the bot
  {
    neutral();
  }
}
//************************************************************************
