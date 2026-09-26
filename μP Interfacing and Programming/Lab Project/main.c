#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 20000000

// ============ CONFIG BITS ============
#pragma config FOSC = HS     // Using 8MHz crystal
#pragma config WDTE = OFF    // No watchdog needed
#pragma config PWRTE = ON    // Wait for power to stabilize
#pragma config BOREN = ON    // Prevent reset during voltage drops
#pragma config LVP = OFF     // Disable low-voltage programming
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


// ============ LCD PINS ============
#define RS RB1
#define EN RB2

// ============ FUNCTION PROTOTYPES ============
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INIT(void);
void LCD_DELAY(void);
void LCD_String(const char *);
void ClearUID(void);

// ============ RFID BUFFER ============
char UID[13];
unsigned char i = 0;

// =================================================
// UART INTERRUPT
// =================================================
void __interrupt() ISR(void)
{
    if (RCIF==1)
    {
         char data = RCREG;
    
          
       // Accept ONLY hex characters 0-9 A-F
        if ((data >= '0' && data <= '9') || (data >= 'A' && data <= 'F'))
            
        {
            if (i < 12){
                UID[i++] = data;
              
            
             if(i == 12)
                UID[12] = '\0'; //  Null terminate
           
            
            }    
       
        }
        // Handle UART overrun
        if (OERR) {
            CREN = 0;
            CREN = 1;
        }
      RCIF = 0;   // Clear interrupt flag
    }   
}  

// =================================================
// MAIN PROGRAM
// =================================================
void main(void)
{
    TRISD = 0x00;    // LCD data port
    TRISC = 0x80;    // RC7 = RX
    TRISB = 0x00;    // Buzzer + LED

    RB0 = 0;         // Buzzer
    RB7 = 0;         // LED

 
    
    SPBRG = 129;       // 9600 baud @ 20MHz
    TXSTA = 0x24;      // BRGH=1, TXEN=1
    RCSTA = 0x90;      // SPEN=1, CREN=1

    // Interrupts
    GIE = 1; PEIE = 1; RCIE = 1;

    // LCD
    LCD_INIT();
    LCD_String("RFID SYSTEM");
    __delay_ms(3000);
    LCD_CMD(0x01);
    LCD_String("Scan Your Card");

    while (1)
    {
         
      if(i == 12){
         
           //ensure null terminated
            UID[12] = '\0';
            
             LCD_CMD(0x01);
            LCD_String("Student UID:");
            LCD_CMD(0xC0);
            LCD_String(UID);
            __delay_ms(1500);
        
              if(strcmp(UID, "02006A0B2645") == 0 || strcmp(UID, "0200695B8EBE") == 0)
                   {
                        RB7 = 1;  // LED
                        RB0 = 0;  // Buzzer off
                        
                        LCD_CMD(0x01);
                        LCD_String("Attendance ");
                        LCD_CMD(0xC0);
                        LCD_String("Marked");
                        __delay_ms(2000);
                        RB7=0;
                         
                    }
             
               else
                    {
                        RB7 = 0;
                        RB0 = 1;
                     
                     
                        LCD_CMD(0x01);
                        LCD_String("Invalid Card");
                        __delay_ms(1500);
 
                        RB0=0;

                    }
                        
                        ClearUID();
                        LCD_CMD(0x01);
                        LCD_String("Scan Your Card");
                   }

    }
}
void ClearUID(void)
{
    unsigned char k;
    for (k = 0; k < 13; k++)
        UID[k] = '\0';
    i = 0;
}

// =================================================
// LCD FUNCTIONS 
// =================================================

void LCD_CMD(unsigned char cmd)
{
    RS = 0;
    PORTD = cmd;
    EN = 1;
    __delay_ms(2);
    EN = 0;
    LCD_DELAY();
}

void LCD_DATA(unsigned char data)
{
    RS = 1;
    PORTD = data;
    EN = 1;
    __delay_ms(2);
    EN = 0;
    LCD_DELAY();
}

void LCD_INIT(void)
{
    LCD_CMD(0x38);   // 8-bit mode
    LCD_CMD(0x0C);   // Display ON
    LCD_CMD(0x06);   // Auto increment
    LCD_CMD(0x01);   // Clear screen
    __delay_ms(2);
}

void LCD_DELAY(void)
{
    unsigned char i;
    for(i=0; i<250; i++);
}

void LCD_String(const char *s)
{
    while(*s)
        LCD_DATA(*s++);
}
