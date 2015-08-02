#include "SPI.h"
#include "DMD.h"
#include "TimerOne.h"
#include "mp3.h"
#include "DistanceSensor.h"
#include "Arial_black_16.h"
// you can remove the fonts if unused
#include "SystemFont5x7.h"
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
/* change these values if you have more than one DMD connected */
DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN);

typedef enum
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4
} Player_t;


void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup()
{
   Timer1.initialize( 5000 );
///*period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.*/
//
   Timer1.attachInterrupt( ScanDMD );
///*attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()*/
//
   dmd.clearScreen( true );
/* true is normal (all pixels off), false is negative (all pixels on) */

//   Serial.begin(9600);
//   Serial.println("power on");
   delay(1000);
//   Serial.println("init");


   if (mp3.init()==false)
   {
//	   Serial.println("wtf 1");
   }

//   if (mp3.SetPlayMode(PLAYMODE_SINGLE)==false)
//   {
//	   Serial.println("wtf 2");
//   }

//   if (mp3.SelectTrack(1)==false)
//   {
//	   Serial.println("wtf 3");
//   }
//   if (mp3.PauseResume()==false)
//   {
//	   Serial.println("wtf 2");
//   }





//   mp3.PauseResume();

   pinMode(1,INPUT_PULLUP);
   pinMode(0,OUTPUT);
   digitalWrite(0,LOW);
   d1.init();
   d2.init();
   d3.init();
   d4.init();
//   Serial.begin(9600);


}


bool buttonPress()
{
	return digitalRead(1)==LOW;
}


void playIAmTheChampion()
{

}


void loopLogo(void)
{
   while(true)
   {
//   char test[4] = "LOL";
	   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
	   dmd.clearScreen( true );
	   dmd.selectFont(Arial_Black_16);
	   dmd.drawMarquee("BONGR.CA",8,(32*DISPLAYS_ACROSS)-1,0);
	   long start=millis();
	   long timer=start;
	   boolean ret=false;
	   while(!ret){
		 if ((timer+30) < millis()) {
		   ret=dmd.stepMarquee(-1,0);
		   timer=millis();
		   if (buttonPress() && (timer - start) > 500)
		   {
			   return;
		   }
		 }
	   }
   }


}


void loopGetReady()
{
	while (true)
	{
		dmd.clearScreen( true );
		dmd.selectFont(Arial_Black_16);
		dmd.drawMarquee("POUR YOUR DRINKS!",17,(32*DISPLAYS_ACROSS)-1,0);
		long start=millis();
		long timer=start;
		boolean ret=false;
		while(!ret){
		 if ((timer+30) < millis()) {
		   ret=dmd.stepMarquee(-1,0);
		   timer=millis();
		   if (buttonPress() && (timer - start) > 500)
		   {
			   return;
		   }
		 }
		}
	}
}

void loop321()
{
	dmd.clearScreen( true );
	dmd.selectFont(Arial_Black_16);
	dmd.drawMarquee("3....2....1....",15,(32*DISPLAYS_ACROSS)-1,0);
	long start=millis();
	long timer=start;
	boolean ret=false;
	while(!ret){
	 if ((timer+30) < millis()) {
	   ret=dmd.stepMarquee(-1,0);
	   timer=millis();
	 }
	}

	dmd.clearScreen(true);
	delay(500);
	for(int i=0;i<5;i++)
	{
	dmd.drawString(0,0,"GO!!!",5,GRAPHICS_NORMAL);
	delay(50);
	dmd.drawString(0,0,"GO!!!",5,GRAPHICS_INVERSE);
	delay(50);
	}

}


void drawColumn(int player,int height)
{
	//32 pixels = 8 pixels wide each
	int x1=player*8 + 0;
	int y1=16-height;
	if (y1 < 0)
		y1 = 0;
	if (y1>16)
		y1=16;
	int x2=(player*8) +1;
	int y2=16;
	dmd.drawFilledBox(  x1,  y1, x2, y2, GRAPHICS_NORMAL );
}

int convertHeight(float in)
{
//	static int x = 16;
//	static const float MAX_HEIGHT = 43;
//	static const float OFFSET = 23.75;


	//in is the reading
	//small reading = more beer left

	//values based on calibration
	float slope = (0.0 - 16.0)/(43.0  -23.75);
	float intercept = 35.75;

	int ret = (int)(slope*in + intercept);

	if (ret > 16)
		ret = 16;
	if (ret < 0)
		ret = 0;

	return ret;
}
Player_t loopDrink()
{
	int p1Height = 0;
	int p2Height = 0;
	int p3Height=0;
	int p4Height=0;
	int x=0;

	//get start values

	int p1Start = convertHeight(d1.measure());
	int p2Start = convertHeight(d2.measure());
	int p3Start = convertHeight(d3.measure());
	int p4Start = convertHeight(d4.measure());
	const int MIN_START = 4;
	const int END = 1;
	while (true)
	{
		x++;
		dmd.clearScreen(true);

		p1Height = convertHeight(d1.measure());
		p2Height = convertHeight(d2.measure());
		p3Height = convertHeight(d3.measure());
		p4Height = convertHeight(d4.measure());

		drawColumn(0,p1Height);
		drawColumn(1,p2Height);
		drawColumn(2,p3Height);
		drawColumn(3,p4Height);
//		delay(100);
		if ((p1Start > MIN_START) and (p1Height <= END))
			return PLAYER_1;
		if ((p2Start > MIN_START) and (p2Height <= END))
			return PLAYER_2;
		if ((p3Start > MIN_START) and (p3Height <= END))
			return PLAYER_3;
		if ((p4Start > MIN_START) and (p4Height <= END))
			return PLAYER_4;

		delay(25);
		if (buttonPress())
			return PLAYER_1;
	}
	return PLAYER_1;

}

void loopWinner(Player_t winner)
{
	char string[15] = "PLAYER 0 WINS!";
	string[7]=winner+'1';

	dmd.clearScreen( true );
	   dmd.selectFont(Arial_Black_16);
	   dmd.drawMarquee(string,15,(32*DISPLAYS_ACROSS)-1,0);
	   long start=millis();
	   long timer=start;
	   boolean ret=false;
	   while(!ret){
	     if ((timer+40) < millis()) {
	       ret=dmd.stepMarquee(-1,0);
	       timer=millis();
	     }
	   }
}

void loop()
{
	//1 homer
	//2 danger
	//3 fatality
	//4 acdc

	loopLogo();
	mp3.SetPlayMode(PLAYMODE_SINGLE);

	static int song = 0;

	switch (song)
	{
	case 0:
		mp3.SelectTrack(2);
		break;
	case 1:
		mp3.SelectTrack(4);
		break;
	case 2:
		mp3.SelectTrack(5);
		break;
	case 3:
		mp3.SelectTrack(7);
		break;
	}
	song = (song + 1)%4;
	loopGetReady();
	loop321();
	Player_t winner = loopDrink();

//	mp3.SetPlayMode(PLAYMODE_SINGLE);

	static int winSound = 0;

	switch (winSound)
	{
	case 0:
		mp3.SelectTrack(1);
		break;
	case 1:
		mp3.SelectTrack(3);
		break;
	case 2:
		mp3.SelectTrack(6);
		break;
	}
	winSound = (winSound + 1 )%3;
	loopWinner(winner);


}

