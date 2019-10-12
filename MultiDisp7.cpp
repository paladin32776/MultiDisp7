#include "MultiDisp7.h"

MultiDisp7::MultiDisp7(unsigned const char display_count, unsigned const char* addresses,
                       unsigned const char* types, unsigned const char* subdigits)
{
  N=display_count;
  for (int n=0; n<N; n++)
  {
    int n_check = 0, n_existing = -1;
    while ((n_check<n) && (n_existing==-1))
    {
      if ((D[n_check]->get_addr())==addresses[n])
        n_existing = n_check;
      n_check++;
    }
    if (n_existing>-1)
      D[n] = D[n_existing];
    else
      D[n] = new Disp7(addresses[n], types[n]);
    D_subdigit[n] = subdigits[n];
  }
}

void MultiDisp7::set(unsigned char display_index, unsigned char number)
{
  D[display_index]->set_digit(D_subdigit[display_index]);
  D[display_index]->set(number);
}

void MultiDisp7::set(unsigned char display_index, unsigned char number, unsigned char decimal)
{
  D[display_index]->set_digit(D_subdigit[display_index]);
  D[display_index]->set(number, decimal);
}

void MultiDisp7::clear(unsigned char display_index)
{
  D[display_index]->set_digit(D_subdigit[display_index]);
  D[display_index]->clear();
}

void MultiDisp7::clear(unsigned char display_index, unsigned char digits)
{
  for (int n=display_index; (n<N) && (n<display_index+digits); n++)
  {
    D[n]->set_digit(D_subdigit[n]);
    D[n]->clear();
  }
}

void MultiDisp7::clear()
{
  clear(0, N);
}

void MultiDisp7::print(char* str, unsigned char display_index)
{
  int n=display_index, nstr=0;
  unsigned char Nstr = strlen(str);
  while ((nstr<Nstr) && (n<N))
  {
    if ((str[nstr]>47 && str[nstr]<58) || (str[nstr]==32))
    {
      if (nstr<Nstr-1)
      {
        if (str[nstr]==32)
          clear(n);
        else
          set(n, str[nstr]-48, str[nstr+1]==46);
      }
      else
        set(n, str[nstr]-48);
      nstr++;
      n++;
    }
    else
      nstr++;
  }
}

void MultiDisp7::print(char* str)
{
  print(str, 0);
}

void MultiDisp7::dim(unsigned char level)
{
  unsigned char ontime =(unsigned char)(level*255/100);
  for (int n=0; n<N; n++)
    D[n]->dutycycle(ontime);
}
