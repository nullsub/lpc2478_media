#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"

#include <string.h>
#include "terminal.h"

//extern xQueueHandle uart_receive_queue;

static int get_word(char *buffer, char *source, const int length)
{
	int currnt_length = 0;
	int skipped_chars = 0;
	while (*source == ' ') {
		source += sizeof(char);
		skipped_chars ++;
	}
	while (*source != 0x00 && *source != ' ' && currnt_length < length) {
		*buffer = *source;
		buffer += sizeof(char);
		source += sizeof(char);
		currnt_length ++;
	}
	*buffer = 0x00;
	return  currnt_length + skipped_chars;
}

int add_cmd(char *cmd_name, void (*func) (char *args));
int parse_cmd(char *cmd);
void cmd_help(char *args);
void cmd_status(char *args);

struct cmd {
	void (*func) (char *args);
	char *name;
	void *next;
};

static int nr_of_cmds;
static struct cmd *first_cmd;

void debug_msg(char *msg)
{
	tprintf("DEBUG: ");
	tprintf(msg);
	tprintf("\n");
}

void serial_task(void *pvParameters)	//term-task
{
	char crrnt_cmd[TERM_CMD_LENGTH];
	int crrnt_cmd_i = 0;

	tprintf("MEDIA PLAYER --- chrisudeussen@gmail.com\n");

	add_cmd("help", cmd_help);
	add_cmd("status", cmd_status);

	char ch;

	tprintf("\n$");
	for (;;) {
		//xQueueReceive(uart_receive_queue, &ch, portMAX_DELAY); //blocking
		switch (ch) {
			case '\b':
				if (crrnt_cmd_i > 0) {
					tprintf("%c %c", ch, ch);
					crrnt_cmd_i--;
				}
				break;
			case '\n':
			case '\r':
				tprintf("\n");
				if (crrnt_cmd_i > 0) {
					crrnt_cmd[crrnt_cmd_i] = 0x00;
					if (parse_cmd(crrnt_cmd))
						tprintf("unknown cmd\n");
				}
				tprintf("$");
				crrnt_cmd_i = 0;
				break;
			default:
				tprintf("%c", ch);
				crrnt_cmd[crrnt_cmd_i] = ch;
				if (crrnt_cmd_i < TERM_CMD_LENGTH - 1)
					crrnt_cmd_i++;
		}
	}
}

void cmd_help(char *args)
{
	tprintf("available commands are:\n");
	tprintf("help - show this help\n");
	tprintf("status - show statistics, free Mem, and running tasks\n");
	return;
}

void cmd_status(char *args)
{
	int free_heap = xPortGetFreeHeapSize();
	tprintf("Free Heap: %i of %i bytes used; %i%% full\n",
			free_heap, configTOTAL_HEAP_SIZE,
			((free_heap*100)/configTOTAL_HEAP_SIZE));
}

//char *args is <cmd_name> <arg1> <arg2> ...
#define ARG_LENGTH	15 

int parse_cmd(char *cmd)
{
	char cmd_name[ARG_LENGTH];

	// get command name
	int length = get_word(cmd_name, cmd, ARG_LENGTH);
	if (length == 0) {
		return -1;
	}
	//get command function
	struct cmd *crrnt_cmd = first_cmd;
	for (int i = 0; i < nr_of_cmds; i++) {
		if (strcmp(cmd_name, crrnt_cmd->name) == 0) {
			crrnt_cmd->func(cmd);
			return 0;
		}
		crrnt_cmd = crrnt_cmd->next;
	}
	return -1;
}

int add_cmd(char *cmd_name, void (*func) (char *args))
{
	struct cmd *crrnt_cmd;

	if (nr_of_cmds == 0) {
		first_cmd = (struct cmd *)pvPortMalloc(sizeof(struct cmd));
		if (first_cmd == NULL) {
			return -1;
		}
		crrnt_cmd = first_cmd;
	} else {
		crrnt_cmd = first_cmd;
		for (int i = nr_of_cmds - 1; i > 0; i--) {
			crrnt_cmd = crrnt_cmd->next;
		}
		crrnt_cmd->next =
			(struct cmd *)pvPortMalloc(sizeof(struct cmd));
		if (crrnt_cmd->next == NULL) {
			return -1;
		}

		crrnt_cmd = crrnt_cmd->next;
	}

	crrnt_cmd->name = cmd_name;
	crrnt_cmd->func = func;
	crrnt_cmd->next = NULL;

	nr_of_cmds++;
	return 0;
}

