#include <stdio.h>
#include <conio.h>
#include <_6551.h>
#include <peekpoke.h>
#include <telestrat.h>

extern int rs232(void);
extern void rs232_console();
extern void send_byte_rs232();

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
    printf("Send 'A' 200 times            .. 3\n");
    printf("Start console                 .. 4\n");
    printf("Quit menu                     .. 5\n");
    key=cgetc();
    if (key=='2')
    {
      data=PEEK(0x31C);
      status=PEEK(0x31D);
      cmd=PEEK(0x31E);
      ctrl=PEEK(0x31F);
      print_6551_status_register(status);
       
      printf("Control : 0x%x\n",ctrl);
      printf("Cmd : 0x%x\n",cmd);
      printf("data : 0x%x\n",ctrl);
    }
    if (key=='3')
    {
      for(i=0;i<20;i++)
      {
        printf("%d .. ",i);
        status=PEEK(0x31D);
        print_6551_status_register(status);
        send_byte_rs232();
      }
      printf("\n");
    }
    if (key=='4')
    {
      rs232_console();
    }
    
    if (key=='5')
    {
      break;
    }
    printf("Press a key ... \n");
    key=cgetc();
  }
}
/*
#define ACIADR $031C ; DATA REGISTER
#define ACIASR $031D ; STATUS REGISTER
#define ACIACR $031E ; command register
#define ACIACT $031F ; control register


*/

int main ()
{
  unsigned char key;
  clrscr();
  //textcolor(COLOR_RED);
  //cputc('b');
  //puts("fff");
  cvline (5);
  //gotoxy (10,10);
  //cprintf("Hello");
  printf("Orixdbg\n");
  textcolor(COLOR_GREEN);
  printf("Start rs232 tool .. 1\n");  
  printf("Quit             .. 2\n");
  while (1)
  {
    key=cgetc();
    if (key=='1')
      rs232_menu();
    
    if (key==27 ||key=='2')
      break;
  }
    //rs232();
  return 1;
}