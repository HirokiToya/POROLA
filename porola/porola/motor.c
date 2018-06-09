#include "motor.h"

static void init_pwm();
static void init_port_motor();
static void init_enc();

void motor( int no, int duty )
{
	if(duty > 255)  duty = 255;
	if(duty < -255) duty = -255;
	
	switch( no ){
		case W1:
		if(duty > 0){
			MTU6.TGRB = 255-duty;
			MOTOR_1_CW;
		
		}else if(duty < 0){
			MTU6.TGRB = 255+duty;
			MOTOR_1_CCW;
	
		}else{
			MTU6.TGRB = 0;
			MOTOR_1_BREAK;
		}
	   
		case W2:
		if(duty > 0){
			MTU9.TGRB = duty;
			MOTOR_2_CCW;
		
		}else if(duty < 0){
			MTU9.TGRB = -duty;
			MOTOR_2_CW;
	
		}else{
		  MTU9.TGRB = 0;
			MOTOR_2_BREAK;
		}
	}
}

void init_motor() {
	init_pwm();
	init_port_motor();
	init_enc();
}

static
void init_pwm(){
/*-----set motor PWM-----*/

  MSTP(MTU6)=0;
  MSTP(MTU9)=0;

  //count clock phi64
  MTU6.TCR.BIT.TPSC = 3;
  MTU9.TCR.BIT.TPSC = 3;

  //counter clear (use TGRC(A))
  MTU6.TCR.BIT.CCLR =1;
  MTU9.TCR.BIT.CCLR =1;

  //PWM mode 1
  MTU6.TMDR.BIT.MD =3; //PWM mode 2
  MTU9.TMDR.BIT.MD =2; //PWM mode 1

  //TGRC(A)..Low to Hight
  MTU6.TIORH.BIT.IOA =2;
  MTU9.TIORH.BIT.IOA =2;

  //TGRD(B)..Low to Low
  MTU9.TIORH.BIT.IOB = 1;

  MTU6.TIORH.BIT.IOB =2;//TGRB
  MTU6.TIORL.BIT.IOC =2;//TGRC
  MTU6.TIORL.BIT.IOD =2;//TGRD

  //set count value
  MTU9.TGRA = 255;
  MTU9.TGRB = 0;
  MTU6.TGRA = 255;
  MTU6.TGRB = 0;
  MTU6.TGRC = 0;
  MTU6.TGRD = 0;

  //count start
  MTUB.TSTR.BIT.CST0 = 1;//6 
  MTUB.TSTR.BIT.CST3 = 1;//9

  //motor direction port
  PORT5.DDR.BIT.B0=1;
  PORT5.DDR.BIT.B1=1;
  PORT5.DDR.BIT.B5=1;
  PORT5.DDR.BIT.B4=1;// you can't use P53
}

static
void init_port_motor() {
  //set motor port
  PORT5.DDR.BIT.B0=1;
  PORT5.DDR.BIT.B1=1;
  PORT5.DDR.BIT.B5=1;
  PORT5.DDR.BIT.B4=1;

  //set enc port
  PORT2.DDR.BIT.B2=0;//P22 input
  PORT2.DDR.BIT.B3=0;//P23 input
  PORT2.DDR.BIT.B4=0;//P24 input
  PORT2.DDR.BIT.B5=0;//P25 input

  PORTC.DDR.BIT.B0=0;
  PORTC.DDR.BIT.B1=0;
  PORTC.DDR.BIT.B2=0;
  PORTC.DDR.BIT.B3=0;

  //linetraceLED
  PORTD.DDR.BIT.B0 = 1;
  PORTD.DDR.BIT.B1 = 1;
  PORTD.DDR.BIT.B2 = 1;
  PORTD.DDR.BIT.B3 = 1;

  //photo rifrector port
  PORT4.DDR.BIT.B0 = 0; 
  PORT4.DDR.BIT.B1 = 0; 
  PORT4.DDR.BIT.B2 = 0; 
  PORT4.DDR.BIT.B3 = 0; 

  //set input buffer control register
  PORT2.ICR.BIT.B0=1;
  PORT2.ICR.BIT.B1=1;
  PORT2.ICR.BIT.B2=1;
  PORT2.ICR.BIT.B3=1;
  PORT2.ICR.BIT.B4=1;
  PORT2.ICR.BIT.B5=1;

  PORTC.ICR.BIT.B0=1;
  PORTC.ICR.BIT.B1=1;
  PORTC.ICR.BIT.B2=1;
  PORTC.ICR.BIT.B3=1;

  PORT1.DDR.BIT.B3=1;// motor2 pwm
}

static
void init_enc(){
  //MTU1
  //MTCLKA-A P24 CN2 29
  //MTCLKB-A P25 CN2 30
  //MTU2
  //MTCLKC-A P22 CN2 27
  //MTCLKD-A P23 CN2 28
  //MTU7
  //MTCLKG-A PC0 CN2 17
  //MTCLKH-A PC1 CN2 18
  //MTU8
  //MTCLKE-A PC2 CN2 19
  //MTCLKF-A PC3 CN2 20

  //IOPORT.PFDMTU.BIT.TCLKS = 1; //MTCLKx-B

  //use A
  MSTP(MTUA)=0;
  MSTP(MTUB)=0;
  MSTP(MTU1)=0;
  MSTP(MTU2)=0;
  MSTP(MTU7)=0;
  MSTP(MTU8)=0;

  MTUA.TSTR.BIT.CST1 = 0;
  MTUA.TSTR.BIT.CST2 = 0;
  MTUB.TSTR.BIT.CST1 = 0;
  MTUB.TSTR.BIT.CST2 = 0;

  // count = 0 
  MTU1.TCNT =0;
  MTU2.TCNT =0;
  MTU7.TCNT =0;
  MTU8.TCNT =0;

  // use TCLKx_A
  IOPORT.PFCMTU.BIT.TCLKS=0;
  IOPORT.PFDMTU.BIT.TCLKS=0;

  // phase count mode1
  MTU1.TMDR.BIT.MD=4;
  MTU2.TMDR.BIT.MD=4;
  MTU7.TMDR.BIT.MD=4;
  MTU8.TMDR.BIT.MD=4;

  MTUA.TSTR.BIT.CST1=1;
  MTUA.TSTR.BIT.CST2=1;
  MTUB.TSTR.BIT.CST1=1;
  MTUB.TSTR.BIT.CST2=1;
}
