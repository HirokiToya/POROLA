#ifndef DISTANCE_MEASURE_H
#define DISTANCE_MEASURE_H

#include "iodefine.h"
#include "rxpi.h"
#include "motor.h"
#include "servo.h"


#define MaxCount 9

void set_start_pos();
void start_search();
void search();
void stop_turning();
int  get_distance();
void set_recursion();
void start_recursion();

#endif