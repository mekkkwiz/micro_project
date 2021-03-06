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
#define _FLEX_LCD216_H  //  LCD Type 16x2
//#define _FLEX_LCD416_H  //  LCD Type 16x4
// Assign MCU's pin to LCD
#define LCD_DB4   PIN_A0
#define LCD_DB5   PIN_A1
#define LCD_DB6   PIN_A2
#define LCD_DB7   PIN_A3
#define LCD_RS    PIN_C1
#define LCD_E     PIN_A5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lcd.c>


int16 START_TIME = 65059;

//!//Happy Birthday
// int16 arr[25] = {
// 65059,65059,65111,65059,65179,65157,65059,65059,65111,65059,65218,65179,
// 65059,65059,65306,65252,65179,65157,65111,
// 65268,65268,65252,65179,65218,65179
// };
// int16 time[25] = {
// 100,80,140,120,120,140,100,80,140,120,120,140,100,80,140,140,120,120,120,100,80,140,120,120,120
// };

#INT_TIMER1
void timer1_isr(){
   set_timer1(START_TIME);
   output_toggle(PIN_B6);
}

//lcd display function
void lcd_Show(long f){
      lcd_gotoxy(5, 2);           // Go to column 5 row 2
      printf(lcd_putc,"%lu",f);
      lcd_gotoxy(12,2);
      lcd_putc("Hz");
}

//calculate given frequency to timer
int16 convertTimer(long f){
   return 65536 - (1000000/(4*f));
}

