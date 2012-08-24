#ifndef TERMINAL_H
#define TERMINAL_H

#include "uart.h"

void debug_msg(char *msg);
void serial_task(void *pvParameters);

#define TERM_CMD_LENGTH		20

#endif	
