/*!
\file   LCD.h
\date   2022-06-08
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  Functions Handler LCD 16x2 mode 4 bits.

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


#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

   
#define RS PORTDbits.RD0  /*PIN 0 of PORTD is assigned for register select Pin of LCD*/
#define EN PORTDbits.RD1  /*PIN 1 of PORTD is assigned for enable Pin of LCD */
#define ldata PORTD  /*PORTD(PD4-PD7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD  /*define macros for PORTD Direction Register*/
    
/**  @brief LCD_Init iniciliza el LCD
 * @param void
 */    
void LCD_Init(void);       
/**  @brief  LCD_Command Envia datos al puerto del pic como comando al LCD
 * @param Recibe un dato tipo char
 */   
void LCD_Command(unsigned char ); /*Send command to LCD*/

/**
 * @brief LCD_Char Enviar y registrar datos en el LCD
 * @param x Recibe un dato de tipo char
 */
void LCD_Char(unsigned char x);    /*Send data to LCD*/

/**
 * @brief LCD_String para imprimir en el LCD
 * @param recibe el mensaje de tipo char
 */
void LCD_String(const char *);     /*Display data string on LCD*/
/**
 * @brief LCD_String_xy imprime el mensaje en la 1er y 2da linea
 * @param Recibe la ubicacion y el valor de tipo char
 */  
void LCD_String_xy(char, char , const char *);

/** @brief LCD_Clear limpia el LCD.
 * @param void

 */   
void LCD_Clear(void);                  /*Clear LCD Screen*/


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

