#include "Arduino.h"
#include "DistanceSensor.h"
/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/


DistanceSensor::DistanceSensor(int t, int e)
{
	trigPin=t;
	echoPin=e;

}

void DistanceSensor::init()
{
	pinMode(trigPin,OUTPUT);
	pinMode(echoPin,INPUT);
}

float DistanceSensor::measure()
{
	long duration, distance;

	digitalWrite(trigPin,LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin,LOW);

	duration = pulseIn(echoPin,HIGH);

	distance = (duration/2) / 29.1;

	return distance;
}

DistanceSensor d1(2,3);
DistanceSensor d2(2,3);
DistanceSensor d3(2,3);
DistanceSensor d4(2,3);



