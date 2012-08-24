#include "uart.h"
#include "lpc24xx.h"

void init_uart0(unsigned int baud)
{
	PINSEL0 |= (1<<4)|(1<<6);
	U0FCR = 7; // Enable and clear FIFO's
	U0LCR = 0x83; // 8N1, dis Divisor latch bit
	U0DLL = ((PCLK/16)/baud)%256;
	U0DLM = ((PCLK/16)/baud)/256;
	U0LCR = 3; // Disable Divisor latch bit
}

void send_uart0(unsigned char byte){
	while (!(U0LSR & 0x20)); 
	U0THR = byte;
}

void sendstr_uart0(char str[]){
	int i = 0;
	while(str[i] != 0){
		send_uart0(str[i++]);
	}
}

void sendstrl_uart0(unsigned char str[], int length){
	int i = 0;
	for (i=0;i<length;i++){
		send_uart0(str[i++]);
	}
}

void sendint4_uart0(signed short data)
  {
    unsigned char byt;
	byt = data / 1000;
	data = data - byt * 1000;
	send_uart0(byt + 48);
	byt = data / 100;
	data = data - byt * 100;
	send_uart0(byt + 48);
	byt = data / 10;
	data = data - byt * 10;
	send_uart0(byt + 48);
	send_uart0(data + 48); 
}

void sendint8_uart0(long data)
  {
    unsigned char byt;
    byt = data / 10000000;
	data = data - byt * 10000000;
	send_uart0(byt + 48);

    byt = data / 1000000;
	data = data - byt * 1000000;
	send_uart0(byt + 48);

    byt = data / 100000;
	data = data - byt * 100000;
	send_uart0(byt + 48);

    byt = data / 10000;
	data = data - byt * 10000;
	send_uart0(byt + 48);

	byt = data / 1000;
	data = data - byt * 1000;
	send_uart0(byt + 48);

	byt = data / 100;
	data = data - byt * 100;
	send_uart0(byt + 48);

	byt = data / 10;
	data = data - byt * 10;
	send_uart0(byt + 48);
	send_uart0(data + 48); 
}
