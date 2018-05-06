#include <stdio.h>
#include <conio.h>
#include <_6551.h>
#include <peekpoke.h>
#include <telestrat.h>

extern int rs232(void);
extern void rs232_console();
extern void send_byte_rs232();

#define ACIA_TXE	 0x10


#define DATA_6551_REGISTER 0x31C
#define STATUS_6551_REGISTER 0x31D
#define COMMAND_6551_REGISTER 0x31E
#define CONTROL_6551_REGISTER 0x31F

void jasmin_menu()
{
}

void joystick_menu()
{
	unsigned char control;
	unsigned char control_button;
	printf("Press any joysticks\n");
	POKE(0x0322,128+64);
	POKE(0x0320,128+64);
	while (1)
	{
		control=PEEK(0x320);
		control_button=PEEK(0x321);
		printf("control %d\n",control);
		if (control==254)
			printf("Right\n");
		if (control==253)
			printf("Left\n");		
		if (control==255-4)
			printf("fire\n");		
		if (control==255-8)
			printf("down\n");
		if (control==255-16)
			printf("up\n");
		if (control_button&32==0)
		    printf("third button\n");
		if (control_button&128==0)
		    printf("Second button\n");		
		}
}


void wait()
{
	unsigned char i;
	for (i=0;i<0x68;i++);
}


void send_byte(unsigned char car)
{
	while((PEEK(STATUS_6551_REGISTER)&ACIA_TXE)!=ACIA_TXE)
	{
		printf("Waiting ...\n");
	}
	printf("Sending : %d\n",car);
	POKE(DATA_6551_REGISTER,car);
	wait();
}

void setcommand_rs232()
{
  printf("Setting control register\n");
  printf("* Set 9600 bauds\n"); // 
  printf("* 1 stop bit\n"); // 
  printf("* Word length 8\n"); 
  printf("* Baud rate clock\n"); // 16
  
  POKE(CONTROL_6551_REGISTER,0+2+4+8+16);
  
  printf("Setting command register\n");
  printf("* Disable IRQ\n");
  printf("* DTR ready\n");
  printf("* transmitter intrrupt control : do not use\n");
  POKE(COMMAND_6551_REGISTER,1+2+4+8);

}

void print_6551_status_register(unsigned char       status)
{
  printf("Status   : 0x%x\n",status);
  printf("      b7 (irq)     : 0x%x\n",status&128);
  printf("      b6 (dsrb)    : 0x%x\n",status&64);
  printf("      b5 (dcdb)    : 0x%x\n",status&32);
  printf("      b4 (tdre)    : 0x%x\n",status&16);
  printf("      b3 (rdrf)    : 0x%x\n",status&8);
  printf("      b2 (overrun) : 0x%x\n",status&4);  
  printf("      b1 (FE)      : 0x%x\n",status&2);    
  printf("      b0 (PE)      : 0x%x\n",status&1);    
}

void rs232_menu()
{
  unsigned char key;
  unsigned char       data;           /* Data register */
  unsigned char       status;         /* Status register */
  unsigned char       cmd;            /* Command register */
  unsigned char       ctrl;           /* Control register */
  static unsigned char i;
  
  while (1)
  {
    clrscr();
    printf("Read RS232 input and displays .. 1\n");
    printf("Output ACIA registers         .. 2\n");
    printf("Send 'A' 20 times             .. 3\n");
    printf("Start console                 .. 4\n");
    printf("Set command register          .. 5\n");
    printf("Quit menu                     .. 6\n");
    key=cgetc();
    if (key=='2')
    {
      data=PEEK(DATA_6551_REGISTER);
      status=PEEK(STATUS_6551_REGISTER);
      cmd=PEEK(COMMAND_6551_REGISTER);
      ctrl=PEEK(CONTROL_6551_REGISTER);
      print_6551_status_register(status);
       
      printf("Control : 0x%x\n",ctrl);
      printf("Cmd : 0x%x\n",cmd);
      printf("data : 0x%x\n",data);
    }
    if (key=='3')
    {
      setcommand_rs232();
	  
	  status=PEEK(STATUS_6551_REGISTER);
      print_6551_status_register(status);
	  
      for(i=0;i<20;i++)
      {
        printf("%d .. ",i);
        //POKE(DATA_6551_REGISTER,0x42);
		
		send_byte('A');  
		print_6551_status_register(status);
        send_byte_rs232();
		print_6551_status_register(status);
      }

      printf("\n");
    }
    if (key=='4')
    {
      rs232_console();
    }
    
    if (key=='5')
    {
      setcommand_rs232();
    }
        
    
    if (key=='6')
    {
      break;
    }
    printf("Press a key ... \n");
    key=cgetc();
  }
}


int main ()
{
  unsigned char key;
  clrscr();

  cputc(CH_ULCORNER);
  chline(38);
  cputc(CH_URCORNER);
  printf("|                 Orixdbg              |");
  cputc(CH_ULCORNER);
  chline(38);
  cputc(CH_URCORNER);  
  textcolor(COLOR_GREEN);
  printf("|Start rs232 tool                    |1|"); 
  cputc(CH_ULCORNER);
  chline(38);
  textcolor(COLOR_GREEN);
  cputc(CH_ULCORNER);
  printf("|Start joystick tool                 |2|"); 
  cputc(CH_ULCORNER);
  chline(38);
  
  cputc(CH_URCORNER);  
  printf("|Quit                                |3|");
  cputc(CH_ULCORNER);
  chline(38);
  cputc(CH_URCORNER);
  while (1)
  {
    key=cgetc();
    if (key=='1')
      rs232_menu();
    if (key=='2')
      joystick_menu();
  
    
    if (key==27 ||key=='3')
      break;
  }
    //rs232();
  return 1;
}