void main()
{
   lcd_init();
   //initial code for setup timer for interrupt
   lcd_putc('\f');
   lcd_gotoxy(5, 1); 
   lcd_putc("WELCOME"); 
   lcd_gotoxy(1, 2);           
   lcd_putc("CYBMCYSSBSSNTMMC");   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
   set_timer1(START_TIME);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   //-----------------------------------------------------//
   //var decaration
   int lastButton = -1;
   long inputFeq = 500; 
   int fakePointer = -1;
   //-----------------------------------------------------//
//!   long default_feq [6] = {1043, 1175, 1319, 1399, 1565, 1764};
   int16 d_but1 = 65306;
   int16 d_but2 = 65333;
   int16 d_but3 = 65356;
   int16 d_but4 = 65367;
   int16 d_but5 = 65386;
   int16 d_but6 = 65404;
//!   long current_feq [6];
//    copy arr from defalut -> current for initialize value
   int16 c_but1 = d_but1;
   int16 c_but2 = d_but2;
   int16 c_but3 = d_but3;
   int16 c_but4 = d_but4;
   int16 c_but5 = d_but5;
   int16 c_but6 = d_but6;
   
   int16 c_feq_but1 = 1043;
   int16 c_feq_but2 = 1175;
   int16 c_feq_but3 = 1319;
   int16 c_feq_but4 = 1399;
   int16 c_feq_but5 = 1565;
   int16 c_feq_but6 = 1764;
   //-----------------------------------------------------//
   While(1){
      switch(fakePointer){
            case 1:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT1_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but1);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 2:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT2_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but2);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     lcd_Show(c_feq_but2);
                     break;
            case 3:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT3_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but3);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 4:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT4_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but4);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 5:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT5_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but5);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 6:  lcd_putc('\f');
                     lcd_gotoxy(5, 1); 
                     lcd_putc("BT6_FEQ"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",c_feq_but6);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 7:  lcd_putc('\f');
                     lcd_gotoxy(4, 1); 
                     lcd_putc("FEQ_RESET"); 
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",inputFeq);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");

                     c_but1 = d_but1;
                     c_but2 = d_but2;
                     c_but3 = d_but3;
                     c_but4 = d_but4;
                     c_but5 = d_but5;
                     c_but6 = d_but6;

                     c_feq_but1 = 1043;
                     c_feq_but2 = 1175;
                     c_feq_but3 = 1319;
                     c_feq_but4 = 1399;
                     c_feq_but5 = 1565;
                     c_feq_but6 = 1764;

                     fakePointer = -1;
                     break;
            case 11: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT1_FEQ_SET");
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 12: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT2_FEQ_SET"); 
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 13: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT3_FEQ_SET"); 
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 14: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT4_FEQ_SET"); 
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 15: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT5_FEQ_SET"); 
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 16: lcd_putc('\f');
                     lcd_gotoxy(3, 1); 
                     lcd_putc("BT6_FEQ_SET"); 
                     lcd_gotoxy(5, 2);
                     printf(lcd_putc,"%lu",inputFeq);
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            case 99: lcd_putc('\f');
                     lcd_gotoxy(4, 1); 
                     lcd_putc("CURRENT_FEQ");
                     lcd_gotoxy(5, 2);           // Go to column 7 row 2
                     printf(lcd_putc,"%lu",inputFeq);   // Write num with 5 numbers max
                     lcd_gotoxy(12,2);
                     lcd_putc("Hz");
                     fakePointer = -1;
                     break;
            defalut: disable_interrupts(INT_TIMER1);
                     output_low(PIN_A7);
                     break;
                     
                     
         }
      if (!input(PIN_C2)){//reset
         inputFeq = 500;
         lcd_putc('\f');
         fakePointer = 7;
         printf("reset pressed\n");
         
      }
      if (!input(PIN_B5)){//inc
         if(inputFeq < 25000){
            inputFeq++;
         }
         else {
            inputFeq = 25000;
            
         }
         fakePointer = 99;
         printf("inc pressed\n");
      }
      if (!input(PIN_B4)){//dec
         if(inputFeq >500){
            inputFeq--;
         }
         else {
            inputFeq = 500;
         }
         fakePointer = 99;
         printf("dec pressed\n");
      }

      if(!input(PIN_B7)){
         switch(lastButton)
         {
         case 1:  c_but1 = convertTimer(inputFeq);
                  c_feq_but1 = inputFeq;
                  fakePointer = 11;
                  printf("set pressed\n");
                  break;
         case 2:  c_but2 = convertTimer(inputFeq);
                  c_feq_but2 = inputFeq; 
                  fakePointer = 12; 
                  printf("set pressed\n");
                  break;
         case 3:  c_but1 = convertTimer(inputFeq);
                  c_feq_but3 = inputFeq; 
                  fakePointer = 13;  
                  printf("set pressed\n");
                  break;
         case 4:  c_but1 = convertTimer(inputFeq);
                  c_feq_but4 = inputFeq; 
                  fakePointer = 14;
                  printf("set pressed\n");
                  break;
         case 5:  c_but1 = convertTimer(inputFeq);
                  c_feq_but5 = inputFeq; 
                  fakePointer = 15;  
                  printf("set pressed\n");
                  break;
         case 6:  c_but1 = convertTimer(inputFeq);
                  c_feq_but6 = inputFeq; 
                  fakePointer = 16;
                  printf("set pressed\n");
                  break;
         }
      }
      
      if(!input(PIN_B3)){
         output_high(PIN_A7);
         lastButton = 1;
         START_TIME  = c_but1;
         enable_interrupts(INT_TIMER1);
         printf("1 pressed\n");
         fakePointer = 1;
      }
      else if(!input(PIN_B2)){
         output_high(PIN_A7);
         lastButton = 2;
         START_TIME  = c_but2;
         enable_interrupts(INT_TIMER1);
         printf("2 pressed\n");
         fakePointer = 2;
      }
      else if(!input(PIN_B1)){
         output_high(PIN_A7);
         lastButton = 3;
         START_TIME  = c_but3;
         enable_interrupts(INT_TIMER1);
         printf("3 pressed\n");
         fakePointer = 3;
         lcd_Show(c_feq_but3);
      }
      else if(!input(PIN_B0)){
         output_high(PIN_A7);
         output_high(PIN_A7);
         lastButton = 4;
         START_TIME  = c_but4;
         enable_interrupts(INT_TIMER1);
          printf("4 pressed\n");
         fakePointer = 4;
         lcd_Show(c_feq_but4);
      }
      else if(!input(PIN_C5)){
         output_high(PIN_A7);
         lastButton = 5;
         START_TIME  = c_but5;
         enable_interrupts(INT_TIMER1);
          printf("5 pressed\n");
         fakePointer = 5;
         lcd_Show(c_feq_but5);
      }
      else if(!input(PIN_C4)){
         output_high(PIN_A7);
         lastButton = 6;
         START_TIME  = c_but6;
         enable_interrupts(INT_TIMER1);
         printf("6 pressed\n");
         fakePointer = 6;
         lcd_Show(c_feq_but6);
      }
      
   }  
}
