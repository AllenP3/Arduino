 
#include <PPMReader.h>
#define ML_Ctrl 2    
#define ML_PWM 5  
#define MR_Ctrl 4    
#define MR_PWM 6   
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
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);

  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM,0);
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM,0);
  delay(1000);
 
}

void readPPMData()
{
  /*for (int channel = 1; channel <= channelAmount; ++channel) {
        unsigned long value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }*/
    for (int channel = 1; channel <= channelAmount; ++channel)
  {
    unsigned long value = ppm.latestValidChannelValue(channel, 0);
    ch[channel - 1] = value;
  }
}

void move_forward()
{
 // int rawfront = map(drivevalue, 1500, 2000, 255, 0);
      digitalWrite(ML_Ctrl, HIGH);
      analogWrite(ML_PWM, pp1);
      digitalWrite(MR_Ctrl, HIGH);
      analogWrite(MR_PWM, pp2);
      Serial.println("FORWARD");
}
void move_backward()
{
  //int rawback = map(drivevalue, 1500, 1000, 0, 255);
      digitalWrite(ML_Ctrl, LOW);
      analogWrite(ML_PWM, pp1);
      digitalWrite(MR_Ctrl, LOW);
      analogWrite(MR_PWM, pp2);
      Serial.println("BACKWARD");
}
void move_left()
{
 // int rawleft = map(turnvalue, 1500, 1000, 0, 255);
      digitalWrite(ML_Ctrl, LOW);
      analogWrite(ML_PWM, pp3);
      digitalWrite(MR_Ctrl, HIGH);
      //int leftturn = map(rawleft, 0, 255, 255, 0);
      analogWrite(MR_PWM,pp4);
      Serial.println("LEFT");

}

void move_right()
{
   //int rawright = map(turnvalue, 1500, 2000, 255, 0);
      digitalWrite(ML_Ctrl, HIGH);
      analogWrite(ML_PWM, pp3);
      digitalWrite(MR_Ctrl, LOW);
      //int rightturn = map(rawright, 255, 0, 0, 255);
      analogWrite(MR_PWM,pp4);
      Serial.println("RIGHT");
}

void neutral() 
{
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM,0);
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM,0);
}

void mobilize() 
{

  int one = ch[0];
  int two = ch[1];
  int three = ch[2];
  int four = ch[3];
  int five = ch[4];
  int six = ch[5];


  if (two > 1485 && two < 1515) // stay idle
  {
    ch2_neutral = true;
  }

  else if (two <= 1450) // move backward
  {
    ch2_neutral = false;
    pp1 = abs(map(two, 1500, 1000, 0, var_maxPWM));
    pp2 = pp1;
    move_backward();
    Serial.println("Moving Backward");
  }
  
  else if (two >= 1550) // move forward
  {
    ch2_neutral = false;
    pp1 = abs(map(two, 1500, 2000, var_maxPWM, 0)); // map PPM 
    pp2 = pp1;
    move_forward();
    Serial.println("Moving Forward");
  }
  
  if (four > 1485 && four < 1515) // stop 
  {
    ch3_neutral = true;
  }
  else if (four >= 1550) // move right
  {
    ch3_neutral = false;
    pp3 = abs(map(four, 1500, 2000, var_maxPWMTurn, 0 ));
    pp4 = abs(map(pp3, var_maxPWMTurn, 0, 0, var_maxPWMTurn ));
    move_right();
  }
  else if (four <= 1450) // move left
  {
    ch3_neutral = false;
    pp3 = abs(map(four, 1500, 1000, 0, var_maxPWMTurn));
    pp4 = abs(map(pp3, 0, var_maxPWMTurn, var_maxPWMTurn , 0));
    move_left();
  }
  else if(ch2_neutral == false && ch3_neutral == false){
    //turn();
  }

  if (ch2_neutral == true && ch3_neutral == true) // neutral gear 
  {
    neutral();
  }
}
