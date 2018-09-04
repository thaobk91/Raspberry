
#include <wiringPi.h>


#define GPIO_BLINK 				27

int main(void)
{
    wiringPiSetupGpio();

    pinMode(GPIO_BLINK, OUTPUT);

    while(1)
    {
        digitalWrite(GPIO_BLINK, HIGH);
        delay(500);
        digitalWrite(GPIO_BLINK, LOW);
        delay(500);
    }

    return 0;
}










