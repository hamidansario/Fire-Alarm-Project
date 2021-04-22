#include<reg51.h>
sbit sensor=P1^0;
sbit rs=P1^1;
sbit rw=P1^2;
sbit en=P1^3;
sbit buzzer=P3^0;
void lcdinit();
void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcddis(unsigned char *);
void delay();
void main()
{
	buzzer=0;
	sensor=0;
	back:lcdinit();
	lcddis(" FIRE ALERT ");
	lcdcmd(0xc0);
	lcddis("  SYSTEM  ");
	delay();
	while(1)
	{
		if(sensor==1)
		{
			lcdcmd(0x01);
			lcddis("FIRE DETECTED");
			buzzer=1;
		}
		goto back;
	}
}
void lcdinit()
{
	lcdcmd(0x38);
	lcdcmd(0x01);
	lcdcmd(0x10);
	lcdcmd(0x0c);
	lcdcmd(0x80);
}
void lcdcmd(unsigned char val)
{
	P2=val;
	rs=0;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddis(unsigned char *s)
{
	unsigned char w;
	for(w=0;s[w]!='\0';w++)
	{
		lcddat(s[w]);
	}
}
void delay()
{
	unsigned int v1;
	for(v1=0;v1<10000;v1++);
}
	
	