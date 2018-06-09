#include "rxpi.h"

int rx_state = STOP_;
int rx_time_milli_sec = 0;
robotState	pattern = waiting;
int line_num = 0;  // for count black line number 
int line_flag = 0; // for control linetrace
int forth_line_flag = 0; // for conditional branch of 4th black line
int interrupt_count = 0;
int search_flag = 0; // for serching act
int get_count = 0;
int search_count = 0;


/*----- init CMT timer -----*/
void init_CMT(void)
{
  MSTP(CMT0)=0;
  MSTP(CMT1)=0;
  MSTP(CMT2)=0;
  MSTP(CMT3) = 0;
  CMT0.CMCR.BIT.CKS = 11;
  CMT1.CMCR.BIT.CKS = 11;
  CMT2.CMCR.BIT.CKS = 11;
  CMT3.CMCR.BIT.CKS = 11;
  CMT0.CMCOR = 976;  //0.02[s]
  CMT1.CMCOR = 976;
  CMT2.CMCOR = 976;
  CMT3.CMCOR = 976;
  CMT0.CMCR.BIT.CMIE = 1;
  CMT1.CMCR.BIT.CMIE = 1;
  CMT2.CMCR.BIT.CMIE = 1;
  CMT3.CMCR.BIT.CMIE = 1;
  IR(CMT0,CMI0)  = 0;
  IR(CMT1,CMI1)  = 0;
  IR(CMT2,CMI2)  = 0;
  IR(CMT3,CMI3)  = 0;
  IEN(CMT0,CMI0) = 1;
  IEN(CMT1,CMI1) = 1;
  IEN(CMT2,CMI2) = 1;
  IEN(CMT3,CMI3) = 1;
  IPR(CMT0,CMI0) = 1;
  IPR(CMT1,CMI1) = 1;
  IPR(CMT2,CMI2) = 1;
  IPR(CMT3,CMI3) = 1;
	CMT.CMSTR0.BIT.STR0 = 0;
	CMT.CMSTR0.BIT.STR1 = 0;
	CMT.CMSTR1.BIT.STR2 = 0;
	CMT.CMSTR1.BIT.STR3 = 0;
}

void start_CMT0(void)
{
  CMT.CMSTR0.BIT.STR0 = 1;
}

void stop_CMT0(void)
{
  CMT.CMSTR0.BIT.STR0 = 0;
}

void start_CMT1(void)
{
  CMT.CMSTR0.BIT.STR1 = 1;
}

void stop_CMT1(void)
{
  CMT.CMSTR0.BIT.STR1 = 0;
}

void start_CMT2(void)
{
  CMT.CMSTR1.BIT.STR2 = 1;
}

void stop_CMT2(void)
{
  CMT.CMSTR1.BIT.STR2 = 0;
}

void start_CMT3(void)
{
  CMT.CMSTR1.BIT.STR3 = 1;
}

void stop_CMT3(void)
{
  CMT.CMSTR1.BIT.STR3 = 0;
}

