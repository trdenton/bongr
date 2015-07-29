#ifndef __DISTANCE_SENSOR_H__
#define __DISTANCE_SENSOR_H__

//ultrasonic rangefinder
class DistanceSensor
{
private:
	int trigPin;
	int echoPin;
public:
	DistanceSensor(int trigPin, int echoPin);
	void init();

	//return distance in cm
	float measure();

};


extern DistanceSensor d1;
extern DistanceSensor d2;
extern DistanceSensor d3;
extern DistanceSensor d4;

#endif
