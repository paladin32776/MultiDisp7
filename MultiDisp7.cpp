#include "MultiDisp7.h"

MultiDisp7::MultiDisp7(unsigned const char display_count, unsigned const char* addresses,
                       unsigned const char* types, unsigned const char* subdigits)
{
  N=display_count;
  for (int n=0; n<N; n++)
  {
    D[n] = new Disp7(addresses[n], types[n], subdigits[n]);
    D[n]->mode(Disp7::PWM0);
    D[n]->period(Disp7::PWM0, 0);
    D[n]->dutycycle(Disp7::PWM0, 255);
  }
}

void MultiDisp7::set(unsigned char display_index, unsigned char number)
{
  D[display_index]->set(number);
}

void MultiDisp7::clear(unsigned char display_index)
{
  D[display_index]->clear();
}

void MultiDisp7::clear(unsigned char display_index, unsigned char digits)
{
  for (int n=display_index; (n<N) && (n<display_index+digits); n++)
    D[n]->clear();
}

void MultiDisp7::clear()
{
  clear(0, N);
}

void MultiDisp7::print(unsigned char display_index, unsigned char Nstr, char* str)
{
  int n=display_index, nstr=0;

  while ((nstr<Nstr) && (n<N))
  {
    if ((str[nstr]>47 && str[nstr]<58) || (str[nstr]==32))
    {
      if (nstr<Nstr-1)
      {
        if (str[nstr]==32)
          D[n]->clear();
        else
          D[n]->set(str[nstr]-48, str[nstr+1]==46);
      }
      else
        D[n]->set(str[nstr]-48);
      nstr++;
      n++;
    }
    else
      nstr++;
  }
}

void MultiDisp7::print(char* str)
{
  print(0, 2*N, str);
}

void MultiDisp7::dim(unsigned char level)
{
  unsigned char ontime =(unsigned char)(level*255/100);
  for (int n=0; n<N; n++)
    D[n]->dutycycle(Disp7::PWM0, ontime);
}
