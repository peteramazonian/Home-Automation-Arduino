#include <VirtualWire.h>

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
	Serial.begin(9600);
}

void loop()
{
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	if (vw_get_message(buf, &buflen)) 
	{
		for (int i = 0; i < 2; i++)
		{
			Serial.write((char)buf[i]);
		}

	}

}