#define PCLK	80000000
void init_uart0(unsigned int baud);
void send_uart0(unsigned char byte);
void sendstr_uart0(char str[]);
void sendstrl_uart0(unsigned char str[], int length);
void sendint4_uart0(signed short data);
void sendint8_uart0(long data);


