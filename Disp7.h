#include "Arduino.h"
#include <Wire.h>

#define D7_MODE1 0x00
#define D7_MODE2 0x01
#define D7_PWM0 0x02
#define D7_PWM1 0x03
#define D7_PWM2 0x04
#define D7_PWM3 0x05
#define D7_PWM4 0x06
#define D7_PWM5 0x07
#define D7_PWM6 0x08
#define D7_PWM7 0x09
#define D7_PWM8 0x0A
#define D7_PWM9 0x0B
#define D7_PWM10 0x0C
#define D7_PWM11 0x0D
#define D7_PWM12 0x0E
#define D7_PWM13 0x0F
#define D7_PWM14 0x10
#define D7_PWM15 0x11
#define D7_GRPPWM 0x12
#define D7_GRPFREQ 0x13
#define D7_LEDOUT0 0x14
#define D7_LEDOUT1 0x15
#define D7_LEDOUT2 0x16
#define D7_LEDOUT3 0x17
#define D7_SUBADR1 0x18
#define D7_SUBADR2 0x19
#define D7_SUBADR3 0x1A
#define D7_ALLCALLADR 0x1B
#define D7_IREF 0x1C
#define D7_EFLAG1 0x1D
#define D7_EFLAG2 0x1E

class Disp7
{
  private:
    unsigned char addr;
    unsigned char digit;
    unsigned short modeon[3] = {0b01, 0b10, 0b11};
    unsigned short offon[2] = {0b00, 0b01};  // {OFF, ON}
    unsigned short* Seg2LED;
    unsigned short Seg2LED_large[8] = {2,3,5,6,7,1,0,4};
    unsigned short Seg2LED_small[8] = {0,1,2,3,4,5,6,7};
    unsigned short Numbers[10] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
                                  0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110};
    void write_byte(unsigned char regbyte, unsigned char databyte);
    unsigned char read_byte(unsigned char regbyte);
    void set_segments(unsigned short segments);
  public:
    static unsigned const char LARGE=0, SMALL=1;
    static unsigned const char SOLID=0, PWM0=1, PWM1=2;
    Disp7(unsigned char address, unsigned char display_type, unsigned char display_digit);
    void mode(unsigned char nmode);
    void set(unsigned char number);
    void set(unsigned char number, unsigned char decimal);
    void clear();
    void dutycycle(unsigned char pwm, unsigned char ontime);
    void period(unsigned char pwm, unsigned char prescaler);
};
