#include "hd44780.h"

#ifdef HD44780_DUAL
	#define HD44780_SET_E(x) {if (hd44780_device == 0) HD44780_E1 = x; else HD44780_E2 = x;}
#else
	#define HD44780_SET_E(x) {HD44780_E = x;}
#endif

void hd44780_wait()
{
	unsigned char temp;
	HD44780_DATA_TRIS = HD44780_DATA_CAST(0xff);
	HD44780_RS = 0;
	HD44780_RW = 1;
	do
	{
		HD44780_SET_E(1);
		temp = HD44780_DATA;
		HD44780_SET_E(0);
		HD44780_SET_E(1);
		HD44780_SET_E(0);
	} while (HD44780_DATA_R7(temp));
	HD44780_DATA_TRIS = HD44780_DATA_CAST(0x00);
	HD44780_RW = 0;
}

void hd44780_put_char(unsigned char data)
{
	hd44780_wait();
	HD44780_RS = 1;
#ifdef HD44780_4BIT
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(data >> 4);
	HD44780_SET_E(0);
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(data & 0x0f);
	HD44780_SET_E(0);
#else
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(data);
	HD44780_SET_E(0);
#endif
}

void hd44780_put_cmd(unsigned char cmd)
{
	hd44780_wait();
	HD44780_RS = 0;
#ifdef HD44780_4BIT
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(cmd >> 4);
	HD44780_SET_E(0);
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(cmd & 0x0f);
	HD44780_SET_E(0);
#else
	HD44780_SET_E(1);
	HD44780_DATA = HD44780_DATA_CAST(cmd);
	HD44780_SET_E(0);
#endif
}

inline void hd44780_set_address(unsigned char addr)
{
	hd44780_put_cmd(0x80 | addr);
}

inline void hd44780_clear(void)
{
	hd44780_put_cmd(0x01);
	HD44780_DELAY_1640US();
}

void hd44780_init_ports(void)
{
	HD44780_DATA = HD44780_DATA_CAST(0x00);
	HD44780_DATA_TRIS = HD44780_DATA_CAST(0x00);

	HD44780_RS = 0;
	HD44780_RS_TRIS = 0;
	HD44780_RW = 0;
	HD44780_RW_TRIS = 0;

#ifdef HD44780_DUAL
	HD44780_E1 = 0;
	HD44780_E1_TRIS = 0;
	HD44780_E2 = 0;
	HD44780_E2_TRIS = 0;
#else
	HD44780_E = 0;
	HD44780_E_TRIS = 0;
#endif
}

void hd44780_init(void)
{
#ifdef HD44780_DUAL
	unsigned char device_counter;
#endif

	hd44780_init_ports();

	HD44780_DELAY_1640US();

#ifdef HD44780_DUAL
	for (device_counter = 0; device_counter <= 1; device_counter++)
	{
		hd44780_device = device_counter;
#endif
		hd44780_put_cmd(0x28 /* 2 lines, 5x7 font */
#ifndef HD44780_4BIT
				| 0x10
#endif
				);
		hd44780_put_cmd(0x08); /* display off, cursor off, cursor blink off */
		hd44780_clear();
		hd44780_put_cmd(0x0c); /* display on, cursor off, cursor blink off */
		hd44780_put_cmd(0x06); /* increment cursor; don't shift display */
#ifdef HD44780_DUAL
	}
#endif
}
