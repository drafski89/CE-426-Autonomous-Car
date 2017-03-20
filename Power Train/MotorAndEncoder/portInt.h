/*
 * portInt.h
 *
 *  Created on: Mar 14, 2017
 *      Author: jacob
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"

#ifndef PORTINT_H_
#define PORTINT_H_

int encoderRight;
int encoderLeft;
void portInt(void);
void encoderHandler(void);



#endif /* PORTINT_H_ */
