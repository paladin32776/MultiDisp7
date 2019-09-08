#include "MultiDisp7.h"

unsigned const char addr[] = {97, 96};
unsigned const char type[] = {MultiDisp7::LARGE, MultiDisp7::LARGE};

MultiDisp7 m7(2,addr, type);

void setup()
{
}

void loop()
{
  char s[4];
  for (float x=0; x<=20; x=x+0.1)
  {
    sprintf(s, "%01.1f", x);
    m7.print(s);
    delay(20);
  }
  for (int n=100; n>=0; n--)
  {
    m7.dim(n);
    delay(30);
  }
  m7.clear();
  m7.dim(100);
  delay(1000);
}
