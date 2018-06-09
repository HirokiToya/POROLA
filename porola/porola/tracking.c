#include "motor.h"

ENCODER encoder1;
ENCODER encoder2;

static int loop_count = 0;
int max_loop_count_1 = 1003; 
int max_loop_count_2 = 1003;
long int traj1[1001], traj2[1001];

int get_loop_count() { return loop_count; }

void traj_tracking(float distance, float rotation, float time){ //m, degree,  sec
  rprintf("traj_tracking fun is called\r\n");
  float conv_distance = distance;
  float conv_rotation = deg2rad(rotation);

	float w=BODY_WIDTH;
	float r=WHEEL_RADIUS;
	
	float	thetaR = (conv_distance+(w/2)*conv_rotation)/r;
	float	thetaL = (conv_distance-(w/2)*conv_rotation)/r;

	make_traj(W1, thetaL, time);
	make_traj(W2, thetaR, time);

  start_tracking(NULL);
}

void make_traj_with_distance_degrees(float distance, float rotation, float time){
  rprintf("make_traj_with_distance_degrees fun is called\r\n");
  float conv_distance = distance;
  float conv_rotation = deg2rad(rotation);

	float w=BODY_WIDTH;
	float r=WHEEL_RADIUS;
	
	float	thetaR = (conv_distance+(w/2)*conv_rotation)/r;
	float	thetaL = (conv_distance-(w/2)*conv_rotation)/r;

	make_traj(W1, thetaL, time);
	make_traj(W2, thetaR, time);
}

void make_traj(int no, float rad, float time )
{
  float time_start = (float) (rx_time_milli_sec) / 1000.0 ; //[s]
  float time_end   = (float) (rx_time_milli_sec) / 1000.0 + time; //[s]
  float enc_start, enc_end;

  switch( no ){

  case W1: // =1

    max_loop_count_1 = (int) (time / RsampTime) +1; 
    rx_state = STOP_;
    enc_start = encoder1.cnt;
    enc_end   = encoder1.cnt + rad2enc( rad );

    //rprintf(" \r\n W1startCount: %lf  W1endCount: %lf \r\n", enc_start, enc_end);

    {
        float x_enc   = enc_end - enc_start; //xf-xi
        float tg        = time_end - time_start; //tf-ti
        float a2, a3 ;
        int   count;
        a2 =  3 * x_enc / (tg * tg );
        a3 = -2 * x_enc / (tg * tg * tg);
        //rprintf(" \r\n a2: %lf   a3: %lf \r\n", a2, a3);
    
        for(count =0; count < max_loop_count_1; count++){
          float current_time = count * RsampTime;
          traj1[count] =  a3 * current_time * current_time * current_time + a2 * current_time * current_time ;
          traj1[count] += enc_start;

          //rprintf ("time:[%lf]\t W1counts = %d\r\n", current_time, traj1[count]);
        }
    }

    // set counter.
    loop_count = 0;
    break;

  case W2:

    max_loop_count_2 = (int) (time / RsampTime) +1; // itime 
    rx_state = STOP_;
    enc_start = encoder2.cnt;
    enc_end   = encoder2.cnt + rad2enc( rad );
    //rprintf(" \r\n W2startCount: %lf  W2endCount: %lf \r\n", enc_start, enc_end);

    {
        float x_enc   = enc_end - enc_start;
        float tg        = time_end - time_start;
        float a2, a3;
        int   count;
        a2 =  3 * x_enc / (tg * tg );
        a3 = -2 * x_enc / (tg * tg * tg);
        //rprintf(" \r\n a2: %lf   a3: %lf \r\n", a2, a3);
 
        for(count =0; count<max_loop_count_2; count++){
          float current_time = count * RsampTime;
          traj2[count] =  a3 * current_time * current_time * current_time + a2 * current_time * current_time ;
          traj2[count] += enc_start;
          //rprintf ("time:[%lf]\t W2counts = %d\r\n", current_time, traj2[count]);
        }
    }

    // set counter.
    loop_count = 0;
    break;

  default:
    break;
  }
}

