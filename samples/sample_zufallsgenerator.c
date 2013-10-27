#include "pollinspiel.h"

int main(void)
{
	init();

	uint8_t led = LED1;
	while(1)
	{
		int randnum = 0;
		while(!getbutton(BUTTON5))
		{
			randnum++;
		}
		setledByNum(led, LED_OFF);

		led = LED1;
		int delay = randnum % 200;
		while(delay < 500)
		{
			setledByNum(led, LED_OFF);
			led++;
			setledByNum(led, LED_ON);

			delay += 10;
			if (led > 4) led = 1;
			waitms(delay);
		}

		sound(1000, 500);
	}
	

	done();
}
