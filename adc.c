/*
 * File:   adc.c
 * Author: Logicos
 *
 * Created on 26 de enero de 2023, 10:20 AM
 */

#include "adc.h"
#include <xc.h>


void ADC_Init()
{    
    TRISA0 = 1;
    ANSEL = 0x01; //  Configura el Puerto como Entrada Analógica.
    
    ADCON1bits.ADFM = 1; //  Justificación Derecha (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0;
    ADRESH=0;		/* Flush ADC output Register */
    ADRESL=0;   
}   

int ADC_Read(int channel)
{
    int digital;

    /* Channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000) & ADC is disabled */
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);  
    
    ADCON0 |= ((1<<ADON)|(1<<GO));	/*Enable ADC and start conversion*/

    /* Wait for End of conversion i.e. Go/done'=0 conversion completed */
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH << 8) + ADRESL;	/*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}

