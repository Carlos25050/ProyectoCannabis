/* 
 * File:   adc.h
 * Author: Logicos
 *
 * Created on 26 de enero de 2023, 09:55 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

/** @brief ADC_Init inicializa el conversor
 * @param void
 */
void ADC_Init(void);

/**  @brief ADC_Read Convierte en digital lo que lee en la entrada.
 * @param Channel Canal de entrada y salida del sensor.
 * @return El valor convertido entre 0 y 1023.
 */
int ADC_Read(int channel);
    


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

