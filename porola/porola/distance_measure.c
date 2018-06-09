#include "distance_measure.h"

void set_start_pos(){
  traj_tracking(0.0, 25.0, 2.0);
  traj_tracking(0.90, 0.0, 4.0);
  traj_tracking(0.0, 105.0, 4.0);
  traj_tracking(-0.10, 0.0, 2.0);
  pattern = searching;
}

void start_search()
{
  search_count++;

  if(get_count == MaxBallCount){
    get_count = 0;
    search_count = 0;
    //robot turn to go back
    traj_tracking(0.0, -180.0, 5.0);
    pattern = return_tracing;
  }else{
    pattern = none;
    search_flag = 1;
    rx_state = TRAJ_;
    while(rx_state == TRAJ_);
    search();
  }
}

void search()
{
  rprintf("search()\r\n");
  traj_tracking(0.0, 60.0, 3.0);
  traj_tracking(0.0, -60.0, 3.0);
  traj_tracking(0.0, -60.0, 3.0);
  traj_tracking(0.0, 60.0, 3.0);
  set_recursion();
  pattern = searching; 
}


int get_distance(){
  int ad;
  float vol;
  float dist;
  ad = AD1.ADDRC;
  vol = 3.3 * ad / 1024.0;
  dist = -8.479 * vol * vol * vol + 46.880 * vol * vol - 90.995 * vol + 80.600;
  dist = (int)(dist + 0.5); //rounding off
  rprintf("dist:%.1lf\r\n", dist);
  return dist;
}


void stop_turning(){
  rprintf("stop_turning()\r\n");
  int last_dist = get_distance();
  int current_dist = get_distance();
  int dist = (last_dist+current_dist) / 2;
  if( dist < 25 ){
    int d_check = last_dist - current_dist;
    if(d_check < 5){
      rprintf("get_ball()\r\n");
      stop_CMT0();
      get_ball();
      start_CMT1();
    }
  }
}

void set_recursion(void)
{
  rprintf("recursion()\r\n");

  while(1){
    if(Ph0=White && Ph1==White && Ph2==White && Ph3==White)
    {
      motor(W1,-40);
      motor(W2,-40);
    }else{
      break;
    }
  }
  start_recursion();
}

void start_recursion(void)
{
  rprintf("start_recursion()\r\n");
  interrupt_count = 0;
  pattern = none;
	rx_state = RECURSION_;
	while(rx_state == RECURSION_);
}
