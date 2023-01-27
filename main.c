#include "lib/include.h"
/*
int main(void)
{
    //Experimento 1
  //Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
  //junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
  //cuya frecuencia sea de 10KHz  */
/*
    Configurar_PLL(_50MHZ);  //CONFIGURACION DE LA VELOCIDAD DEL RELOJ (LLAMA FUNCION PARA CONFIGURAR)
                             //PIN PB6 PARA PWM0
    Configura_Reg_PWM1(8);  //FUNCION PARA CONFIGURAR EL PWM 

    while (1)
    {
        
    }
      
}
*/

volatile uint8_t c_R; //VARIABLE DE MONITOREO 
volatile uint8_t c_A;
volatile uint8_t c_V;
uint8_t algo;
volatile uint16_t C;

uint16_t count;
int main(void)
{
    //Experimento 3
/* Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz, utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa  
 */

    Configurar_PLL(_20MHZ);  //CONFIGURACION DE LA VELOCIDAD DEL RELOJ (LLAMA FUNCION PARA CONFIGURAR)
    Configurar_UART0();//Yo FCLK 20MHZ Baudrate 57600 
    //Configura_Reg_ADC0();
    Configura_Reg_PWM3(8); //CONFIGURACION PARA EXPERIMENTO 3 
    
    // PARA DARLE UN VALOR A CADA COLOR DEL LED Y SABER CUAL SE ESTA MODIFICANDO  
    c_R = 82; 
    c_V = 86;
    c_A = 65;

     
    //a=4000;
    //b=16000;
    //c=5000; 
    

    while (1)
    {
        
        //PWM0->_0_CMPB = (int)(a*10000)/50; 
        //PWM0->_1_CMPA = (int)(b*10000)/50;
        //PWM0->_2_CMPA = (int)(c*10000)/50;
        
        C = readChar();
        
        switch (C)
        {
            case 'R':
                while (c_R == 82) //SELECCION DEL COLOR 
                {
                    c_R = (int)readChar(); 
                }
            
                PWM0->_0_CMPB = 20000-((int)(c_R*10000)/50); //PB7 (ROJO)
                c_R = 82;
            break;

            case 'G':
                while (c_V == 86)
                {
                    c_V = (int)readChar();
                }
                PWM0->_2_CMPA = 20000-((int)(c_V*10000)/50); //PE4 (VERDE)
                c_V = 86;
            break;

            case 'B':
                while (c_A == 65)
                {
                    c_A = (int)readChar();
                }

                PWM0->_1_CMPA = 20000-((int)(c_A*10000)/50); //PB4 (AZUL)
                c_A = 65;
            break;

            default:
                algo=1;
            break;
        }   
    }
}

