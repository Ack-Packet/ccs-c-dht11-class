struct dht11class
{
   unsigned int data[4];
};

void dht11_init(unsigned int pin)
{
   bit_set(portd,pin);
}

unsigned int get_bytes(unsigned int pin)
{
   int i=8;
   unsigned int8 ret=0;
   
   while(i--)
   {
      while(!((portd>>pin)&0x01));
      
      delay_us(40);
      
      if((portd>>pin)&0x01)
      {
         bit_set(ret,i);
         while(((portd>>pin)&0x01));
      }
   }
   
   return ret;
}

struct dht11class dht11_read(unsigned int pin)
{
   struct dht11class dht;
   
   bit_clear(portd,pin);
   delay_ms(30);
   bit_set(portd,pin);
   delay_us(40);
   //bit_set(trisd,pin);
   
   while(((portd>>pin)&0x01));
   while(!((portd>>pin)&0x01));
   while(((portd>>pin)&0x01));
   
   for(int i=0;i<4;i++)
   {
      dht.data[i]=get_bytes(pin);
   }
   
   //bit_clear(trisd,pin);
   bit_set(portd,pin);
   
   return dht;
}
