/*
 * main.c
 */
#include "portInt.h"

int main(void) {
	
	portInt();
    uint32_t duty = 4500;    //1.5ms pulse width
	//digitalWrite(INA_1,HIGH);
	//digitalWrite(INB_1,LOW);
	//analogWrite(PWM_1,255);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
	//PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,duty);
	while(1)
	{
	    //GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
	    //GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
	    SysCtlDelay(100000);
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,duty);
	    //int i = 0;

	    SysCtlDelay(100000);
	    PWMGenDisable(PWM1_BASE, PWM_GEN_0);
	    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
	    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
	    PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	    /*
	    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
	    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
	    SysCtlDelay(100000);
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,duty);
	    SysCtlDelay(100000);
	    */

	}
}
