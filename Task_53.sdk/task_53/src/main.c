#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "microblaze_sleep.h"
#include "xparameters.h"
#include "xgpio.h"

#define size	128

XGpio GPIO_0;
// declarar XGpio e XGpio instancias
XGpio_Config GPIO_0_conf;


int main() {
	int i;
	unsigned int value=0;
	unsigned int input;
	char *s = "000";
	unsigned int my_array[] = {948,999,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,999,888,777,666,555,444,333,222,111,133,292,339,499,999,677,781,891,98,109,114,127,139,396,777,926,471,911,491,913,163,626,581,591,333,421,345,555,888,272,312,326,334,734,435,836,937,238,239,240,121,59,199,27,98,99,10,99,92,159,163,114,177,101,44,55,192,58,81,129,193,124,76,38,181,147,182,77,71,17,164,149,193,62,45,81,176,184,165,28,199,1,199,1,199,1,199,1,199,1,199,1,199,15,12,9,98,9,134,14,15,16,7,2,6,1,4,7,18,1,5,20,21,22,23,24,25,15,15,15,101,199,102,198,103,197,104,196,105,195,111,189,122,184,137,136,135,134,144,141,190,120,170,60,70,30,50,111,981,141,171,121,66,193,118,125,173,176,180,169,187,165,181,101,577,153,159,679,144,155,799,177,139,152,799,179};

	GPIO_0_conf.BaseAddress = XPAR_AXI_GPIO_0_BASEADDR;
	GPIO_0_conf.DeviceId = XPAR_GPIO_0_DEVICE_ID;
	GPIO_0_conf.IsDual = XPAR_GPIO_0_IS_DUAL;


	XGpio_CfgInitialize(&GPIO_0, &GPIO_0_conf, GPIO_0_conf.BaseAddress);
	init_platform();
	print("Data sort in hardware\n\r");

	for(i=0;i<size;i++) {
		value = 0xe0000000 | (i<<16) |  my_array[i];
		XGpio_DiscreteWrite(&GPIO_0, 1, value);
	}

	value = 0x20000000;
	// Para reset Unroll ROM
	XGpio_DiscreteWrite(&GPIO_0, 1, value);
	MB_Sleep(10);
	value = 0;

	// reset est� passivo
	XGpio_DiscreteWrite(&GPIO_0, 1, value);
	MB_Sleep(10);

	for(i=0; i<size; i++) {
		// 0x000303FF - m�scara (100 palavras)
		XGpio_DiscreteWrite(&GPIO_0, 1, (i<<16) & 0x00FF0000); // selecionar o endere�o de RAM
		input = XGpio_DiscreteRead(&GPIO_0, 2);
		s[2] = (char)((input%10)+0x30);
		s[1] = (char)(((input/10)%10)+0x30);
		s[0] = (char)(input/100+0x30);
		print("data = ");
		print(s);
		print("\n");
	}

	print("The program has been terminated\n\r");
	cleanup_platform();
	return 0;
}*/
