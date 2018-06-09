#ifndef SERVO_H
#define SERVO_H

void init_servo();
void init_horn();
void MTU0_cnt_start();
void MTU0_cnt_stop();
void MTU10_cnt_start();
void MTU10_cnt_stop();

void servo1_open();
void servo1_close();
void horn_open();
void horn_close();
void arm_up();
void arm_down();
void servo4_open();
void servo4_close();
void get_ball();

#endif