//#include "MultiDisp7.h"
#include "Disp7.h"

// unsigned const char addr[] = {96};
// unsigned const char type[] = {MultiDisp7::LARGE};
// unsigned const char subdigit[] = {0};

//MultiDisp7 m7(2,addr, type, subdigit);
Disp7 d7(96, Disp7::LARGE, 0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  d7.set(4,true);

  // char s[4];
  // for (float x=0; x<=20; x=x+0.1)
  // {
  //   sprintf(s, "%01.1f", x);
  //   m7.print(s);
  //   delay(20);
  // }
  // for (int n=100; n>=0; n--)
  // {
  //   m7.dim(n);
  //   delay(30);
  // }
  // m7.clear();
  // m7.dim(100);
  delay(1000);
}
