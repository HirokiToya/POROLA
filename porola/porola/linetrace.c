
#include "motor.h"

void initilize_linetrace()
{
  //linetraceLED
  // PORTD.DDR.BIT.B0 = 1;
  // PORTD.DDR.BIT.B1 = 1;
  // PORTD.DDR.BIT.B2 = 1;
  // PORTD.DDR.BIT.B3 = 1;

  //photo rifrector port
  PORT4.DDR.BIT.B0 = 0; 
  PORT4.DDR.BIT.B1 = 0; 
  PORT4.DDR.BIT.B2 = 0; 
  PORT4.DDR.BIT.B3 = 0;
}

void start_linetrace(void)
{
	rprintf("StartLinetrace\r\n");
  rprintf("line_flag:%d\r\n",line_flag);
	rprintf("line_num:%d\r\n",line_num);
  reset_port_for_Arduino();
  rap_flag++;
  line_num = 0;
  pattern = none;
	rx_state = LINE_;
	while(rx_state == LINE_);
}

void start_return_linetrace()
{
  reset_port_for_Arduino();
  pattern = none;
	rx_state = RETURN_LINETRACE_;
	while(rx_state == RETURN_LINETRACE_);
}

void linetrace(void)
{
  //BBBB
  if(Ph0==Black && Ph1==Black && Ph2==Black && Ph3==Black)
    {
      motor(W1,50);
      motor(W2,50);
      if(line_flag == 0){
        increse_line_count();
				rprintf("line_num:%d\r\n",line_num);
      }
	  }
  //WBBW
  else if(Ph0==White && Ph1==Black && Ph2==Black && Ph3==White)
    {
      motor(W1,50);
      motor(W2,50);
      line_flag = 0;
      rprintf("WBBW\r\n");
	  }
	//BWWW
  else if(Ph0==Black && Ph1==White && Ph2==White && Ph3==White)
	  {
      motor(W1,50);
	    motor(W2,-30);
      line_flag = 0;
      rprintf("BWWW\r\n");
	  }
  //WWWB
  else if(Ph0==White && Ph1==White && Ph2==White && Ph3==Black)
    {
      motor(W1,-30);
      motor(W2,50);
      line_flag = 0;
      rprintf("WWWB\r\n");
	  }
  //BBWW
  else if(Ph0==Black && Ph1==Black && Ph2==White && Ph3==White)
    {
      motor(W1,50);
      motor(W2,10);
      line_flag = 0;
      rprintf("BBWW\r\n");
	  }
  //WWBB
  else if(Ph0==White && Ph1==White && Ph2==Black && Ph3==Black)
    {
      motor(W1,10);
      motor(W2,50);
      line_flag = 0;
      rprintf("WWBB\r\n");
	  }
  //WBWW
  else if(Ph0==White && Ph1==Black && Ph2==White && Ph3==White)
    {
      motor(W1,50);
	    motor(W2,20);
      line_flag = 0;
      rprintf("WBWW\r\n");
	  }
  //WWBW
  else if(Ph0==White && Ph1==White && Ph2==Black && Ph3==White)
    {
	    motor(W1,20);
	    motor(W2,50);
      line_flag = 0;
      rprintf("WWBW\r\n");
	  }
  else{
      line_flag = 0;
    }
}

void increse_line_count()
{
  if(line_state_scan())
  {
    line_flag = 1;
  }else{
    line_flag = 0;
  }
}

int line_state_scan()
{
  for(int i=0; i<30; i++);

  if(Ph0==Black && Ph1==Black && Ph2==Black && Ph3==Black)
  {
    line_num++;
    return 1;
  }
  return 0;
}

void set_recursion(void)
{
  rprintf("recursion()\r\n");

  while(1){
    if(Ph0=White && Ph1==White && Ph2==White && Ph3==White)
    {
      motor(W1,-35);
      motor(W2,-35);
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

void set_start_limited_line_trace()
{
  while(1){
    if(Ph0=White && Ph1==White && Ph2==White && Ph3==White)
    {
      motor(W1,-35);
      motor(W2,-35);
    }else{
      break;
    }
  }
  start_limited_line_trace();
}

void start_limited_line_trace()
{
  rprintf("start_limited_line_trace()\r\n");
  interrupt_count = 0;
  pattern = none;
	rx_state = LIMITED_LINETRACE_;
	while(rx_state == LIMITED_LINETRACE_);
}


