#ifndef _HD44780_H_
#define _HD44780_H_

#include "hd44780_settings.h"

#ifndef HD44780_DATA
	#error Define HD44780_DATA as LATx or PORTx
#endif
#ifndef HD44780_DATA_TRIS
	#error Define HD44780_DATA_TRIS as TRISx
#endif
#ifdef HD44780_4BIT
	#ifndef HD44780_DATA_SHIFT
		#error You are using the 4-bit interface; define HD44780_DATA_SHIFT(x) as x << 4 or x & 0x0f
	#endif
	#ifndef HD44780_DATA_R7
		#error You are using the 4-bit interface; define HD44780_DATA_R7(x) as x >> 7 or something like that
	#endif
#endif

#ifndef HD44780_RS
	#error Define HD44780_RS as LATxbits.LATxn or PORTxbits.RBn
#endif
#ifndef HD44780_RS_TRIS
	#error Define HD44780_RS_TRIS as TRISxbits.TRISxn
#endif
#ifndef HD44780_RW
	#error Define HD44780_RW as LATxbits.LATxn or PORTxbits.RBn
#endif
#ifndef HD44780_RW_TRIS
	#error Define HD44780_RW_TRIS as TRISxbits.TRISxn
#endif

#ifdef HD44780_DUAL
	#ifndef HD44780_E1
		#error Define HD44780_E1 as LATxbits.LATxn or PORTxbits.RBn
	#endif
	#ifndef HD44780_E1_TRIS
		#error Define HD44780_E1_TRIS as TRISxbits.TRISxn
	#endif

	#ifndef HD44780_E2
		#error Define HD44780_E2 as LATxbits.LATxn or PORTxbits.RBn
	#endif
	#ifndef HD44780_E2_TRIS
		#error Define HD44780_E2_TRIS as TRISxbits.TRISxn
	#endif
#else
	#ifndef HD44780_E
		#error Define HD44780_E as LATxbits.LATxn or PORTxbits.RBn
	#endif
	#ifndef HD44780_E_TRIS
		#error Define HD44780_E_TRIS as TRISxbits.TRISxn
	#endif
#endif

#ifdef HD44780_4BIT
	#define HD44780_DATA_CAST(x) HD44780_DATA_SHIFT(x)
#else
	#define HD44780_DATA_CAST(x) x
#endif

#ifdef HD44780_DUAL
unsigned char hd44780_device = 0;
#endif

void hd44780_put_char(unsigned char data);
inline void hd44780_clear(void);
inline void hd44780_set_address(unsigned char addr);
void hd44780_init_ports(void);
void hd44780_init(void);

#endif
