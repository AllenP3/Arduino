
#include "omni.h"

void setup()
{
  Serial.begin(9600);
  init_GPIO();
 

//go_advance(SPEED);
     delay(250);
     stop_Stop();
     delay(1000);
  /*
go_back(SPEED);
      delay(1000);
      stop_Stop();
      delay(1000);
	  
left_turn(TURN_SPEED);
      delay(1000);
      stop_Stop();
      delay(1000);
	  
right_turn(TURN_SPEED);
     delay(1000);
     stop_Stop();
     delay(1000);
  
right_shift(200,200,200,200); //right shift
     delay(1000);
     stop_Stop();
     delay(1000);

left_shift(200,200,200,200); //left shift
     delay(1000);
     stop_Stop();
     delay(1000);
	 
left_shift(200,0,200,0); //left diagonal back
     delay(1000);
     stop_Stop();
	 delay(1000);
 
right_shift(200,0,200,0); //right diagonal ahead
     delay(1000);
     stop_Stop();
	 delay(1000);

left_shift(0,200,0,200); //left diagonal ahead
     delay(1000);
     stop_Stop();
     delay(1000);

right_shift(0,200,0,200); //right diagonal back
     delay(1000);
     stop_Stop();
	 delay(1000);
*/
}

void loop(){
  Mobilize();
  
}
