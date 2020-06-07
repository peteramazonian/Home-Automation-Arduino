/*
CS ---------------------->> 10
SCK ---------------------->> 13
MOSI -------------------->> 11
MISO--------------------->> 12
VCC --------------------->> +5v
GND--------------------->> Arduino's Ground

speaker ---------------->> 9
*/
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

void setup()
{
	tmrpcm.speakerPin = 9;
	Serial.begin(9600);
	if (!SD.begin(SD_ChipSelectPin))
	{
		Serial.println("SD fail");
		return;
	}
	tmrpcm.setVolume(6);

}

void loop() {
	tmrpcm.play("music.wav");
	tmrpcm.play("music2.wav");
}
