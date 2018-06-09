#include "iodefine.h"
#include "vect.h"
#include "motor.h"
#include "servo.h"
#include "rxpi.h"
#include "distance_measure.h"
#include "run_mode.h"

#ifdef DEBUG_TRAJ_MODE
static void print_trajectory_header();
static void print_trajectory(void);

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
	start_CMT0();
	//rx_state = TRAJ_;
	// start_ADC0(); //for linetrace
	// start_ADC1(); //for distance sencer

    // make_traj_with_distance_degrees(0.50, 0.0, 3.0);
	// print_trajectory_header();
    // start_tracking(print_trajectory);
	
	make_traj_with_distance_degrees(0.0, 60.0, 3.0);
	print_trajectory_header();
    start_tracking(print_trajectory);

	make_traj_with_distance_degrees(0.0, -60.0, 3.0);
	print_trajectory_header();
    start_tracking(print_trajectory);
	
	while(1)
	{
		// rprintf("enc1:%d, enc2:%d \r\n",
        //      (int)encoder1.cnt, (int)encoder2.cnt);
	}

}

static void print_trajectory_header() {
    rprintf("time, cnt1, traj1, cnt2, traj2");
}
static void print_trajectory()
{
    static int loop = -1;
    int cloop = get_loop_count();
    if(loop == cloop)
        return;
    loop = cloop;

    rprintf("%d, %d, %d, %d, %d \r\n",
             (int)loop, (int)encoder1.cnt, (int)encoder1.goal_cnt, (int)encoder2.cnt, (int)encoder2.goal_cnt);
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
#endif
