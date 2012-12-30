#include <AccelStepper.h>

AccelStepper stepper; // Defaults to FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);
}

void loop()
{
  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
	stepper.moveTo(-stepper.currentPosition());
  
  stepper.run();
}
