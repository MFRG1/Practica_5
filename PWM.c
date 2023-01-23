#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    /*Se habilita modulo PWM0 pag 354*/
    SYSCTL->RCGCPWM |= (1<<0);
    
    /*Habilita GPIO Puerto B pag 340 y pag. 1233 
    SYSCTL->RCGCGPIO |= (1<<1);
    
    /*Habialitar o desabilitar Divisor  Pag 254    frec, tarjeta / frec PWM = cuentas */
    SYSCTL->RCC &= ~(1<<20); //Cabe en los 16 bits del PWMs  
    
    /*Se habilita la función alternativa para PB4 Pag 672*/
    GPIOB->AFSEL |= (1<<4);

    //Se indica como salida 
    GPIOB->DIR = (1<<4); 

    /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; 
    
    /* para decirle si es digital o no Pag 682*/
    GPIOB->DEN |= (1<<4); 
    
    // Se desactiva generador acorde a tabla 1233 para saber con que gen. se trabaja
    PWM0->_1_CTL = (0<<0); //se le asigna 0 a 0 porque es el bit para indicar lo habilitado o desabilitado según pag. 1266
    
    // Modo de configuración - modo regresivo pag. 1285, pag. 1239 para saber que valor poner, y 1248 comparador para el PWM a usar 
    PWM0->_1_GENA = 0x0000008C; 
    
    // Configuración de cargas: cuentas=fclk/fpwm  para 50MHz cuentas = (50,000,000/10,000)
    PWM0->_1_LOAD = 5000;  
    PWM0->_1_CMPA = 2250;  //ciclo de trabajo
    
    //Habilitar generadores a usar
    PWM0->_1_CTL = (1<<0);
    
    //Se habilita el PWM que se usa pag. 1247 y 1233
    PWM0->ENABLE = (1<<2); 
}
