#include "release_ball.h"

void blue_act()
{
	traj_tracking(0.30, 0.0, 2.0);
	traj_tracking(0.0, -185.0, 4.0);
	traj_tracking(-0.35, 0.0, 2.0);
	for(int i=0; i<500; i++){
		blue_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
	}
	reset_port_for_Arduino();
	traj_tracking(0.22, 0.0, 2.0);
	traj_tracking(0.0, 90.0, 2.0);
	pattern = return_tracing;
}

void yellow_act()
{
	traj_tracking(0.15, 0.0, 1.0);
	traj_tracking(0.0, -90.0, 2.0);
	traj_tracking(-0.25, 0.0, 2.0);
	for(int i=0; i<500; i++){
		yellow_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
	}
	reset_port_for_Arduino();
	traj_tracking(0.25, 0.0, 2.0);
	traj_tracking(0.0, 90.0, 2.0);
	pattern = return_tracing;
}

void red_act()
{
	traj_tracking(0.10, 0.0, 1.0);
	traj_tracking(0.0, -110.0, 3.0);
	traj_tracking(-0.20, 0.0, 2.0);
	for(int i=0; i<500; i++){
		red_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
  }
	reset_port_for_Arduino();
	traj_tracking(0.20, 0.0, 2.0);
	traj_tracking(0.0, -80.0, 3.0);
}

