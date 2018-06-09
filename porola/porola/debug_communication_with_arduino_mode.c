#include "iodefine.h"
#include "vect.h"
#include "motor.h"
#include "servo.h"
#include "release_ball.h"
#include "rxpi.h"
#include "distance_measure.h"
#include "run_mode.h"

#ifdef DEBUG_COMMUNICATION_WITH_ARDUINO_MODE

void main(void)
{
	//init
	pattern = none;
	rx_state = STOP_;
	init_motor();
	init_servo();
	init_ADC();
	init_UART();
	init_CMT();
	init_PORT_for_Arduino();
	init_horn();

	// start_CMT0(); //for linetrace

	start_ADC0(); //for linetrace
	start_ADC1(); //for distance sencer

	//start linetrace
	//pattern = tracing;
	//start searching
	//pattern = searching;
	InArduino = 0;

	while(1)
	{
		if(InArduino == 1){
			InArduino = 1;
		}
		else{
			InArduino = 0;
		}

		rprintf("InArduino:%d\r\n",InArduino);
	}

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
#endif
