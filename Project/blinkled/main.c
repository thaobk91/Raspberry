
#include <stdio.h>
#include <wiringPi.h>


#define BUTTON_PIN 				0

int eventCounter = 0;
void vButtonHandle(void)
{
	eventCounter++;
	//printf("Button event!\r\n");
}


int main(void)
{
    wiringPiSetup();
	
	wiringPiISR(BUTTON_PIN, INT_EDGE_FALLING, &vButtonHandle);

    pinMode(2, OUTPUT);
	//pullUpDnControl (BUTTON_PIN, PUD_UP);

    while(1)
    {
		printf( "counter. = %d\n", eventCounter );
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }

    return 0;
}