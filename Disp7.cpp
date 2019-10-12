#include "Disp7.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

Disp7::Disp7(unsigned char address, unsigned char display_type)
{
  Wire.begin(14,2);
  addr = address;
  digit = 0;
  if (display_type==LARGE)
    Seg2LED = Seg2LED_large;
  else if (display_type==SMALL)
    Seg2LED = Seg2LED_small;
  mode(PWM1);
  write_PWMX(0xFF);
  write_byte(D7_GRPPWM, 0xFF);
  write_byte(D7_MODE1,0b00000001);
  write_byte(D7_MODE2,0b00001000);
}

void Disp7::mode(unsigned char nmode)
{
  offon[1] = modeon[nmode];
}

void Disp7::write_byte(unsigned char regbyte, unsigned char databyte)
{
  Wire.beginTransmission(addr); // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.write(byte(databyte));             // sends value byte
  Wire.endTransmission();     // stop transmitting
}

void Disp7::write_LS()
{
  Wire.beginTransmission(addr); // transmit to device #addr
  Wire.write(byte(D7_LEDOUT0 | D7_AI_ALL)); // sends instruction byte including auto increment set
  Wire.write(byte(LS.LSbyte[0])); // sends value bytes
  Wire.write(byte(LS.LSbyte[1]));
  Wire.write(byte(LS.LSbyte[2]));
  Wire.write(byte(LS.LSbyte[3]));
  Wire.endTransmission();     // stop transmitting
}

void Disp7::write_PWMX(unsigned char value)
{
  Wire.beginTransmission(addr); // transmit to device #addr
  Wire.write(byte(D7_PWM0 | D7_AI_ALL)); // sends instruction byte including auto increment set
  for (int n=0; n<16; n++)
    Wire.write(byte(value)); // sends value bytes
  Wire.endTransmission();     // stop transmitting
}

unsigned char Disp7::read_byte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (byte)1);
  unsigned char databyte = Wire.read();
  return databyte;
}

void Disp7::set_bit(unsigned int *number, unsigned char n, bool x)
{
  unsigned int newbit = !!x;    // Also booleanize to force 0 or 1
  *number ^= (-newbit ^ *number) & (1UL << n);
}

void Disp7::set_segments(unsigned short segments)
{
  for (int n=0; n<8; n++)
  {
    set_bit(&LS.LS, 2*Seg2LED[n+digit*8], offon[bitRead(segments,7-n)] & 1);
    set_bit(&LS.LS, 2*Seg2LED[n+digit*8]+1, offon[bitRead(segments,7-n)] & 2);
  }
  write_LS();
}

void Disp7::set(unsigned char number)
{
  set_segments(Numbers[number]);
}

void Disp7::set(unsigned char number, unsigned char decimal)
{
  set_segments(Numbers[number]+decimal);
}

void Disp7::set_digit(unsigned char _digit)
{
  if ((_digit==0) || (_digit==1))
    digit = _digit;
}

void Disp7::clear()
{
  set_segments(0);
}

void Disp7::dutycycle(unsigned char ontime)
{
  write_byte(D7_GRPPWM, ontime);
}

void Disp7::period(unsigned char prescaler)
{
    write_byte(D7_GRPFREQ, prescaler);
}

void Disp7::set_allcall(unsigned char allcalladr)
{
  write_byte(D7_ALLCALLADR, allcalladr);
  write_byte(D7_MODE1, read_byte(D7_MODE1) | 0x01);
}

void Disp7::clear_allcall()
{
  write_byte(D7_MODE1, read_byte(D7_MODE1) & 0xFE);
}

unsigned char Disp7::get_addr()
{
  return addr;
}
