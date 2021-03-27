/*
 * display.h
 *
 *  Created on: Dec 19, 2020
 *      author:MEHMET AKİF GÜMÜŞ-171024027
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "bsp.h"

typedef struct{
	uint8_t Digits[4];

}SSD;

/*
 * Display struct keep the digits and
 * overflow, sign, dot, invalid bits
 */
SSD Display;

/*
 * initiation for keypad pins
 */
void init_SSD();

/*
 * This function ensures that the digits on the display
 * are lit by quickly flashing the digits.
 */
void display_SSD();

/*
 * the cases which are inside of this func show that
 * how to display the character
 */
void printDigit_SSD(uint8_t);

//void displayID_SSD();


/*
 * separates the incoming result into digit
 * and we can see that if number is negative or
 * not through sign bit
 */
void utility_SSD(float var);


#endif /* DISPLAY_H_ */
