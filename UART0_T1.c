//********************Información********************//
/*>Copyright (C) 2022 David Zavala
 *>Este es un programa de uso libre creado con fines totalmente
 *educativos.
 *>Este programa envía constantemente la palabra "Hola desde MSP430"
 *a la terminal de la computadora con un Baudrate de 115200 bps.
 *>Para mayor información sobre la tarjeta de desarrollo consulta
 *el manual en https://www.ti.com/lit/ug/slau367p/slau367p.pdf
 */
//*********************************Librerias**********************************************//
#include <msp430.h>
#include <stdint.h>
#include <string.h>
//****************************************************************************************//
#define SIZE_MSG 20
void UART0_CFG();
void GPIOs_CFG();
void send_msg(char msg[]);

//******************************Programa principal***************************************//
int main(void)
{
    UART0_CFG();
    GPIOs_CFG();
    char Msg[SIZE_MSG]= "Hola desde MSP430\n\r";

    while(1){
        send_msg(Msg);
    }
}

//************Configuración del UART 0 para comunicarse con la terminal (USB) *************//
   void UART0_CFG(){
       UCA0CTLW0 |= UCSWRST;                       //Pone a A0 en software reset
       UCA0CTLW0 |= UCSSEL__SMCLK;                 //Configura reloj igual a 1 SMCLK= 1 MGHZ
       //Se busca llegar a una frecuencia de 115200 bauds por segundo
       UCA0BRW = 8;                                //Prescalador entero entre 8
       UCA0MCTLW=0XD600;                           //Prescalador fraccionario

   }
//****************************************************************************************//
//*****************************Configuracion de Puertos**********************************//
   void GPIOs_CFG(){
       P2SEL1 |= 0x02;                         //Configura al pin 2.1 como receptor UART
       P2SEL0 &= ~0x02;                        //Pag 93 datasheet
       P2SEL1 |= 0x01;                         //Configura al pin 2.0 como transmisor UART
       P2SEL0 &= ~0x01;                        //Pag 93 datasheet
       PM5CTL0 &= ~LOCKLPM5;                   //Desactiva alta impedancia
       UCA0CTLW0 &= ~UCSWRST;                  //Quita de A0 el software reset
   }
//****************************************************************************************//
   //********************************** Envía mensaje ************************************//
void send_msg(char msg[]){
   int i=0;
   while(i<SIZE_MSG){
       while(UCA0STATW & 0x01);
           UCA0TXBUF = msg[i];
           i++;
   }i=0;
}
//****************************************************************************************//
