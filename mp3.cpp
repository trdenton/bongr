/*****************************************************************************/
//	Function: control the seeedstudo Grove MP3 player
//      Hardware: Grove - Serial MP3 Player
/*******************************************************************************/
#include <SoftwareSerial.h>
#include "mp3.h"
#include "Arduino.h"
//SoftwareSerial mp3(2, 3);//modify this with the connector you are using.
Mp3Player mp3(4,5);
Mp3Player::Mp3Player(int rx, int tx)
	:SoftwareSerial(rx,tx)
{
}

bool Mp3Player::init()
{

	begin(9600);
//	delay(100);
	if (SetPlayMode(PLAYMODE_SINGLE)!=true)
	{

		return false;

	}
	delay(10);
//	return PauseResume();
	return true;

}


//Set the music index to play, the index is decided by the input sequence
//of the music;
//hbyte: the high byte of the index;
//lbyte: the low byte of the index;
bool Mp3Player::SelectTrack(int index)
{
	uint8_t hbyte = (index>>8) & 0x00FF;
	uint8_t lbyte = (index & 0x00FF);
	/*ser.*/write(0x7E);
	/*ser.*/write(0x04);
	/*ser.*/write(0xA0);
	/*ser.*/write(hbyte);
	/*ser.*/write(lbyte);
	/*ser.*/write(0x7E);
    delay(10);
	while(available())
	{
		if (0xA0==read())
			return true;
		else
			return false;
    }

	 return false;
}
// Pause on/off  the current music
// first time calling shuts off music
//
bool Mp3Player::PauseResume(void)
{
 write(0x7E);
 write(0x02);
 write(0xA3);
 write(0x7E);
 delay(10);
 while(available())
 {
	 if (0xA3==read())
		 return true;
	 else
		 return false;
 }
 return false;
}

//Set the volume, the range is 0x00 to 0x1F
bool Mp3Player::SetVolume(uint8_t volume)
{
 write(0x7E);
 write(0x03);
 write(0xA7);
 write(volume);
 write(0x7E);
 delay(10);
 while(available())
 {
 if (0xA7==read())
 return true;
 else
 return false;
 }
 return false;
}


bool Mp3Player::SetPlayMode(PlayMode_t playmode)
{
  if (((playmode==PLAYMODE_SINGLE)|(playmode==PLAYMODE_REPEAT)|(playmode==PLAYMODE_PLAYLIST)|(playmode==PLAYMODE_RANDOM))==false)
  {
    Serial.println("PlayMode Parameter Error! ");
    return false;
  }
   write(0x7E);
 write(0x03);
 write(0xA9);
 write((uint8_t)playmode);
 write(0x7E);
 delay(10);
 while(available())
 {
 if (0xA9==read())
 return true;
 else
 return false;
 }
 return false;
}
