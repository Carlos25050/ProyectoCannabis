/*!
\file   seguridad.c
\date   2022-06-28
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  Security House.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic16f887.h>  /*Header file PIC16f887 definitions*/
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "adc.h"
#include <math.h>

/*Variables definidas*/
#define Data_Out PORTDbits.RD2        /* assign Port pin for data*/
#define Data_In PORTDbits.RD2       /* read data from Port pin*/
#define Data_Dir TRISDbits.TRISD2     /* Port direction */
#define _XTAL_FREQ 8000000          /* define _XTAL_FREQ for using internal delay */
#define Data_Out_led0_hum PORTEbits.RE0 //Pin de salida RE0 para led 0
#define Data_Out_led1_hum PORTEbits.RE1 //Pin de salida RE1 para led 1
#define Data_Out_led2_hum PORTEbits.RE2 //Pin de salida RE2 para led 2
#define Data_Out_led0_tem PORTEbits.RE0 //Pin de salida RE0 para led 0
#define Data_Out_led1_tem PORTEbits.RE1 //Pin de salida RE1 para led 1
#define Data_Out_led2_tem PORTEbits.RE2 //Pin de salida RE2 para led 2

/*Asignacion de variables*/
char Temperature[5];
int value_adc;
char value_humedad[5];
double tempC;
char lm35;

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();


void main() {
    char RH_Decimal ,RH_Integral,T_Decimal,T_Integral;
    unsigned char temp_val;
    unsigned char Hum_val;
    char value[10];   
    //Configura Fosc = 8Mhz interno, Fuente de Fosc del sistema = interno
    OSCCON = 0x71; //Configura oscilador interno (FOSC = 8Mhz)
    LCD_Init(); //Inicializa el LCD
    ADC_Init();
    LCD_String_xy(0,0,"Monitoreo");
    __delay_ms(2000);
    LCD_Command(0xC0);
     
    ANSELH=0;
    TRISB0=0;
    OSCCON = 0x71;   /* set internal oscillator with frequency 8 MHz*/
    TRISE0 = 0;//Indica que el bit 0 en el puertoE es salida.
    TRISE1 = 0;//Indica que el bit 1 en el puertoE es salida.
    TRISE2 = 0;//Indica que el bit 2 en el puertoE es salida.
    
    TRISB0=0;//Indica que el bit 0 en el puertoB es salida.
    TRISB1=0;//Indica que el bit 1 en el puertoB es salida.
    TRISB2=0;//Indica que el bit 2 en el puertoB es salida.
    
    
    LCD_Init();         /* initialize LCD16x2 */
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */    
    
    temp_val = 35;
    Hum_val=20;
    
    
    while (1) {
     
  
     //value_adc = ADC_Read(0);//humedad tierra
     //sprintf(value_humedad,"Hums%d",value_adc);
     DHT11_Start();                  /* send start pulse to DHT11 module */
    DHT11_CheckResponse();          /* wait for response from DHT11 module */
    
    /* read 40-bit data from DHT11 module */
    RH_Integral = DHT11_ReadData(); /* read Relative Humidity's integral value */
    RH_Decimal = DHT11_ReadData();  /* read Relative Humidity's decimal value */
    T_Integral = DHT11_ReadData();  /* read Temperature's integral value */
    T_Decimal = DHT11_ReadData();   /* read Relative Temperature's decimal value */
    
    temp_val = (unsigned char) T_Integral;/*toma el valor integral de temperatura y lo transforma en una caracter sin signo y este lo guarda en la variable "temp_value"
  */
    Hum_val=(unsigned char) RH_Integral;
    if (temp_val  > 26){
           Data_Out_led0_tem=1;//Si la temperatura es mayor a 26 grados enciende el led.
           Data_Out_led1_tem=0;//Led apagado
           Data_Out_led2_tem=0;//Led apagado
           __delay_ms(2000);
        }else{
            if(26 >= temp_val  && temp_val  >= 18){
           Data_Out_led0_tem=0;//Led apagado
           Data_Out_led1_tem=1;//Si la temperatura es menor a 26 grados y mayor a 18 grados enciende el led 
           Data_Out_led2_tem=0;//Led apagado
               __delay_ms(2000);
            }else{ 
                if(temp_val <18){
           Data_Out_led0_tem=0;//Led apagado
           Data_Out_led1_tem=0;//Led apagado
           Data_Out_led2_tem=1;//Si la temperatura es menor a 18 grados enciende el led 
                   __delay_ms(2000);
              
            }
        }
 if (Hum_val  > 75){
           Data_Out_led0_hum=1;//Si la humedad es mayor al 75% enciende el led.
           Data_Out_led1_hum=0;//Led apagado.
           Data_Out_led2_hum=0;//Led apagado.
           __delay_ms(2000);
        }else{
            if(75 >= Hum_val  && Hum_val  >= 70){
           Data_Out_led0_hum=0;//Led apagado.
           Data_Out_led1_hum=1;//Si la humedad es menor al 75%  y mayor al 70%  enciende el led. 
           Data_Out_led2_hum=0;//Led apagado.
               __delay_ms(2000);
            }else{ 
                if(Hum_val <70){
           Data_Out_led0_hum=0;//
           Data_Out_led1_hum=0;
           Data_Out_led2_hum=1;//Si la temperatura es menor al 70%  enciende el led.
                   __delay_ms(2000);
                }
            }
        }
    
    LCD_Clear(); /*Funcion que limpia lo que se presenta en el LCD*/
    sprintf(value,"T:%d",T_Integral);//Se encarga de convertir T_Integral al tipo de dato char.
    LCD_String_xy(1,0,value);//Indica la posicion donde se ubicara el dato en el LCD.
    sprintf(value,".%d",T_Decimal);//Se encarga de convertir T_Decimal al tipo de dato char.
    LCD_String(value);//Muestra el valor en el LCD.
    LCD_Char(0xdf);//Muestra el simbolo "°" en el LCD.
    LCD_Char('C');//Muestra el caracter C en el LCD.

    sprintf(value,"RH:%d",RH_Integral);//Se encarga de convertir RH_Integral al tipo de dato char.
    LCD_String_xy(2,0,value);//Indica la posicion donde se ubicara el dato en el LCD.
    sprintf(value,".%d ",RH_Decimal);//Se encarga de convertir RH_Decimal al tipo de dato char.
    LCD_String(value);//Muestra el valor en el LCD.
    LCD_Char('%');//Muestra el caracter '%' en el LCD.
    
    
}
}
}

/**
 * @brief DHT11_ReadData() Se encarga de leer los datos que recibe el sensor. 
 * @return retorna el dato de la temperatura y humedad al pic.
 */
char DHT11_ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(Data_In & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(Data_In & 1);
    }
  return data;
}
/**
 * @brief DHT11_Start() Se encarga de inicializar el sensor DTH11. 
 */
void DHT11_Start()
{    
    Data_Dir = 0;       /* set as output port */
    Data_Out = 0;       /* send low pulse of min. 18 ms width */ /*Mantiene la linea de datos en un estado bajo de 18 */
    __delay_ms(18);
    Data_Out = 1;       /* pull data bus high */
    __delay_us(20);
    Data_Dir = 1;       /* set as input port */    
//    LED = 14;
}
/**
 * @brief DHT11_CheckResponse() Es un protocolo que permite validar la llegada de los datos.  
 */


void DHT11_CheckResponse()
{
    while(Data_In & 1);     /* wait till bus is High */     
    while(!(Data_In & 1));  /* wait till bus is Low */
    while(Data_In & 1);     /* wait till bus is High */
}


