​//variable declaration

unsigned int pulserate, pulsecount,a;

unsigned int i;

countpulse();

sbit IR_Tx at RA3_bit;

//LCD pin initialisation

sbit LCD_RS at RB4_bit;

sbit LCD_EN at RB5_bit;

sbit LCD_D4 at RB0_bit;

sbit LCD_D5 at RB1_bit;

sbit LCD_D6 at RB2_bit;

sbit LCD_D7 at RB3_bit;

//direction set

sbit LCD_RS_Direction at TRISB4_bit;

sbit LCD_EN_Direction at TRISB5_bit;

sbit LCD_D4_Direction at TRISB0_bit;

sbit LCD_D5_Direction at TRISB1_bit;

sbit LCD_D6_Direction at TRISB2_bit;

sbit LCD_D7_Direction at TRISB3_bit;

//message

char message1[] = " Your Heart Rate Is"; 

char p[3]; 

char message3[] = "Normal!\0"; 

char message4[] = "High! Run to Doc\0"; 

char message5[] = "Ohh!low\0"; 

char message6[] = "place your finger"; 

char message7[] = "processing..."; 

void delay_debounce(){               //delay after message display

Delay_ms(300); 

}

void delay_refresh(){

Delay_ms(10); 

}

void Move_Delay() {                    // Function used for text moving

 Delay_ms(300);                        // You can change the moving speed here

}

countpulse(){

Lcd_Cmd(_LCD_CLEAR);                    // Clear display 

Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off 

Lcd_Out(1,1,message7); 

delay_debounce(); 

delay_debounce(); 

TMR0=0 ;

Delay_ms(15000);  // Delay 1 Sec 

IR_Tx = 0; 

pulsecount = TMR0; 

pulserate = pulsecount*4; 

a=pulserate;

}

void main() {

CMCON = 0x07;                         // Disable Comparators

TRISA = 0b00110000;                // RA4/T0CKI input, RA5 is I/P only

TRISB = 0b00000000;                // RB7 input, rest output

OPTION_REG = 0b00101000;     // Prescaler (1:1), TOCS =1 for counter mode

 Lcd_Init();                               // Initialize LCD

 TMR0=0 ;

 IR_Tx = 1;

 test:

 Lcd_Cmd(_LCD_CLEAR);             // Clear display

 Lcd_Cmd(_LCD_CURSOR_OFF);   // Cursor off

 Lcd_Out(1,1,message6);

 for(i=0; i<17; i++) {                      // Moving text

   Lcd_Cmd(_LCD_SHIFT_RIGHT);   // Move text to the right 17 times

   Move_Delay();

 }

Delay_ms(2000);

 if(TMR0>0){                           //checking timer is  0 initially

 countpulse();                         //timer>0 if finger is placed

  }

  else {

  for(i=0; i<17; i++) {                // Move text to the left 17 times

     Lcd_Cmd(_LCD_SHIFT_LEFT);

     Move_Delay();

   }

  goto test;

  }

Lcd_Cmd(_LCD_CLEAR);                     // Clear display

 Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

 Lcd_Out(1,1,message1);

   for(i=0; i<16; i++) {                           // Moving text

   Lcd_Cmd(_LCD_SHIFT_RIGHT);          // Move text to the right 16 times

   Move_Delay();

 }

   Lcd_Cmd(_LCD_CLEAR);                      // Clear display

 Lcd_Cmd(_LCD_CURSOR_OFF);              //cursor off

           

           a=pulserate;

           IntToStr(pulserate,p);                  //integer to string conversion

do {

         if(a<60){                             //display if pulserate<60

  Lcd_Out(1,1,message5);

  Delay_ms(2000);

  Lcd_Out(2,1,p);

  }

if(a>59&&a<100)                          //display if 59<pulserate<100 

           {

Lcd_Out(1,1,message3); 

Delay_ms(2000); 

 Lcd_Out(2,1,p);

  }

if(a>100)                                      //dispaly if pulserate>100  

 {

 Lcd_Out(1,1,message4);

 Delay_ms(2000);

 Lcd_Out(2,1,p);

   }

 Delay_ms(2000);

 Lcd_Cmd(_LCD_CLEAR);

 Lcd_Cmd(_LCD_CURSOR_OFF);

 } while(1);

}