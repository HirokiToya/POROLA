#include "servo.h"
#include "rxpi.h"
#include "iodefine.h"

void init_servo()
{
//Servo1 CN1-27
  PORT3.DR.BIT.B2  = 0;
  PORT3.DDR.BIT.B2 = 1;
//Servo2
  PORT3.DR.BIT.B4  = 0;
  PORT3.DDR.BIT.B4 = 1;
//Servo3 CN2-13
  PORTB.DR.BIT.B4  = 0;
  PORTB.DDR.BIT.B4 = 1;
//Servo4
  PORTB.DR.BIT.B5  = 0;
  PORTB.DDR.BIT.B5 = 1;

  MSTP(MTU0) = 0;
  MSTP(MTU10) = 0;

  MTU0.TCR.BIT.TPSC = 3; 
  MTU10.TCR.BIT.TPSC = 3; 

  MTU0.TCR.BIT.CCLR = 1;
  MTU10.TCR.BIT.CCLR = 1;

  MTU0.TMDR.BIT.MD = 2;
  MTU10.TMDR.BIT.MD = 2;

  MTU0.TIORH.BIT.IOA = 2;
  MTU0.TIORL.BIT.IOC = 2;
  MTU10.TIORH.BIT.IOA =2;
  MTU10.TIORL.BIT.IOC = 2;

  MTU0.TIORH.BIT.IOB = 1;
  MTU0.TIORL.BIT.IOD = 1;
  MTU10.TIORH.BIT.IOB = 1;
  MTU10.TIORL.BIT.IOD = 1;

  MTUB.TOER.BIT.OE4A = 1;
  MTUB.TOER.BIT.OE4C = 1;
  MTU10.TMDR.BIT.BFA = 0;
  MTU10.TMDR.BIT.BFB = 0;

  MTU0.TGRA = 5000;
  MTU0.TGRB = 0;
  MTU0.TGRC = 5000;
  MTU0.TGRD = 0;

  MTU10.TGRA = 5000;
  MTU10.TGRB = 0;
  MTU10.TGRC = 5000;
  MTU10.TGRD = 0;

  MTUA.TSTR.BIT.CST0 = 1;
  MTUB.TSTR.BIT.CST4 = 1;
}

void MTU0_cnt_start(){
  MTUA.TSTR.BIT.CST0 = 1;
}

void MTU0_cnt_stop(){
  MTUA.TSTR.BIT.CST0 = 0;
}

void MTU10_cnt_start(){
  MTUB.TSTR.BIT.CST4 = 1;
}

void MTU10_cnt_stop(){
  MTUB.TSTR.BIT.CST4 = 0;
}

void servo1_open(){
  MTU0.TGRB = 750;
}

void servo1_close(){
  MTU0.TGRB = 410;
}

void horn_open(){
  MTU0.TGRD = 180;
}

void horn_close(){
  MTU0.TGRD = 340;
}

void arm_up(){
  MTU10.TGRB = 760;
}

void arm_down(){
  MTU10.TGRB = 380;
}

void servo4_open(){
  MTU10.TGRD = 500;
}

void servo4_close(){
  MTU10.TGRD = 500;
}

void init_horn(){
  arm_up();
  horn_open();
}

void get_ball()
{
  arm_down();
  for(int i=0; i<500; i++){
    rprintf("=========\r\n");
  }
  horn_close();
  for(int i=0; i<500; i++){
    rprintf("=========\r\n");
  }
  arm_up();
  for(int i=0; i<500; i++){
    rprintf("=========\r\n");
  }
  horn_open();
  for(int i=0; i<500; i++){
    rprintf("=========\r\n");
  }

}
  