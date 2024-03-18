#include "main.h"

#ifndef SRC_RING_BUFFER_H_
#define SRC_RING_BUFFER_H_

#define RING_BUFFER_SZIE 32

//status
typedef enum
{
	RB_OK 		= 0x00U,
	RB_ERROR	= 0x01U
}RB_Status;

//object
typedef struct
{
	uint8_t buffer[RING_BUFFER_SZIE];

	uint16_t head;
	uint16_t tail;

}RingBuffer_t;

//write
RB_Status RB_Write(RingBuffer_t * buff, uint8_t value);

//read
RB_Status RB_Read(RingBuffer_t * buff, uint8_t * value);

//flush
void RB_Flush(RingBuffer_t * buff);


#endif /* SRC_RING_BUFFER_H_ */
