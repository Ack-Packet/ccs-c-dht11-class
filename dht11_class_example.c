#include <16F877A.h>

#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG

#use delay(crystal=16MHz)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=esp,errors)

#define portd (*((unsigned int*)0x08))
#define trisd (*((unsigned int*)0x88))

#include <dht11_class.c>

/*
void bit_set(unsigned int port,unsigned int pin)
{
   port=(port | (0x01<<pin));
}
*/

/*
void bit_clear(unsigned int port,unsigned int pin)
{
   port=(port & ~(0x01<<pin));
}
*/
void main()
{   
   trisd=0x00;
   portd=0x00;
   
   struct dht11class dht1;
   struct dht11class dht2;
   
   dht11_init(0);
   dht11_init(1);
   
   delay_ms(1000);
   
   while(TRUE)
   {
      dht1=dht11_read(0);
      dht2=dht11_read(1);
      
      fprintf(esp,"1: %u.%u  %u.%u\r\n",dht1.data[0],dht1.data[1],dht1.data[2],dht1.data[3]);
      fprintf(esp,"2: %u.%u  %u.%u\r\n\r\n",dht2.data[0],dht2.data[1],dht2.data[2],dht2.data[3]);
      delay_ms(100);
   }
}
