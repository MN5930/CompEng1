// Weather staion kit design written in C for Sam3x Microcontroller
// Written by Nazari

#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Libraries\X_LED.h"
#include "Libraries\X_COMMON.h"
#include "Libraries\X_FUNCTIONS.h"
#include "Libraries\X_LCD.h"
#include "Libraries\X_PRESSURE.h"
#include "Libraries\X_TEMP.h"
#include "Libraries\X_KEYPAD.h"
#include "Libraries\X_BUTTON.h"
#include "Libraries\X_RTC.h"
#include <stdlib.h>

float calculateAverage(float * data);

char status = 0;//current system status
char status_changed = 0;//if status has changed

char isInput = 0;//if we are reading keypad

char inputFinished = 0;//if finished the input for this time

int key[2];//key value cache for saving 2 recently inputted keys 

int key_value;//final input key value

float tPressureData[10]; //temporary pressure data
float tTemperatureData[10];//temporary temperature data

Entity * header, * tail; //header and tail for link list

char isRecord = 0; //if one data has been recorded.

void main(void)
{ 
	//initialization
	SystemInit();
	//turn off the LED
	keyLedOff();
	initial_RTC();
	initial_LCD();
	//print the main menu
	print_main_2_lcd();
	//initial the key value cache
	key[0] = -1;
	key[1] = -1;
	//initial link list
	header = tail = NULL;
	//request temp value
	request_temp();
	while(1)
	{
		//clear LCD if status has been changed.
		if(status_changed)
		{
			clear_txt_LCD();
			clear_graph_LCD();
			status_changed = 0;
		}

		//print corresponding screen
		switch(status)
		{
		case 0:
			isTest = 0;//cancel test mode
			print_main_2_lcd();
			break;
		case 1:
			print_Normal_main_2_lcd();
			break;
		case 2:
			print_Fast_main_2_lcd();
			break;
		case 3:
			printPressure_LCD_Week();
			break;
		case 4:
			printTemp_LCD_Week();
			break;
		case 5:
			print_temp_Pressure_LCD_Week_txt();
			break;
		case 6:
			Sun_direction((int)trackSun());
			break;
		case 7:        
			print_simulation_menu();
			break;
		case 10:        
			printSystemTest();
			break;
		}
		//check if we need readKeypad
		if(getButtonValue() || isInput)
		{
			isInput = 1;
			keyLedOn();
		}
		//readKeypad
		if(isInput)
		{
			int tmp;
			if(key[0] == -1)
			{
				read_keyboard(&key[0]);
				tmp = key[0];
			}else if(key[1] == -1)
			{
				read_keyboard(&key[1]);
				tmp = key[1];
			}else
			{        
				read_keyboard(&tmp);
				if(tmp != 12)
				{
					key[0] = key[1];
					key[1] = tmp;
				}
			}      
			//12(#) means input end
			if(tmp == 12)
			{
				isInput = 0;
				inputFinished = 1;
				if(key[0] == 12)
					key_value = 0;//0 means just # be pushed
				else if(key[1] == 12)
					key_value = key[0];
				else if(status != 1)
					key_value = key[1];//read last inputted key if status is not in normal mode to setting
				else if(key[0] == 1 && key[1] == 11)
					key_value = 10;
				else 
					key_value = -1;
				key[0] = -1;
				key[1] = -1;
			}
		}

		if(inputFinished)
		{
			keyLedOff();
			switch(status)
			{
			case 0:
				{
					if((key_value >= 1 && key_value <= 7)||key_value == 10)
					{
						status = key_value;
						status_changed = 1;
					}
				}
				break;
			case 1:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}else if(key_value >= 1 && key_value <= 10)//setting record times per minute
					{
						range = key_value;
						secondCounter = 0;
					}
				}
				break;
			case 2:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}
				}
				break;
			case 3:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}
				}
				break;
			case 4:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}
				}
				break;
			case 5:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}
				}
				break;
			case 6:
				{
					if(key_value == 0)
					{
						status = 0;
						status_changed = 1;
					}
				}
				break;
			case 7: 
				{
					//start test mode
					isTest = 1;
					switch(key_value)
					{
					case 0:
						{
							status = 0;
							status_changed = 1;
						}
						break;   
					case 1:
						{
							status = 5;
							status_changed = 1;
						}
						break;
					case 2:
						{
							status = 3;
							status_changed = 1;
						}
						break;
					case 3:
						{
							status = 4;
							status_changed = 1;
						}
						break;
					}
				}
				break;
			case 10:
			  {
				if(key_value == 0)
				{
					status = 0;
					status_changed = 1;
				}
			  }
			  break;
			}
			inputFinished = 0;
		}    
		float temporary;//temporary value for saving data
		temporary = getPressure();
		if(temporary != -1)
			pressure = temporary;

		if(temp_ready)
		{
			temporary = get_temp();
			if(temporary != -1)
				temperature = temporary;
			request_temp();
		}
		//temperature alarm
		if(temporary >= 35 || temporary <= 0)
			alarmLedOn();
		else
			alarmLedOff();
		//update real time clock time
		getRTCStatus();
		//one second is passed
		if(isSecond)
		{
			isSecond = 0;
			if(status != 2)
			{
				//record data and calculate average value when system is not in fast mode
				secondCounter ++;
				if(secondCounter >= 60)
				{
					tPressureData[range - 1] = pressure;
					tTemperatureData[range - 1] = temperature;
					avgTemperature = calculateAverage(tTemperatureData);
					avgPressure = calculateAverage(tPressureData);
					isRecord = 1;
					secondCounter = 0;
				}else if(secondCounter % (60 / range) == 0)
				{
					tPressureData[secondCounter / (60 / range) - 1] = pressure;
					tTemperatureData[secondCounter / (60 / range) - 1] = temperature;
				}
			}else
			{
				isRecord = 1;   
				secondCounter = 0;
			}

			if(isRecord)
			{
				//recording data
				isRecord = 0;        
				timeCounter++;
				Entity * tmp;
				if(status == 2)
					tmp = createEntity(temperature, pressure, recordDate >= 7 ? 6:recordDate);
				else
					tmp = createEntity(avgTemperature, avgPressure, recordDate >= 7 ? 6:recordDate);
				while(tmp == NULL)
				{
					//delete first day's data in the link list when the memory is runned out
					header = deleteFirstDay(header);
					if(status == 2)
						tmp = createEntity(temperature, pressure, recordDate >= 7 ? 6:recordDate);
					else
						tmp = createEntity(avgTemperature, avgPressure, recordDate >= 7 ? 6:recordDate);
				}				
				//record data
				if(header == NULL)
				{
					header = tail = tmp;
				}else
				{
					tail->next = tmp;
					tail = tmp;
				}
				//update average, minimal, maximal data
				updateData(tmp, timeCounter);
				//(timeCounter == 24)//for test
				if(timeCounter == 1439)
				{
					recordDate++;
					timeCounter = 0;
					if(recordDate >= 7)
					{
						//delete first day's data when we already have 7 days' data
						int ii;
						for(ii = 0; ii < 6; ii++)
						{
							pressureData[ii][0] = pressureData[ii + 1][0];
							pressureData[ii][1] = pressureData[ii + 1][1];
							pressureData[ii][2] = pressureData[ii + 1][2];
							temperatureData[ii][0] = temperatureData[ii + 1][0];
							temperatureData[ii][1] = temperatureData[ii + 1][1];
							temperatureData[ii][2] = temperatureData[ii + 1][2];
						}
						for(ii = 0; ii < 3; ii++)
						{
							pressureData[6][ii] = 0;
							temperatureData[6][ii] = 0;
						}
						header = deleteDate(header, 0);
						decreaseDate(header);
					}
				}
			}
		} 

	}//while end
}//main end

float calculateAverage(float * data)
{
	float tmp = 0;
	int ii;
	for(ii = 0; ii < range; ii++)
	{
		tmp += data[ii];
	}
	return tmp / range;
}
