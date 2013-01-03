#ifndef SIM_H
#define SIM_H

#include <LCD.h>

#ifdef SIM
extern LCD *sim_lcd;
#define lcd (*sim_lcd)
#else
extern LCD lcd;
#endif

#endif
