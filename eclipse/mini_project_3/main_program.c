/*
 ================================================================================================
 Name        : main_program.c
 Author      : Mohamed Elshafie
 Description : Fan control using LM35 temperature sensor
 Date        : Oct 8, 2021
 ================================================================================================
 */

#include <avr/io.h>
#include "std_types.h"
#include "common_macros.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "adc.h"

int main(void){
	/* make ADC work with internal ref voltage and prescalar F_CPU/8 */
	ADC_ConfigType ADC_config = {INT,div_by_8};

	DcMotor_Init();
	LCD_init();
	ADC_init(&ADC_config);

	uint8 temperature;

	LCD_displayString("Fan is ");
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =    C");

	while(1){
		/* get current temperature*/
		temperature = LM35_getTemperature();

		if(temperature < 30){
			DcMotor_Rotate(STOP, 0);
			LCD_moveCursor(0,7);
			LCD_displayString("OFF");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temperature);
			LCD_displayCharacter(' ');
		}
		else if(temperature >= 30 && temperature <60){
			DcMotor_Rotate(CW, 25);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,7);
			LCD_intgerToString(temperature);
		}
		else if(temperature >=60 && temperature <90){
			DcMotor_Rotate(CW, 50);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,7);
			LCD_intgerToString(temperature);
		}
		else if(temperature >=90 && temperature <120){
			DcMotor_Rotate(CW, 75);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,7);
			if(temperature >= 100)
					{
						LCD_intgerToString(temperature);
					}
					else
					{
						LCD_intgerToString(temperature);
						/* In case the digital value is two digits
						 * print space in the next digit place to clear it */
						LCD_displayCharacter(' ');
					}
		}
		else if(temperature >=120){
			DcMotor_Rotate(CW, 100);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,7);
			LCD_intgerToString(temperature);
		}
	}
}
