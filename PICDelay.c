// NB: The folowing delay routines must be calibrated for the CPU / Xtal Frequency being used

#include <p18cxxx.h>
#include <stdlib.h>
#include <timers.h>
#include <delays.h>

void DelayMS(int MilliSeconds)
{
	int i;
	for (i=0; i<MilliSeconds; i++)
	{
		Delay1KTCYx(1);									// 1 msec = 4000 cycles at 16Mhz/4 MIPS
	}
	return;
}
