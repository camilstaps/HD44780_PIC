# HD44780
C library for interfacing a HD44780 LCD display with a PIC microcontroller

This library was initially developed for the XC8 compiler, but I see no reason
why it shouldn't work with XC16 or XC8.

Copyright &copy; 2016 [Camil Staps](mailto:info@camilstaps.nl). This project is
licensed under the GPL v2.0 license. For more details, see the `LICENSE` file.

## Features

- Supports 8- and 4-bit mode
- Support for two displays sharing the same bus (except for the Enable lines)