void start_tracking(void (*delegate)(void))
{
  //rprintf("start_tracking()\r\n");

  // clear present value.
  encoder1.traj_total_diff   = 0;
  encoder1.traj_last_diff    = 0;
  encoder1.traj_current_diff = 0;

  encoder2.traj_total_diff   = 0;
  encoder2.traj_last_diff    = 0;
  encoder2.traj_current_diff = 0;

  // to tracking mode
  rx_state =TRAJ_;

  while (rx_state == TRAJ_){
    if(delegate){
      delegate();
    }
	}
}


void stop_tracking()
{
	rx_state = STOP_REQ_;
	while(rx_state != STOP_);
}

void update_enc_count(void)
{
  //memory of last value
  encoder1.raw_last_cnt = encoder1.raw_current_cnt;
  encoder2.raw_last_cnt = encoder2.raw_current_cnt;

  //read count value
  encoder1.raw_current_cnt = (float)MTU1.TCNT;
  encoder2.raw_current_cnt = (float)MTU2.TCNT;

  //increment of pulse count number
  encoder1.raw_update_cnt = 0;
  encoder1.raw_update_cnt = -(encoder1.raw_current_cnt - encoder1.raw_last_cnt);
  encoder2.raw_update_cnt = 0;
  encoder2.raw_update_cnt = -(encoder2.raw_current_cnt - encoder2.raw_last_cnt);

  //add increment of count number
  encoder1.cnt -= encoder1.raw_update_cnt;
  encoder2.cnt += encoder2.raw_update_cnt;
}

/*----Interrupt processing-----*/
void pd_control(void)
{
  float fx1, fx2;

  if ( (1002 < max_loop_count_1) && (1002 < max_loop_count_2) ) {
    rx_state = STOP_REQ_;
    //rprintf ("END");
    return;
  }

  if ( loop_count >= max_loop_count_1 ) max_loop_count_1 = 1003;
  if ( loop_count >= max_loop_count_2 ) max_loop_count_2 = 1003;

  if ( (loop_count <= max_loop_count_1 ) && (max_loop_count_1 < 1002 )) {

    encoder1.goal_cnt = traj1[loop_count];
    encoder1.traj_current_diff = traj1[loop_count] - encoder1.cnt;
    encoder1.traj_total_diff += encoder1.traj_current_diff ;

    fx1 = PROPORTIAL_GAIN   * (float)encoder1.traj_current_diff +
          DIFFERENTIAL_GAIN * (encoder1.traj_current_diff - encoder1.traj_last_diff ) * RsampTime;

    //rprintf("cnt1:%d,traj1:%d,diff:%d \r\n",(int)encoder1.cnt, (int)traj1[loop_count], (int)encoder1.traj_current_diff);
    motor(W1, (int)fx1);
    encoder1.traj_last_diff = encoder1.traj_current_diff;
  }

  if ( (loop_count <= max_loop_count_2) && (max_loop_count_2 < 1002 )) {

    encoder2.goal_cnt = traj2[loop_count];
    encoder2.traj_current_diff = traj2[loop_count] - encoder2.cnt;
    encoder2.traj_total_diff += encoder2.traj_current_diff;

    fx2 = PROPORTIAL_GAIN   * (float)encoder2.traj_current_diff +
         DIFFERENTIAL_GAIN * (encoder2.traj_current_diff - encoder2.traj_last_diff ) * RsampTime;

    //rprintf("cnt2:%d,traj2:%d,diff:%d \r\n",(int)encoder2.cnt, (int)traj2[loop_count], (int)encoder2.traj_current_diff);
    motor(W2, (int)fx2);
    encoder2.traj_last_diff = encoder2.traj_current_diff;
  }

  ++ loop_count;
}