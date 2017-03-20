/*config ports*/
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "portInt.h"
#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"

void portInt(void){

    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 83;

    uint32_t period = 5000; //20ms (16Mhz / 64pwm_divider / 50)
    uint32_t duty = 4500;    //1.5ms pulse width
    /*configure motor pins
     * pA3,pa4 motor1 ina and inb
     * PB6 motor1 pwm
     * Pe4, Pe5 motor 2 ina and inb
     * pB7 motor2 pwm
     *
     * */
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//64);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
 //motor 1
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
    //GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    //GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_6);
   // GPIOPinConfigure(GPIO_PB6_M0PWM0);//PB6
    // motor 2

    //GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5);
    //GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);

    //GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_6|GPIO_PIN_7);

    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_0);
    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PD0_M1PWM0);//
    GPIOPinConfigure(GPIO_PD1_M1PWM1);//
    ui32PWMClock = SysCtlClockGet() / 64;
   // ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    /*pwm setup*/
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, period);

    //Set PWM duty
       PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,0);
       PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT ,true);
       PWMGenEnable(PWM1_BASE, PWM_GEN_0);
    /*encoder pins
     * pf4, pd7 motor1 encoders
     * pd6, pc7 motor2 encoders
     */

    //GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_RISING_EDGE);
    GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_RISING_EDGE);
    GPIOIntRegister(GPIO_PORTC_BASE,encoderHandler);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_6);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_7);


}

void encoderHandler(void){
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_6);
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_7);
    if(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6))
    {
        encoderLeft -= 1;
    }
    else{
        encoderRight += 1;
    }
}
