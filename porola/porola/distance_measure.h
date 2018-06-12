#ifndef DISTANCE_MEASURE_H
#define DISTANCE_MEASURE_H

#include "iodefine.h"
#include "rxpi.h"
#include "motor.h"
#include "servo.h"
#include "communicate_arduino.h"


#define MaxCount 9

void set_start_position();
void set_second_position();
void start_search();
void start_second_lap_search();
void search();
void stop_turning();
int  get_distance();


#endif