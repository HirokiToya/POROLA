#include "distance_measure.h"

void set_start_position()
{
  switch(rap_flag){
    case 1:
        traj_tracking(0.0, 13.0, 1.0);
        traj_tracking(0.88, 0.0, 4.0);
        traj_tracking(0.0, 96.0, 3.0);
        traj_tracking(-0.10, 0.0, 2.0);
        pattern = searching;
    break;

    case 2:
        traj_tracking(0.0, 13.0, 1.0);
        traj_tracking(0.88, 0.0, 4.0);
        traj_tracking(0.0, 96.0, 3.0);
        traj_tracking(0.20, 0.0, 3.0);
        pattern = set_second_pos;
    break;
  }

}

void set_second_position()
{
  set_start_limited_line_trace();
}

void start_search()
{
  search_mode_for_Arduino();
  search_count++;
  if(search_count > 7 && return_flag == 1 ){
    search_count = 0;
    search_mode_flag = 0;
    return_flag = 0;
    //robot turn to go back
    traj_tracking(0.20, 0.0, 3.0);
    traj_tracking(0.0, -188.0, 5.0);
    set_recursion();
    line_num = 0;
    pattern = return_tracing;
  }else{
    search_mode_flag = 0;
    pattern = none;
    rx_state = TRAJ_;
    while(rx_state == TRAJ_);
    search();
  }
}

void start_second_lap_search()
{
  search_mode_for_Arduino();
  search_count++;
  if(search_count > 4 ){ // 7
    search_count = 0;
    search_mode_flag = 0;
    return_flag = 0;
    //robot turn to go back
    traj_tracking(0.0, -188.0, 5.0);
    set_recursion();
    line_num = 0;
    pattern = return_tracing;
  }else{
    search_mode_flag = 0;
    pattern = none;
    rx_state = TRAJ_;
    while(rx_state == TRAJ_);
    search();
  }
}

void search()
{
  rprintf("search()\r\n");

  search_mode_flag = 0;
  escape_loop_get_ball = 0;
  traj_tracking(0.0, 50.0, 3.0);

  search_mode_flag = 1;
  escape_loop_get_ball = 0;
  traj_tracking(0.0, -50.0, 3.0);

  escape_loop_get_ball = 0;
  traj_tracking(0.0, -50.0, 3.0);

  search_mode_flag = 0;
  escape_loop_get_ball = 0;
  traj_tracking(0.0, 50.0, 3.0);
  
  if(search_count < 2)
  {
    traj_tracking(0.10, 0.0, 2.0);
  }else{
    set_recursion();
  }

  switch(rap_flag){
    case 1:
      pattern = searching;
    break;

    case 2:
      pattern = second_lap_searching;
    break;
  }

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
  if( dist < 23 ){
    int d_check = last_dist - current_dist;
    if(d_check < 5){
      motor(W1,1);
      motor(W2,1);
      rprintf("get_ball()\r\n");
      if(escape_loop_get_ball < 3)
      {
        get_ball();
        escape_loop_get_ball++;
      } 
    }
  }
}