/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Moaz Mohamed
 *
 *******************************************************************************/

#include "keypad.h"
#include "gpio.h"

/*******************************************************************************
 *                     Static Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * This function adjusts the value of the pressed key on the keypad, to return the 
 * correct value of the pressed key.
 */
#ifndef STANDARD_KEYPAD
	#if (KEYPAD_NUM_COLS == 3)
		static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
	#elif (KEYPAD_NUM_COLS == 4)
		static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
	#endif
#endif /*STANDARD_KEYPAD*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void)
{
	/*set all rows  as input pins*/
	uint8 rows_counter=0,cols_counter=0;

	/*Each time setup the direction for all keypad port as input pins*/
	for(rows_counter=0;rows_counter<KEYPAD_NUM_ROWS;rows_counter++)
	{
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+rows_counter, PIN_INPUT);
	}

	/*set all columns as input pins in either (4x3, or 4x4) mode*/
	for(cols_counter=0;cols_counter<KEYPAD_NUM_COLS;cols_counter++)
	{
		GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+cols_counter, PIN_INPUT);
	}

	/*check pressed key logic*/
	while(1)
	{
		/* loop for rows */
		for(rows_counter=0;rows_counter<KEYPAD_NUM_ROWS;rows_counter++)
		{
			/*Setup the current row pin as output*/
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+rows_counter, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+rows_counter, KEYPAD_BUTTON_PRESSED);

			/* loop for columns */
			for(cols_counter=0;cols_counter<KEYPAD_NUM_COLS;cols_counter++)
			{
				/* Check if the switch is pressed in this column */
				if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+cols_counter)==KEYPAD_BUTTON_PRESSED)
				{

					#if (KEYPAD_NUM_COLS == 3)
						#ifdef STANDARD_KEYPAD
							return (rows_counter*KEYPAD_NUM_COLS+cols_counter+1);
						#else
							return KEYPAD_4x3_adjustKeyNumber(rows_counter*KEYPAD_NUM_COLS+cols_counter+1);
						#endif
					#elif (KEYPAD_NUM_COLS == 4)
						#ifdef STANDARD_KEYPAD
							return (rows_counter*KEYPAD_NUM_COLS+cols_counter+1);
						#else
							return KEYPAD_4x4_adjustKeyNumber(rows_counter*KEYPAD_NUM_COLS+cols_counter+1);
						#endif
					#endif
				}
			}
			/*return the row pin to be input again*/
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+rows_counter,PIN_INPUT);
		}
	}
}

/*
 * Description :
 * This function adjusts the value of the pressed key on the keypad, to return the 
 * correct value of the pressed key.
 */
#ifndef STANDARD_KEYPAD /*IF STANDARD_KEYPAD IS NOT DEFINED*/

#if (KEYPAD_NUM_COLS==3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button=0;
	switch(button_number)
	{
	case 10:
		keypad_button='*';
		break;
	case 11:
		keypad_button=0;
		break;
	case 12:
		keypad_button='#';
		break;
	default:
		keypad_button=button_number;
		break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COLS==4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button=0;
	switch (button_number)
	{
	case 1:
		keypad_button=7;
		break;
	case 2:
		keypad_button=8;
		break;
	case 3:
		keypad_button=9;
		break;
	case 4:
		keypad_button='/';
		break;
	case 5:
		keypad_button=4;
		break;
	case 6:
		keypad_button=5;
		break;
	case 7:
		keypad_button=6;
		break;
	case 8:
		keypad_button='x';
		break;
	case 9:
		keypad_button=1;
		break;
	case 10:
		keypad_button=2;
		break;
	case 11:
		keypad_button=3;
		break;
	case 12:
		keypad_button='-';
		break;
	case 13:
		keypad_button='C';
		break;
	case 14:
		keypad_button=0;
		break;
	case 15:
		keypad_button='=';
		break;
	case 16:
		keypad_button='+';
		break;
	default:
		keypad_button=button_number;
		break;
	}
	return keypad_button;

}
#endif /*Keypad mode (4x3,4x4)*/
#endif /*STANDARD_KEYPAD*/
