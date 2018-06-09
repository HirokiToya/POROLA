#include "iodefine.h"
#include "vect.h"
#include "motor.h"
#include "servo.h"
#include "rxpi.h"
#include "distance_measure.h"
#include "run_mode.h"

#ifdef DEBUG_MOTOR_MODE

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
//	init_PORT_for_Arduino();
	init_horn();

	// start_CMT0(); //for linetrace

	// start_ADC0(); //for linetrace
	// start_ADC1(); //for distance sencer

	// traj_tracking(0.30, 0.0, 1.5);

	//start linetrace
	//pattern = tracing;
	//start searching
	//pattern = searching;
	
	while(Ph0==White && Ph1==White && Ph2==White && Ph3==White)
	{
		motor(W1,-40);
		motor(W2,-40);
		if(!(Ph0==White && Ph1==White && Ph2==White && Ph3==White)){
			break;
		}
	}
	

	while(1)
	{
		motor(W1,1);
		motor(W2,1);
		// test MOTOR1
		/*
		for(int i = 0; i<100; i++){
			motor(W1,100);
			motor(W2,1);
			update_enc_count();
			rprintf("enc1:%d   enc2:%d\r\n",encoder1.cnt,encoder2.cnt);
		}
		for(int i = 0; i<100; i++){
			motor(W1,-100);
			motor(W2,1);
			update_enc_count();
			rprintf("enc1:%d   enc2:%d\r\n",encoder1.cnt,encoder2.cnt);
		}
		*/
		// test MOTOR2
		/*
		for(int i = 0; i<100; i++){
			motor(W1,1);
			motor(W2,100);
			update_enc_count();
			rprintf("enc1:%d   enc2:%d\r\n",encoder1.cnt,encoder2.cnt);
		}
		for(int i = 0; i<100; i++){
			motor(W1,1);
			motor(W2,-100);
			update_enc_count();
			rprintf("enc1:%d   enc2:%d\r\n",encoder1.cnt,encoder2.cnt);
		}
		*/
	}

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
#endif