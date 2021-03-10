#include <16F886.h>
#device ADC=10 *=16
 
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 
 
#use delay(clock=8M)
 
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
 
#define RUN_BUTTON   PIN_B7
int16 START_TIME = 65059;
 
//Happy Birthday
int16 arr[25] = {
65059,65059,65111,65059,65179,65157,65059,65059,65111,65059,65218,65179,
65059,65059,65306,65252,65179,65157,65111,
65268,65268,65252,65179,65218,65179
};
int16 time[25] = {
100,80,140,120,120,140,100,80,140,120,120,140,100,80,140,140,120,120,120,100,80,140,120,120,120
};
 
#INT_TIMER1
void timer1_isr(){
   set_timer1(START_TIME);
   output_toggle(PIN_A0);
}

void inputHandling(){
   
}

void main()
{
   int i = 0;
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
   set_timer1(START_TIME);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   int c = 0;
   int song_on = 0;
   int ax = 0;
   int bx = 0;
   While(1){
      if( c==0 ){
         if(!input(PIN_A3)){
            if(song_on == 0){
               song_on = 1;
            }
            else {
               song_on = 0;  
            }
            i=0;
            c=1;
         }
      }else {
         if(input(PIN_A3)){
            c=0;
         }    
      }   
      if(!input(PIN_B7) && song_on == 0){
         START_TIME = 65306;// C 1043Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B5) && song_on == 0){
         START_TIME = 65333;// D 1175Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B4) && song_on == 0){
         START_TIME = 65356;// E 1319Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B3) && song_on == 0){
         START_TIME = 65367;// F 1399Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B2) && song_on == 0){
         START_TIME = 65386;// G 1565Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B1) && song_on == 0){
         START_TIME = 65404;// A 1764Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_B0) && song_on == 0){
         START_TIME = 65418;// B 1972Hz
         enable_interrupts(INT_TIMER1);
      }else if(!input(PIN_A1) && song_on == 0){
         START_TIME = 65426;// C High 2088Hz
         enable_interrupts(INT_TIMER1);
      }else if(song_on == 1){
         if(ax%2 == 0){
            if(!bx){
               START_TIME = arr[i%29];
               enable_interrupts(INT_TIMER1);
               i++;
               bx=1;
            }else{
               bx=0;
            }
         }
         ax++;
         delay_ms(time[(i%30)-1]);
      }else{
         START_TIME = 0;
         i=0;
      }   
   }  
}
