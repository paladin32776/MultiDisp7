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

#define D7_AI_NONE 0b00000000
#define D7_AI_ALL 0b10000000
#define D7_AI_PWM 0b10100000
#define D7_AI_GRP 0b11000000
#define D7_AI_PWM_GRP 0b11100000

class Disp7
{
  private:
    unsigned char addr;
    unsigned char digit;
    const unsigned short modeon[3] = {0b01, 0b10, 0b11};
    unsigned short offon[2] = {0b00, 0b01};  // {OFF, ON}
    unsigned short* Seg2LED;
    unsigned short Seg2LED_large[16] = {3,4,13,14,15,1,0,2,9,8,10,11,12,6,5,7};
    unsigned short Seg2LED_small[16] = {2,3,13,14,15,1,0,12,6,7,9,10,11,5,4,8}; // NEEDS UPDATE
    // const unsigned short Numbers[10] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
    //                               0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110};
    const unsigned short Numbers[256] = {
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		//	invalid	0..47 (32 is space and is valid)
                                        0b11111100,	//	0	48
                                        0b01100000,	//	1	49
                                        0b11011010,	//	2	50
                                        0b11110010,	//	3	51
                                        0b01100110,	//	4	52
                                        0b10110110,	//	5	53
                                        0b10111110,	//	6	54
                                        0b11100000,	//	7	55
                                        0b11111110,	//	8	56
                                        0b11110110,	//	9	57
                                        0,0,0,0,0,0,0,			//	invalid	58..64
                                        0b11101110,	//	A	65
                                        0,
                                        0b10011100,	//	C	67
                                        0,
                                        0b10011110,	//	E	69
                                        0b10001110,	//	F	70
                                        0,
                                        0b01101110,	//	H	72
                                        0,
                                        0b01111000,	//	J	74
                                        0,
                                        0b00011100,	//	L	76
                                        0,0,
                                        0b11111100, //  O 79
                                        0b11001110,	//	P	80
                                        0,0,0,0,
                                        0b01111100,	//	U	85
                                        0,0,0,
                                        0b01001110,	//	Y	89
                                        0,
                                        0,0,0,0,0,0,			//	invalid	91..96
                                        0,
                                        0b00111110,	//	b	98
                                        0b00011010,	//	c	99
                                        0b01111010,	//	d	100
                                        0,0,0,0,
                                        0b00100000,	//	i	105
                                        0,0,0,0,
                                        0b00101010,  //  n 110
                                        0b00111010,	//	o	111
                                        0,0,
                                        0b00001010,	//	r	114
                                        0,
                                        0b00011110, //  t 116
                                        0b00111000,	//	u	117
                                        0,0,0,0,0,
                                        0,0,0,0,0,			//	invalid	123..127
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//	invalid	128..175
                                        0b11000110,	//	°	176
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		//	invalid	177..255
                                       };
    union LStype
    {
       unsigned char LSbyte[4];
       unsigned int LS;
    } LS;
    unsigned char read_byte(unsigned char regbyte);
    void set_segments(unsigned short segments);
    void set_bit(unsigned int *number, unsigned char n, bool x);
    void write_byte(unsigned char regbyte, unsigned char databyte);
    void write_LS();
    void write_PWMX(unsigned char value);
  public:
    static unsigned const char LARGE=0, SMALL=1;
    static unsigned const char SOLID=0, PWM0=1, PWM1=2;
    Disp7(unsigned char address, unsigned char display_type);
    void mode(unsigned char nmode);
    void set(unsigned char number);
    void set(unsigned char number, unsigned char decimal);
    void set_digit(unsigned char _digit);
    void clear();
    void dutycycle(unsigned char ontime);
    void period(unsigned char prescaler);
    void set_allcall(unsigned char allcalladr);
    void clear_allcall();
    unsigned char get_addr();
};
