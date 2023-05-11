#include "wrapper.h"

void loop()
{ 
   readPPMData(); 
  for (int i = 0; i < 6; i++)
  {
    Serial.print(" " + String(ch[i]) + " "); 
  }
  Serial.println(); 

  //mobilize();
  neutral;
}

  // neutral(); // stop the bot
    //Serial.println("System on hold");
    //Serial.println();

  /*//front
   // Print latest valid values from all channels
    for (int channel = 1; channel <= channelAmount; ++channel) {
        unsigned long value = ppm.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
  
   unsigned long drivevalue = ppm.latestValidChannelValue(2, 0);
   unsigned long turnvalue = ppm.latestValidChannelValue(4, 0);
    
    if(drivevalue >= 1550){
    int rawfront = map(drivevalue, 1500, 2000, 255, 0);
      digitalWrite(ML_Ctrl, HIGH);// set the direction control pins of group B motor to LOW level
      analogWrite(ML_PWM, rawfront);//set the PWM control speed of group B motor to 
      digitalWrite(MR_Ctrl, HIGH);// set the direction control pins of group A motor to LOW level
      analogWrite(MR_PWM,rawfront);//set the PWM control speed of group A motor to 0
    }
    
    
    else if(drivevalue <= 1450){
    int rawback = map(drivevalue, 1500, 1000, 0, 255);
      digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
      analogWrite(ML_PWM, rawback);//set the PWM control speed of group B motor to 0
      digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group A motor to LOW level
      analogWrite(MR_PWM,rawback);//set the PWM control speed of group A motor to 0
    }

    else if(turnvalue >= 1550){
      int rawright = map(turnvalue, 1500, 2000, 255, 0);
      digitalWrite(ML_Ctrl, HIGH);
      analogWrite(ML_PWM, rawright);

      digitalWrite(MR_Ctrl, LOW);
      int rightturn = map(rawright, 255, 0, 0, 255);
      analogWrite(MR_PWM,rightturn);
    }

    else if(turnvalue <= 1450){
      int rawleft = map(turnvalue, 1500, 1000, 0, 255);
      digitalWrite(ML_Ctrl, LOW);
      analogWrite(ML_PWM, rawleft);

      digitalWrite(MR_Ctrl, HIGH);
      int leftturn = map(rawleft, 0, 255, 255, 0);
      analogWrite(MR_PWM,leftturn);
    }

    else{
      digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  analogWrite(ML_PWM,0);//set the PWM control speed of group B motor to 0
  digitalWrite(MR_Ctrl, LOW);// set the direction control pins of group A motor to LOW level
  analogWrite(MR_PWM,0);//set the PWM control speed of group A motor to 0
    }
   

    
  //digitalWrite(ML_Ctrl, LOW);// set the direction control pins of group B motor to LOW level
  //analogWrite(ML_PWM, teresa);//set the PWM control speed of group B motor to 0
    Serial.println(String(drivevalue));
    Serial.println();
 */
/*
void loop()
{
  readPPMData(); // get the ppm data from transmitter
  //for (int i = 0; i < 6; i++)
 // {
    Serial.print(" " + String(ch[2]) + " "); // print the received channel datas
 // }
  Serial.println(); // print \n 
    //mobilize(); // move the bot according to the instruciton 
  //}
  //else
  //{
    //neutral(); // stop the bot
   // Serial.println("System on hold");
  //}
  //Serial.println();}
*/