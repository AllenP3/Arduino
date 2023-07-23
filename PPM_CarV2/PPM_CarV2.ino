#include "omni.h"

void setup()
{
  Serial.begin(9600);
  init_GPIO();
}

void loop(){
  mobilize();
}
