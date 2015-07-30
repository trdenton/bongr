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

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup()
{
   Timer1.initialize( 5000 );
/*period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.*/

   Timer1.attachInterrupt( ScanDMD );
/*attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()*/

   dmd.clearScreen( true );
/* true is normal (all pixels off), false is negative (all pixels on) */

//   mp3.init();

   pinMode(A0,INPUT);
   d1.init();
   d2.init();
   d3.init();
   d4.init();
   Serial.begin(9600);


}


bool buttonPress()
{
	return digitalRead(A0)==LOW;
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
void displayReadyPlayer(int n)
{
	char string[16] = "READY PLAYER 0!";
	string[13]=n+'0';

	dmd.clearScreen( true );
	   dmd.selectFont(Arial_Black_16);
	   dmd.drawMarquee(string,15,(32*DISPLAYS_ACROSS)-1,0);
	   long start=millis();
	   long timer=start;
	   boolean ret=false;
	   while(!ret){
	     if ((timer+20) < millis()) {
	       ret=dmd.stepMarquee(-1,0);
	       timer=millis();
	     }
	   }
}

void displayPlayerWins(int n)
{

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
	int y1=height;
	int x2=(player*8) +1;
	int y2=0;
	dmd.drawFilledBox(  x1,  y1, x2, y2, GRAPHICS_NORMAL );
}
void loopDrink()
{
	while (true)
	{
		dmd.clearScreen(true);
		drawColumn(0,16);
		drawColumn(1,8);
		drawColumn(2,4);
		drawColumn(3,1);
		delay(500);
	}

}

void loopWinner()
{

}
void loop()
{
//	loopLogo();
//	loopGetReady();
//	loop321();
	loopDrink();
	loopWinner();






//
//	float dist = d1.measure();
////	displayReadyPlayer(3);
//	Serial.println(dist);
//	delay(10);
}

