#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "ring_buffer.h"
#include "string.h"
#include "uartLog.h"
#include <stdbool.h>
#include "stdio.h"
#include <stdlib.h>

#define ENDLINE '\n' //znak końca lini

extern bool ledStatus[4];

void RB_to_command(RingBuffer_t * buff, uint8_t *destination);
void comandParser(uint8_t * cmd);

#endif /* INC_PARSER_H_ */
