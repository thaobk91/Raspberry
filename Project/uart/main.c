
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
	int fd ;
	char Buffer[100];
	int BuffLenght = 0;

	if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
	{
		printf ("Unable to open serial device\n");
		return 1 ;
	}

	while(1)
	{
		while(serialDataAvail(fd))
		{
			char c = serialGetchar(fd);
			fflush (stdout);

			if(c != '!')
				Buffer[BuffLenght++] = c;
			else
				break;
		}

		if(strcmp(Buffer, "abc") == 0)
			serialPuts(fd, "Hello world\r\n");

		memset(Buffer, 0, BuffLenght);
		BuffLenght = 0;
	}

	return 0 ;
}










