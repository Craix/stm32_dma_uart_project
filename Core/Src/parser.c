#include "parser.h"

static char myName[32] = "No name";
char buff[32];

bool ledStatus[4];

void RB_to_command(RingBuffer_t * buff, uint8_t *destination)
{
	uint8_t tmp = 0;
	uint8_t i = 0;

	  do
	  {
		  RB_Read(buff, &tmp);

		  if(tmp == ENDLINE)
		  {
			  destination[i] = 0;
		  }
		  else
		  {
			  destination[i] = tmp;
		  }

		  i++;
	  }
	  while(tmp != ENDLINE);
}

void parse_LED(void)
{
	int ledID = -1;

	char *parsPointer = strtok(NULL, ",");

	if(strlen(parsPointer) > 0)
	{
		for(int j = 0; parsPointer[j] != 0; j++)
		{
			if((parsPointer[j] < '0'|| parsPointer[j] > '9'))
			{
				UART_tx("Wrong led ID\r\n");
				return;
			}
		}

		ledID = atoi(parsPointer);

		if(ledID < 0 || ledID > 3)
		{
			UART_tx("Wrong led ID\r\n");
			return;
		}
	}

	parsPointer = strtok(NULL, "");

	if(strlen(parsPointer) > 0)
	{
		if(parsPointer[0] < '0'|| parsPointer[0] > '1')
		{
			UART_tx("Led wrong value please type 0 or 1 \r\n");
			return;
		}

		int status = atoi(parsPointer);

		if( status != ledStatus[ledID])
		{
			sprintf(buff, "LedID = %d, new status = %d\r\n", ledID, status);
			UART_tx(buff);

			ledStatus[ledID] = status;
		}
		else
		{
			sprintf(buff, "Same status, nop\r\n");
			UART_tx(buff);
		}
	}

}

static void parse_NAME()
{
	char *parsPointer = strtok(NULL, "");
	char message[64];

	if(strlen(parsPointer) > 0)
	{
		if(strcmp("?", parsPointer) == 0)
		{
			sprintf(message, "My name is %s \r\n", myName);
			UART_tx(message);
		}
		else
		{
			if(strlen(parsPointer) > 32)
			{
				UART_tx("Name too long (less then 32) \r\n");
				return;
			}

			strcpy(myName, parsPointer);
			sprintf(message, "My new name is %s  \r\n", myName);
			UART_tx(message);

		}
	}
	else
	{
		UART_tx("Name cannot be empty! \r\n");
	}
}



//NAME=? to see actual name
//NAME = "" to set new name
//LED=1,1 led

void comandParser(uint8_t * cmd)
{
	char *parsPointer = strtok((char*)cmd, "=");

	if(strcmp("LED", (char*)parsPointer) == 0)
	{
		parse_LED();
	}

	if(strcmp("NAME", (char*)parsPointer) == 0)
	{
		parse_NAME();
	}
}
