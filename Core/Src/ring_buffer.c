#include "ring_buffer.h"


RB_Status RB_Write(RingBuffer_t * buff, uint8_t value)
{
	uint8_t headTmp = (buff->head + 1) % RING_BUFFER_SZIE;

	if(headTmp == buff->tail)
	{
		return RB_ERROR;
	}

	buff->buffer[buff->head] = value;

	buff->head = headTmp;

	return RB_OK;
}

RB_Status RB_Read(RingBuffer_t * buff, uint8_t * value)
{
	if( buff->head == buff->tail)
	{
		return RB_ERROR;
	}

	*value = buff->buffer[buff->tail];

	buff-> tail = (buff->tail + 1) % RING_BUFFER_SZIE;

	return RB_OK;
}

void RB_Flush(RingBuffer_t * buff)
{
	buff->head = 0;
	buff->tail = 0;
}
