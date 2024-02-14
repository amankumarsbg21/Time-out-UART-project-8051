//wap to receive 5 bytes & transmitt it back through UART,toggle the LED connected to
//P1.0, 5 times & stop the reception, if the time span between any two receptions is
//equal to or more than 1 sec  (use TIMER 0 with interrupt approach)

#include<reg51.h>
int i=0;
int t=0;
unsigned long j=0;
sbit LED=P1^0;
sbit LEDY=P1^1;
sbit sw=P2^0;
unsigned char c[6]={'\0'};
void Toggle(void);
void ToggleY(void);
int f=0;

void main(void)
{
	while(1)
	{ sw=1;
		LED=0;
		LEDY=0;
		SCON=0x50;
		TMOD=0x21;
		TH1=253;
		TL1=253;
		TR1=1;
		TH0=0x4B;
		TL0=0xFD;
		IE=0x82;
		for(i=0;i<5;i++){
		  while(RI==0){		
				if(f==1){ Toggle();break;}
			}
			c[i]=SBUF;
			t=0;	
			TR0=1;
		  RI=0;
		}


		for(i=0;i<5&&f==0;i++){
			
			SBUF=c[i];
		  while(TI==0);
		  TI=0;
		}
		if(f==0) ToggleY();
		while(sw==1)f=0 ;
	}
}

void Toggle(void){
	for(i=0;i<10;i++){
		LED=~LED;
		for(j=0;j<10000;j++);
	}

}
void ToggleY(void){
	for(i=0;i<10;i++){
		LEDY=~LEDY;
		for(j=0;j<10000;j++);
	}

}

void Isr_timer0(void) interrupt 1{
	TF0=0;
	TR0=0;
	TH0=0x4B;
	TL0=0xFD;
	TR0=1;
	t++;
	if(t==20){f=1;}
}