/*----- init ADC -----*/
void init_ADC(void){
	//set port
  PORT4.DDR.BIT.B0 = 0;
	PORT4.ICR.BIT.B0 = 1;
	PORT4.DDR.BIT.B1 = 0;
	PORT4.ICR.BIT.B1 = 1;
	PORT4.DDR.BIT.B2 = 0;
	PORT4.ICR.BIT.B2 = 1;
	PORT4.DDR.BIT.B3 = 0;
	PORT4.ICR.BIT.B3 = 1;
	PORT4.DDR.BIT.B4 = 0;
	PORT4.ICR.BIT.B4 = 1;
	PORT4.DDR.BIT.B5 = 0;
	PORT4.ICR.BIT.B5 = 1;
	PORT4.DDR.BIT.B6 = 0;
	PORT4.ICR.BIT.B6 = 1;
	PORT4.DDR.BIT.B7 = 0;
	PORT4.ICR.BIT.B7 = 1;
	
	//initialize
  MSTP(AD0) = 0;
	MSTP(AD1) = 0;
	
	//stop ADC
  AD0.ADCSR.BIT.ADST = 0;
	AD1.ADCSR.BIT.ADST = 0;
	
	//set scan mode
  AD0.ADCR.BIT.MODE = 2;
	AD1.ADCR.BIT.MODE = 2;
	
	//start triger
  AD0.ADCR.BIT.TRGS = 0;
	AD1.ADCR.BIT.TRGS = 0;

	//set scan
  AD0.ADCSR.BIT.CH = 0x3;
	AD1.ADCSR.BIT.CH = 0x3;
	
	//data is LSB stuffed
  AD0.ADDPR.BIT.DPSEL = 0;
	AD1.ADDPR.BIT.DPSEL = 0;
	
	//set intrrupt 
  IEN(AD0,ADI0) = 1;
	IEN(AD1,ADI1) = 1;
  IPR(AD0,ADI0) = 1;
	IPR(AD1,ADI1) = 1;
  AD0.ADCSR.BIT.ADIE = 1;
	AD1.ADCSR.BIT.ADIE = 1;
 }

void start_ADC0(void){
	AD0.ADCSR.BIT.ADST = 1;	
}

void stop_ADC0(void){
	AD0.ADCSR.BIT.ADST = 0;	
}

void start_ADC1(void){
	AD1.ADCSR.BIT.ADST = 1;	
}

void stop_ADC1(void){
	AD1.ADCSR.BIT.ADST = 0;	
}

void init_UART(){
  int mn;

  // Port
  // TxD2-A P13 CN2-40
  // RxD2-A P12 CN2-39

  //7
	//SCI6.SCR.BIT.TIE =1; //TXIx access permission
	//SCI6.SCR.BIT.RIE =1; //RXIx access permission
	//IR(SCI6, RXI6) =0;
	//IR(SCI6, TXI6) =0;
	//IEN(SCI6, RXI6) =0; //interrupt permission
	//IEN(SCI6, TXI6) =0;

	MSTP(SCI2) = 0;

	PORT1.DDR.BIT.B2 = 0;
	PORT1.ICR.BIT.B2 = 1;
	PORT1.DDR.BIT.B3 = 1;
	
	SCI2.SCR.BYTE = 0x00 ; 

	SCI2.SMR.BYTE = 0x00;
	
	//5 bps
	// SCI2.BRR = 12;  SCI2.SEMR.BIT.ABCS = 1; // ->115200
	// SCI2.BRR = 12; SCI2.SEMR.BIT.ABCS = 0; //->57600
	SCI2.BRR = 40; SCI2.SEMR.BIT.ABCS = 0; //->19200
	// SCI2.BRR = 76; SCI2.SEMR.BIT.ABCS = 0;// -> 9600

	//6 1bit wait
	for(mn=0;mn<1736;mn++);

	//7
	SCI2.SCR.BIT.RIE = 1;
	SCI2.SCR.BIT.TIE = 1;

	IEN(SCI2, RXI2) = 0x01;
	IEN(SCI2, TXI2) = 0x01;

	IR(SCI2, RXI2) = 0;
	IR(SCI2, TXI2) = 0;

	//8
	SCI2.SCR.BYTE |= 0x30;

}

//from RX_Set_up.h

/******************************************************************************/
/* Function Name: charput
/* Description  : Outputs a character on a serial port
/* Arguments    : character to output
/* Return Value : none
/******************************************************************************/
void charput(uint8_t output_char)
{
	#if uartNum == 6
		/* Wait for transmit buffer to be empty */
		while(IR(SCI6, TXI6) == 0);

		/* Clear TXI IR bit */
		IR(SCI6, TXI6) = 0;

		/* Write the character out */
		SCI6.TDR = output_char;
	#elif uartNum == 2
		while(IR(SCI2, TXI2) == 0);

		/* Clear TXI IR bit */
		IR(SCI2, TXI2) = 0;

		/* Write the character out */
		SCI2.TDR = output_char;

	#endif
}

