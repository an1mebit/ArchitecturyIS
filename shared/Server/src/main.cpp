#include "system.h"
#include "event.h"
#include "camera.h"
#include "generator.h"

int main()
{   
	System* robot = new System(new Camera(), new Generator(new UDPExchanger('s')));

	IEvent* eventReceiver = new ConsoleEvent();
	Event event = Event::NONE;
	
	while (event != Event::EXIT)
	{
		event = eventReceiver->getEvent();
		
		robot->processEvent(event);
	}
	
    return 0;
}