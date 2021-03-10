//Project        : LCD print out
//Purpose        : Test LCD Module
//Auther         : JUMP start innovation
//Email          : jumpstartinnovation@gmail.com
//Complier       : CCS.PCWH.v4.134
//Hardware       : PIC18F2550
//**********************************************************

#include <16f886.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// *** Device Specification ***
#fuses HS            // use Oscillator mode HS
#fuses NOWDT   // doesn't use watch dog
#fuses NOLVP         // doesn't use Low Voltage for program
#fuses NOPROTECT     // No program detect

#use delay (clock=8M, crystal)
// use built-in function: delay_ms() & delay_us() by crytal 20MHz

#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7,stream=HOSTPC,errors)

#define _FLEX_LCD216_H  //  LCD Type 16x2
//#define _FLEX_LCD416_H  //  LCD Type 16x4
// Assign MCU's pin to LCD
#define LCD_DB4   PIN_A0
#define LCD_DB5   PIN_A1
#define LCD_DB6   PIN_A2
#define LCD_DB7   PIN_A3
#define LCD_RS    PIN_C1
#define LCD_E     PIN_A5
//#define LCD_RW    PIN_B1  // Doesn't use RW connect to GND
#include <lcd.c> // include LCD library CCS C

/*******************************************************************************
*  Function prototypes
********************************************************************************/
void headle(void);

/***********************************************************************
 * FUNCTION:    headle
 * DESCRIPTION: Show headle title though rs232
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void headle(void){
                fprintf(HOSTPC,"\n\r******************************************************\n\r");
                fprintf(HOSTPC,"Project        : LCD print out\n\r");
                fprintf(HOSTPC,"Purpose        : Test LCD Module\n\r");
                fprintf(HOSTPC,"Auther         : JUMP start innovation\n\r");
                fprintf(HOSTPC,"Email          : jumpstartinnovation@gmail.com\n\r");
                fprintf(HOSTPC,"Complier       : CCS.PCWH.v4.134\n\r");
                fprintf(HOSTPC,"Hardware       : PIC18F2550\n\r");
                fprintf(HOSTPC,"**********************************************************\n\r");
    }


/***********************************************************************
 * FUNCTION:    main
 * DESCRIPTION: main function
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void main(void){

 headle(); //show message output to serial port

        lcd_init(); //Initial LCD
        fprintf(HOSTPC,">> LCD Initial ... DONE\n\r");
        char a[] = "YOYO";
        long  num = 500;
        while(true){

//!            printf(lcd_putc,"\f");  //clear LCD screen
//!
//!            lcd_gotoxy(4,1); //goto lcd position x=1, y=1
//!            printf(lcd_putc,a);
//!            
//!            lcd_gotoxy(2,2); //goto lcd position x=2, y=2
//!            printf(lcd_putc,num);
//!            
//!            delay_ms(1000);
//!
//!            // clear LCD screen line 1
//!            lcd_gotoxy(16, 1); //goto lcd position x=16, y=1
//!            for(int i=0; i < 16; i++){
//!                printf(lcd_putc," \b\b"); //back space
//!                delay_ms(100);
//!            }
//!
//!            // clear LCD screen line 2
//!            lcd_gotoxy(16, 2); //goto lcd position x=16, y=1
//!            for(int i=0; i < 16; i++){
//!                printf(lcd_putc," \b\b"); //back space
//!                delay_ms(100);
//!            }
               //lcd_putc('\f');
               lcd_gotoxy(4, 1);           // Go to column 4 row 1
               lcd_putc("TEST_BUTTON");
//!               for(int i = 0; i < 200; i++){
//!                  lcd_gotoxy(7, 2);           // Go to column 7 row 2
//!                  printf(lcd_putc,"%3u",(int)i);   // Write i with 3 numbers max
//!                  delay_ms(100);
//!               }
               
              lcd_gotoxy(5, 2);           // Go to column 7 row 2
                  printf(lcd_putc,"%lu",num);   // Write num with 5 numbers max
              if(input(PIN_B7)){
              num++;
              }
              if(input(PIN_B5)){
              num--;
              }
              if(input(PIN_C2)){
              lcd_putc('\f');
              num = 500;
              }
              lcd_gotoxy(12,2);
              lcd_putc("Hz");
              //delay_ms(1000);

        }
}
