#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "typedefine.h"
#include "iodefine.h"
#include "rxpi.h"

/*
	Motor 1 W1
		motor direction
			P50 CN2-33
			P51 CN2-34
		motor PWM
			PA1 CN2-2
	
	Motor 2 W2
	  motor direction
			P55 CN2-38
			P54 CN2-37
		motor PWM
			PB0 CN2-9
*/

#define W1 1
#define W2 2

#define MOTOR_1_CW    PORT5.DR.BIT.B1 = 1; PORT5.DR.BIT.B0 = 0;
#define MOTOR_1_CCW   PORT5.DR.BIT.B1 = 0; PORT5.DR.BIT.B0 = 1;
#define MOTOR_1_BREAK PORT5.DR.BIT.B1 = 1; PORT5.DR.BIT.B0 = 1;

#define MOTOR_2_CW    PORT5.DR.BIT.B4 = 1; PORT5.DR.BIT.B5 = 0;
#define MOTOR_2_CCW	  PORT5.DR.BIT.B4 = 0; PORT5.DR.BIT.B5 = 1;
#define MOTOR_2_BREAK PORT5.DR.BIT.B4 = 1; PORT5.DR.BIT.B5 = 1;

//#define MOTOR_GEAR 248.98
//#define ENCODER_COUNT_PER_ROT 3

#define MOTOR_GEAR 19.2
#define ENCODER_COUNT_PER_ROT 500.0

#define PROPORTIAL_GAIN  0.03
#define DIFFERENTIAL_GAIN 0.02*0.02*2.0
#define BODY_WIDTH   0.262f //[m]
#define WHEEL_RADIUS 0.030f //[m]

#define deg2rad(deg) (((deg)/360.0)*2.0*PI)
#define rad2deg(rad) (((rad)/2.0/PI)*360.0)

static float rad2enc(float rad){
  return ( rad  / (2.0 * PI)  * MOTOR_GEAR * (ENCODER_COUNT_PER_ROT * 4.0));
}

static float enc2rad(float enc){
  return ( enc  * (2.0 * PI)  * MOTOR_GEAR * (ENCODER_COUNT_PER_ROT * 4.0));
}

typedef struct {
	float cnt;
	float goal_cnt;
	int16_t raw_current_cnt;
	int16_t raw_last_cnt;
	int16_t raw_update_cnt;
	float traj_current_diff;
	float traj_last_diff;
	float traj_total_diff;
} ENCODER;

extern ENCODER encoder1;
extern ENCODER encoder2;
extern ENCODER encoder3;
extern ENCODER encoder4;

#define Black 1
#define White 0

// Photo reflector
#define Ph0 PORT4.PORT.BIT.B0
#define Ph1 PORT4.PORT.BIT.B1
#define Ph2 PORT4.PORT.BIT.B2
#define Ph3 PORT4.PORT.BIT.B3

// common parameter
#define SampTime 20     //[ms]
#define RsampTime 0.02 	//[s]

// prototype declaration
void motor( int no, int duty );
void init_motor();
void start_linetrace(void);
void start_return_linetrace(void);
void linetrace(void);
void increse_line_count();
int  line_state_scan();
void forthline_and_arduino_scan();

void traj_tracking(float distance, float degree,float time);
void make_traj(int no, float rad, float time );
void make_traj_with_distance_degrees();
void start_tracking(void (*delegate)(void));
void stop_tracking();
void update_enc_count(void);
void pd_control(void);

// 
int get_loop_count(void);

// sci
extern void    charput(uint8_t output_char);
extern uint8_t charget(void);
extern void    rprintf(char * fmt, ...);
extern int     getLine (char* str, unsigned int len);
extern int     putLine (char* str);

#endif
