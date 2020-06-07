#include <IRremote.h>
#include <VirtualWire.h>
/*
IR pin 7
RF pin 12
lamp pins 3,4
delay 3s

*/
char *controller;
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
const int redPin = 4;
const int greenPin = 3;
int LEDstate = 1;
int LEDstate2 = 1;
void setup() {
	vw_set_ptt_inverted(true); //
	vw_set_tx_pin(12);
	vw_setup(500);// speed of data transfer Kbps
	irrecv.enableIRIn();
	irrecv.blink13(true);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	Serial.begin(9600);
}
void transmitter()
{
	if (LEDstate == 1 && LEDstate2 == 1)
		controller = "44";
	if (LEDstate == 0 && LEDstate2 == 1)
		controller = "54";
	if (LEDstate == 1 && LEDstate2 == 0)
		controller = "45";
	if (LEDstate == 0 && LEDstate2 == 0)
		controller = "55";
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx();
}
void loop() {

	if (millis() % 3000 <= 10)
	{
		transmitter();
	}
	if (irrecv.decode(&results))
	{

		switch (results.value)
		{
		case 0xCC00B847:
		{
			LEDstate = !LEDstate;
			transmitter();
			break;
		}
		case 0xCC007887:
		{
			LEDstate2 = !LEDstate2;
			transmitter();
			break;
		}
		case 0xCC0000FF:
		case 0x124:
		{
			LEDstate = 1;
			LEDstate2 = 1;
			transmitter();
			break;
		}
		case 0xCC00E817:
		case 0x123:
		{
			LEDstate = 0;
			LEDstate2 = 0;
			transmitter();
			break;
		}
		}

		irrecv.resume();
	}
	digitalWrite(redPin, LEDstate);
	digitalWrite(greenPin, LEDstate2);
}