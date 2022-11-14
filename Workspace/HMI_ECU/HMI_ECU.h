/******************************************************************************
 *
 * Module: HMI ECU
 *
 * File Name: HMI_ECU.h
 *
 * Description: Header file for the HMI ECU.
 *
 * Author: Moaz Mohamed
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define PASSWORD_LIMIT 6
#define F_CPU		   1000000UL

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	PASSWORD_FAILED,PASSWORD_PASSED,THIEF
}Password_Status;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * This function display a prompt to the user to enter the password whether to save it or to store it in EEPROM.
 */
void enterPass(uint8* pass,boolean isFirst);

/*
 * Description :
 * This function display the main options on the LCD, and takes input from the user then return that input.
 */
uint8 displayAndChooseOptions(void);

/*
 * Description :
 * This is the callBack Function that'll be called when an interrupt request is generated
 * by Timer1.
 */
void callBack(void);

#endif /* HMI_ECU_H_ */
