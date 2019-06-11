/*
 * FileData.c
 *
 *  Created on: Feb 27, 2018
 *      Author: thaohuyen
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "FileData.h"
#include "main.h"




#define macroFILE_HAQI					"/home/pi/Desktop/EmulatorPQ/HAQI.txt"
#define macroFILE_DAQI					"/home/pi/Desktop/EmulatorPQ/DAQI.txt"




void vFileData_getHAQI( char *HAQI, unsigned char Day, unsigned char Hour )
{
	int fileSrc;
	char Buff[512] = {0};
	unsigned int ui = 0;
	unsigned char isOK = 0;

	memset(HAQI, 0, strlen(HAQI));

	printf("--- FileData: Day = %d, Hour = %d\r\n", Day, Hour);

	fileSrc = open(macroFILE_HAQI, O_RDONLY);
	if(fileSrc < 0)
	{
		printf("--- FileData: get HAQI - cann't open file \"%s\"\r\n", macroFILE_HAQI);
		return;
	}

	ui = 0;

	for(;;)
	{
		char c;
		if(read(fileSrc, (char *)&c, 1) != 1)
			break;
		else if(c == '-')
		{
			if( ((isOK == 0) && (Day == atoi(Buff))) || ((isOK == 1) && (Hour == atoi(Buff))) )
			{
				isOK++;
			}
			memset(Buff, 0, strlen(Buff));
			ui = 0;
		}
		else if(c == '\r')
			continue;
		else if(c == '\n')
		{
			if(isOK == 2)
				break;
			memset(Buff, 0, strlen(Buff));
			ui = 0;
			isOK = 0;
		}
		else
			Buff[ui++] = c;
	}

	//printf("buff = %s\r\n", Buff);

	strcpy(HAQI, Buff);
}




void vFileData_getDAQI( char *DAQI, unsigned char Day, unsigned char Hour )
{
	int fileSrc;
	char Buff[512] = {0};
	unsigned int ui = 0;
	unsigned char isOK = 0;

	memset(DAQI, 0, strlen(DAQI));
	printf("--- FileData: Day = %d, Hour = %d\r\n", Day, Hour);

	fileSrc = open(macroFILE_DAQI, O_RDONLY);
	if(fileSrc < 0)
	{
		printf("--- FileData: get DAQI - cann't open file \"%s\"\r\n", macroFILE_DAQI);
		return;
	}

	ui = 0;
	for(;;)
	{
		char c;
		if(read(fileSrc, (char *)&c, 1) != 1)
			break;
		else if(c == '-')
		{
			if( ((isOK == 0) && (Day == atoi(Buff))) || (isOK == 1) )
			{
				isOK++;
			}
			memset(Buff, 0, strlen(Buff));
			ui = 0;
		}
		else if(c == '\r')
			continue;
		else if(c == '\n')
		{
			if(isOK == 2)
				break;
			memset(Buff, 0, strlen(Buff));
			ui = 0;
			isOK = 0;
		}
		else
			Buff[ui++] = c;
	}

	strcpy(DAQI, Buff);
}
























