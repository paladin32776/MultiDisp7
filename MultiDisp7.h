#include "Arduino.h"
#include "Disp7.h"

class MultiDisp7
{
  private:
    unsigned char N=0;
    Disp7* D[32];
  public:
    static unsigned const char LARGE=Disp7::LARGE, SMALL=Disp7::SMALL;
    static unsigned const char SOLID=Disp7::SOLID, PWM0=Disp7::PWM0, PWM1=Disp7::PWM1;

    MultiDisp7(unsigned const char display_count, unsigned const char* addresses,
               unsigned const char* types, unsigned const char* subdigits);
    void set(unsigned char display_index, unsigned char number);
    void clear(unsigned char display_index);
    void clear(unsigned char display_index, unsigned char digits);
    void clear();
    void print(unsigned char display_index, unsigned char digits, char* str);
    void print(char* str);
    void dim(unsigned char level);
};
