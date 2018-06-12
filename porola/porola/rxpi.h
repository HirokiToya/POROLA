#ifndef RXPI_H
#define RXPI_H

#include <stdint.h>
#include<machine.h>
#include <stdio.h>
#include "iodefine.h"
#include "vect.h"

#define uartNum 2

#ifndef PI
#define PI (3.1415926)
#endif

#define STOP_      		1
#define STOP_REQ_ 	 	2
#define TRAJ_      		3
#define LINE_      		4
#define SEARCH_    		5
#define RECURSION_ 		6
#define RETURN_LINETRACE_ 7
#define LIMITED_LINETRACE_ 8

#define PD0 PORTD.DR.BIT.B0
#define PD1 PORTD.DR.BIT.B1
#define PD2 PORTD.DR.BIT.B2
#define PD3 PORTD.DR.BIT.B3
#define InArduino PORT4.PORT.BIT.B4

typedef enum{
  none,
	waiting,
	tracing,
	set_start_pos,
	set_second_pos,
	searching,
	second_lap_searching,
	return_tracing,
	blue,
	yellow,
	red,
	restart,
	finish

}robotState;

extern int rx_time_milli_sec;
extern int rx_state;
extern robotState pattern;
extern int line_num;
extern int line_flag;
extern int interrupt_count;
extern int search_mode_flag;
extern int search_count;
extern int escape_loop_get_ball;
extern int return_flag;
extern int rap_flag;

//prototype declaration

void init_CMT(void);

void start_CMT0(void);
void stop_CMT0(void);

void start_CMT1(void);
void stop_CMT1(void);

void start_CMT2(void);
void stop_CMT2(void);

void start_CMT3(void);
void stop_CMT3(void);

void init_ADC(void);
void start_ADC0(void);
void stop_ADC0(void);
void start_ADC1(void);
void stop_ADC1(void);

void init_UART();

// sci
extern void    charput(uint8_t output_char);
extern uint8_t charget(void);
extern void    rprintf(char * fmt, ...);
extern int     getLine (char* str, unsigned int len);
extern int     putLine (char* str);

#endif