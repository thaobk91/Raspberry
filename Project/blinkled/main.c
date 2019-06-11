
#include <wiringPi.h>


/* FUNCTION			BCM			WIRINGPI
 * LED		-		19				24
 * MOSI		-		10				12
 * MISO		-		9				13
 * SCK		-		11				14
 * NSS		-		5				21
 * DIO0		-		6				22
 * */


#define LED_STATUS				24


#define GPIO_BLINK 				27

int main(void)
{
    wiringPiSetupGpio();

    pinMode(LED_STATUS, OUTPUT);

    while(1)
    {
        digitalWrite(LED_STATUS, HIGH);
        delay(500);
        digitalWrite(LED_STATUS, LOW);
        delay(500);
    }

    return 0;
}










