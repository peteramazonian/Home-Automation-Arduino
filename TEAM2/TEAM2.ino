#include <VirtualWire.h>
char *controller = "10";
int LampStatus = 1;
int RelayPin = 3;
int period = 7000;
int lightLevel = 30;

void setup()
{
	pinMode(RelayPin, OUTPUT);
	vw_set_ptt_inverted(true);
	vw_set_tx_pin(12);
	vw_setup(500);
	Serial.begin(9600);
}

void loop()
{
	Serial.println(analogRead(A0));
	if ((millis() % period) < 200)
	{
		vw_send((uint8_t *)controller, strlen(controller));
		vw_wait_tx();
		delay(200);
	}

	int sensor = analogRead(A0);
	if (LampStatus == 1)
	{
		if (sensor < lightLevel)
		{
			delay(90);
			if (sensor < lightLevel)
			{
				LampStatus = 0;
				digitalWrite(RelayPin, LampStatus);
				controller = "11";
				vw_send((uint8_t *)controller, strlen(controller));
				vw_wait_tx();
				delay(90);
			}
		}
	}

	if (LampStatus == 0)
	{
		if (sensor >= lightLevel)
		{
			delay(90);
			if (sensor >= lightLevel)
			{
				LampStatus = 1;
				digitalWrite(RelayPin, LampStatus);
				controller = "10";
				vw_send((uint8_t *)controller, strlen(controller));
				vw_wait_tx();
				delay(90);
			}
		}
	}

}
