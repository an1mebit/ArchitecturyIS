#pragma once

#include "event.h"
#include "camera.h"
#include "generator.h"

enum class SystemState
{
	STARTING,
	WORKING,
	STARTING_GENERATOR,
	STOPPING_GENERATOR,
	STOPPING,
	OFF,
	ERROR
};

class System
{
private:
	Camera* camera;
	IGenerator* generator;
	
	SystemState state;
    float x = 0;
    float y = 0;
public:
	System(Camera* cp, IGenerator* gp);

	void processEvent(const Event& event);
	int Run();
	int TurnOn();
	int TurnOff();
    int getCoordinate();
};