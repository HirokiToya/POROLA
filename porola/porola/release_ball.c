#include "release_ball.h"

void blue_act()
{
	traj_tracking(0.30, 0.0, 3.0);
	traj_tracking(0.0, -185.0, 5.0);
	traj_tracking(-0.30, 0.0, 3.0);
	for(int i=0; i<550; i++){
		blue_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
	}
	reset_port_for_Arduino();
	traj_tracking(0.17, 0.0, 2.0);
	traj_tracking(0.0, 90.0, 3.0);
	pattern = return_tracing;
}

void yellow_act()
{
	traj_tracking(0.15, 0.0, 2.0);
	traj_tracking(0.0, -90.0, 3.0);
	traj_tracking(-0.20, 0.0, 2.0);
	for(int i=0; i<550; i++){
		yellow_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
	}
	reset_port_for_Arduino();
	traj_tracking(0.20, 0.0, 2.0);
	traj_tracking(0.0, 90.0, 3.0);
	pattern = return_tracing;
}

void red_act()
{
	traj_tracking(0.10, 0.0, 2.0);
	traj_tracking(0.0, -110.0, 3.0);
	traj_tracking(-0.20, 0.0, 2.0);
	for(int i=0; i<550; i++){
		red_for_Arduino();
		rprintf("com:%d %d %d\r\n",PD1, PD2, PD3);
  }
	reset_port_for_Arduino();
	traj_tracking(0.20, 0.0, 2.0);
	traj_tracking(0.0, -80.0, 3.0);
	init_PORT_for_Arduino();
}

void init_PORT_for_Arduino()
{
  PORTD.DDR.BYTE = 0xff;
  PORTD.DR.BYTE  = 0x0;
}

void reset_port_for_Arduino()
{
	PORTD.DR.BIT.B1 = 0;
  PORTD.DR.BIT.B2 = 0;
  PORTD.DR.BIT.B3 = 0;
}

// void color_for_Arduino()
// {
// 	PORTD.DR.BIT.B1 = 0;
//   PORTD.DR.BIT.B2 = 1;
//   PORTD.DR.BIT.B3 = 0;	
// }

void blue_for_Arduino()
{
  PORTD.DR.BIT.B1 = 1;
  PORTD.DR.BIT.B2 = 0;
  PORTD.DR.BIT.B3 = 0;
}

void yellow_for_Arduino()
{
  PORTD.DR.BIT.B1 = 1;
  PORTD.DR.BIT.B2 = 1;
  PORTD.DR.BIT.B3 = 0;
}

void red_for_Arduino()
{
  PORTD.DR.BIT.B1 = 1;
  PORTD.DR.BIT.B2 = 1;
  PORTD.DR.BIT.B3 = 1;
}
