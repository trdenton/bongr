#ifndef __MP3_H__
#define __MP3_H__
#include "SoftwareSerial.h"

typedef enum
{
	PLAYMODE_SINGLE=0x00,
	PLAYMODE_REPEAT=0x01,
	PLAYMODE_PLAYLIST=0x02,
	PLAYMODE_RANDOM=0x03

}PlayMode_t;



class Mp3Player: public SoftwareSerial
{
//private:
//	SoftwareSerial ser;
public:
	bool init();
	bool SelectTrack(int index);
	bool PauseResume(void);
	bool SetVolume(uint8_t);
	bool SetPlayMode(PlayMode_t);
	Mp3Player(int rx,int tx);
};

extern Mp3Player mp3;
#endif
