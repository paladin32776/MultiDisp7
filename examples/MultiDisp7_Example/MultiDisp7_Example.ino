#include "MultiDisp7.h"

unsigned const char display_count = 2;
unsigned const char addr[] = {96,96};
unsigned const char type[] = {MultiDisp7::LARGE,MultiDisp7::LARGE};
unsigned const char subdigit[] = {0,1};

MultiDisp7 m7(display_count, addr, type, subdigit);

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
