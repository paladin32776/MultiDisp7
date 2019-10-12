# Driving a list of large and small 7-Segment displays via I2C
7-segment displays are driven via a PCA9551 I2C LED driver chip. Currently allows up to 8 displays to be connected on the same I2C bus.

# Methods:

```
MultiDisp7(unsigned const char display_count, unsigned const char* addresses, unsigned const char* types)
```
Constructor with the following arguments:
display_count ... Number of displays connected to I2C bus.
addresses ... Array of I2C addresses for connected digits/TLC59116's
types ... Array of display types. Currently two are supported: MultiDisp7::LARGE and MultiDisp7::SMALL.
(NOTE: SMALL segment order is still arbitrary, and thus won't result in legible digits)

void set(unsigned char display_index, unsigned char number);
Set one digit to a numeric value. Arguments are:
display_index ... Index of display to set number on
number ... Integer number from 0 to 9

void clear(unsigned char display_index);
Clear a specific display. Arguments:
display_index ... Index of display to clear

void clear(unsigned char display_index, unsigned char digits);
Clear a specific range of display. Arguments:
display_index ... Index of first display to clear
digits ...  Count of how many displays forward to clear, including first one.

void clear();
Clear all connected displays.

void print(unsigned char display_index, unsigned char digits, char* str);
Output a string to displays. Arguments are:
display_index ... Index of display to start on.
digits ... Number of digits to display.
str ... Array of chars to show on displays. Allowed characters are 0..9, decimal point, and space.

void print(char* str);
Output a string to displays. Function starts at first display and uses all displays. Arguments are:
str ... Array of chars to show on displays. Allowed characters are 0..9, decimal point, and space.
