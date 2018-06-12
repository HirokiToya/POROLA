#include "communicate_arduino.h"


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

void search_mode_for_Arduino()
{
  PORTD.DR.BIT.B1 = 1;
  PORTD.DR.BIT.B2 = 0;
  PORTD.DR.BIT.B3 = 0;
}

void blue_for_Arduino()
{
  PORTD.DR.BIT.B1 = 0;
  PORTD.DR.BIT.B2 = 1;
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
  PORTD.DR.BIT.B1 = 0;
  PORTD.DR.BIT.B2 = 0;
  PORTD.DR.BIT.B3 = 1;
}