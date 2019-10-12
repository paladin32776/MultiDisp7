# Driving a list of large and small 7-Segment displays via I2C
7-segment displays are driven via a TLC5916 I2C LED driver chip. Currently allows up to 2*14 displays to be connected on the same I2C bus.

# Methods:

#### `MultiDisp7(unsigned const char display_count, unsigned const char* addresses, unsigned const char* types, unsigned const char* subdigits)`

Constructor with the following arguments:
- `display_count` ... Number of displays connected to I2C bus.
- `addresses` ... Array of I2C addresses for connected digits/TLC59116's. 
- `types` ... Array of display types:
  - `MultiDisp7::LARGE`
  - `MultiDisp7::SMALL` (segment order is still arbitrary, won't result in legible digits)
- `subdigits` ... Subdigit of TLC59116 display module (0 or 1) to be mapped to this display digit.

**IMPORTANT NOTE** - allowed address range is **96 to 111**, with the **exception** of:
- **104** ... This is the "AllCall" adress, which addresses **all TLC59116 devices** on the I2C bus at the same time. Useful for e.g. global dimming.
- **107** ... Software **reset** of all TLC59116 devices on the I2C bus.


#### `void set(unsigned char display_index, unsigned char number)`

Set one digit to a numeric value. Arguments are:
- `display_index` ... Index of display to set number on.
- `number` ... Integer number from 0 to 9.

#### `void set(unsigned char display_index, unsigned char number, unsigned char decimal)`

Set one digit to a numeric value. Arguments are:
- `display_index` ... Index of display to set number on.
- `number` ... Integer number from 0 to 9.
- `decimal` ... 0 (or false) displays not decimal point, 1 (or true) displays a decimal point.

#### `void clear(unsigned char display_index)`

Clear a specific display. Arguments:
- `display_index` ... Index of display to clear.

#### `void clear(unsigned char display_index, unsigned char digits)``

Clear a specific range of display. Arguments:
- `display_index` ... Index of first display to clear.
- `digits` ...  Count of how many displays forward to clear, including first one.

#### `void clear()`

Clears all connected displays.

#### `void print(char* str, unsigned char display_index)`

Output a string to displays. Arguments are:
- `str` ... Array of chars to show on displays. Allowed characters are 0..9, decimal point, and space.
- `display_index` ... Index of display to start on.

#### `void print(char* str)`

Output a string to displays. Function starts at first display and uses all displays. Arguments are:
- `str` ... Array of chars to show on displays. Allowed characters are 0..9, decimal point, and space.

#### `void dim(unsigned char level)`

Dims displays.
- `level` ... value from 0 (off) to 100 (full brightness).