/******************************************************************************/
/*End of function  charput
/******************************************************************************/

/******************************************************************************/
/* Function Name: charget
/* Description  : Gets a character on a serial port
/* Arguments    : character to output
/* Return Value : none
/******************************************************************************/

uint8_t charget(void)
{
		uint8_t temp;
	#if uartNum == 6
		/* Read any 'junk' out of receive buffer */
		temp = SCI6.RDR;

		/* Clear flag to receive next byte */
		IR(SCI6, RXI6) = 0;

		/* Wait for next receive data */
		while(IR(SCI6, RXI6) == 0);

		/* Read data */
		temp = SCI6.RDR;

	#elif uartNum == 2

		/* Read any 'junk' out of receive buffer */
		temp = SCI2.RDR;

		/* Clear flag to receive next byte */
		IR(SCI2, RXI2) = 0;

		/* Wait for next receive data */
		while(IR(SCI2, RXI2) == 0);

		/* Read data */
		temp = SCI2.RDR;
		
	#endif
  
  /* Echo data back out */
  if(temp == 0x0A || temp == 0x0D)
  {
    /* Enter was pressed, output newline */
    charput('\r');
    charput('\n');
  }
  else
  {
    /* Echo back character */
    charput(temp);
  }

  /* Receive data acquired, send back up */
  return temp;
  
}
/******************************************************************************/
/*End of function  charget
/******************************************************************************/

void rprintf(char * fmt, ...) {
  char **arg = (char **) &fmt;
  char c;
  char ci;
  char data[30];
  arg++;

  while((c = *fmt++) != 0) {
  	if(c != '%')
      charput(c);
    else {
      char *p;
      c = *fmt++;
      switch(c) {
        case 'd':
          sprintf(data, "%d", *((unsigned *)arg++));
          goto print_s;

        case 'x':
          sprintf(data, "%x", *((unsigned *)arg++));
          goto print_s;

        case 's':
          sprintf(data, "%s", *((unsigned *)arg++));
          goto print_s;

        case 'c':
          sprintf(data, "%c", *((unsigned *)arg++));
          goto print_s;

        case 'l':
          c = *fmt++;
          sprintf(data, "%lf", *((unsigned *)arg++));
          goto print_s;

        case '.':
          c = *fmt++;
          ci = c;
          c = *fmt++;  c = *fmt++;
          if (ci == '0') sprintf(data, "%.0lf", *((unsigned *)arg++));
          else if (ci == '1') sprintf(data, "%.1lf", *((unsigned *)arg++));
          else if (ci == '2') sprintf(data, "%.2lf", *((unsigned *)arg++));
          else if (ci == '3') sprintf(data, "%.3lf", *((unsigned *)arg++));
          else if (ci == '4') sprintf(data, "%.4lf", *((unsigned *)arg++));
          else if (ci == '5') sprintf(data, "%.5lf", *((unsigned *)arg++));
          else sprintf(data, "%lf", *((unsigned *)arg++));
          goto print_s;

					print_s:
					p = data;
					rprintf(p);
          break;

        default:
        charput(c);
      }
    }
  }
}

int getLine (char* buf, unsigned int len) {
  unsigned int count=0;

  for ( count=0; count<len; ++count) {
    char oneCharacter = charget ();

    if ( oneCharacter == '\n' || oneCharacter == '\r' ) {
      buf[ count ]   = '\0';
      return 0;
    }

    buf[count] = oneCharacter;
  }
  
  buf[ len ] = '\0';
  return 1;
}


int putLine (char* buf) {
  unsigned int count;
  char current;
  
  for ( count = 0, current = buf[0]; current != '\0'; current = buf[++count] ) {
    charput (current);
  }
  
  charput('\r');
  charput('\n'); 
  return 0;
}

void abort(void){}
