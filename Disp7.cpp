#include "Disp7.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

Disp7::Disp7(unsigned char address, unsigned char display_type, unsigned char display_digit)
{
  Wire.begin(14,2);
  addr = address;
  if (display_type==LARGE)
    Seg2LED = Seg2LED_large;
  else if (display_type==SMALL)
    Seg2LED = Seg2LED_small;
  mode(SOLID);
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
  // Serial.printf("Write reg 0x%02X: 0x%02X (", regbyte, databyte);
  // PRINTBIN(databyte);
  // Serial.println(")");
}

unsigned char Disp7::read_byte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (byte)1);
  unsigned char databyte = Wire.read();
  // Serial.printf("Read reg 0x%02X: 0x%02X (", regbyte, databyte);
  // PRINTBIN(databyte);
  // Serial.println(")");
  return databyte;
}

void Disp7::set_segments(unsigned short segments)
{
  unsigned short LS = 0;
  for (int n=0; n<8; n++)
       LS += offon[bitRead(segments,7-n)] << (2*Seg2LED[n]);

  write_byte(D7_LEDOUT0, lowByte(LS));
  read_byte(D7_LEDOUT0);

  write_byte(D7_PWM0, 0xFF);
  write_byte(D7_PWM1, 0xFF);
  write_byte(D7_PWM2, 0xFF);
  write_byte(D7_PWM3, 0xFF);
  write_byte(D7_PWM4, 0xFF);
  write_byte(D7_PWM5, 0xFF);
  write_byte(D7_PWM6, 0xFF);
  write_byte(D7_PWM7, 0xFF);

  write_byte(D7_GRPPWM, 0xFF);


  read_byte(D7_EFLAG1);
  read_byte(D7_EFLAG2);

  write_byte(D7_MODE1,0b00000001);
  read_byte(D7_MODE1);

  write_byte(D7_MODE2,0b00001000);
  read_byte(D7_MODE2);

  read_byte(D7_IREF);


  // write_byte(D7_LEDOUT1, highByte(LS));
  // Serial.print("W1 A: ");
  // PRINTBIN(addr);
  // Serial.print("  R: ");
  // PRINTBIN((unsigned char)D7_LEDOUT1);
  // Serial.print("  D: ");
  // PRINTBIN(highByte(LS));
  // Serial.println();
  //
  // c = read_byte(D7_LEDOUT1);
  // Serial.print("R1 A: ");
  // PRINTBIN(addr);
  // Serial.print("  R: ");
  // PRINTBIN((unsigned char)D7_LEDOUT1);
  // Serial.print("  D: ");
  // PRINTBIN(c);
  // Serial.println();
}

void Disp7::set(unsigned char number)
{
  set_segments(Numbers[number]);
}

void Disp7::set(unsigned char number, unsigned char decimal)
{
  set_segments(Numbers[number]+decimal);
}

void Disp7::clear()
{
  set_segments(0);
}

void Disp7::dutycycle(unsigned char pwm, unsigned char ontime)
{
  write_byte(D7_GRPPWM, ontime);
}

void Disp7::period(unsigned char pwm, unsigned char prescaler)
{
    write_byte(D7_GRPFREQ, prescaler);
}
