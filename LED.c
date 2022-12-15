//********************Información********************//
/*>Copyright (C) 2022 David Zavala
 *>Este es un programa de uso libre creado con fines totalmente
 *educativos.
 *>Este programa mantiene encendido el LED 1 y al presionar el
 *pushbutton del puerto P5.5 conmuta al LED 0.
 *>Para mayor información sobre la tarjeta de desarrollo consulta
 *el manual en https://www.ti.com/lit/ug/slau367p/slau367p.pdf
 */

//********************Librerias********************//
#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
//*************************************************//

int main(void){
//************Configuración de puertos*************//
    PM5CTL0 &= ~0x01; //Desactiva alta impedancia de todos los puertos pág
    P1DIR |= 0X03; // P0 y P1 OUTPUT LEDs internos de la tarjeta de desarrollo
    P5DIR &= ~0X20; //P5.5 INPUT Push Button interno
    P5REN |= 0X20; //P5.5 con resistencia interna
    P5OUT |= 0X20; //P5.5 resistencia débil interna tipo PullUp
//************************************************//

//**************Programa principal****************//
        while(1) {

            if (P5IN==0X00){ //Verifica si está presionado el PushButton
                P1OUT = 0x01; //Se enciende el LED 1
            }
            else{
                P1OUT = 0x02; //Se enciende el LED 2
            }
        }
}
//*****
