#include "MultiDisp7.h"

unsigned const char display_count = 2;
unsigned const char addr[] = {96,96};
unsigned const char type[] = {MultiDisp7::LARGE,MultiDisp7::LARGE};
unsigned const char subdigit[] = {0,1};

MultiDisp7 m7(display_count, addr, type, subdigit);

void setup()
{
}

void fadeout()
{
  for (int n=100; n>=0; n--)
  {
    m7.dim(n);
    delay(10);
  }
}

void fadein()
{
  for (int n=0; n<=100; n++)
  {
    m7.dim(n);
    delay(10);
  }
}

void loop()
{
  m7.print("01");
  fadeout();
  m7.print("2.2");
  fadein();
  m7.print("7",0);
  delay(1000);
  m7.print("9.",1);
  fadeout();
  fadein();
  m7.clear(0);
  delay(1000);
  m7.clear(1);
  delay(1000);
}
