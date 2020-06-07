#include <VirtualWire.h>
/*
PlayerArduino's reset pin to 4
*/

int resetPin = 4;
void RFrxSetup()
{
	vw_set_ptt_inverted(true); // Required for DR3100
	vw_set_rx_pin(12);
	vw_setup(500); // Bits per sec
	vw_rx_start(); // Start the receiver PLL running
}

void setup()
{
	RFrxSetup();
	pinMode(resetPin, OUTPUT);
	digitalWrite(resetPin, 0);
}
void loop()
{
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	if (vw_get_message(buf, &buflen))
	{
		if ((char)buf[0] == '5')
		{
			if ((char)buf[1] == '0' )
			{
				digitalWrite(resetPin, 0);
			}
			if ((char)buf[1] == '1' )
			{
				digitalWrite(resetPin, 1);
			}

		}

	}


}
