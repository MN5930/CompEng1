#include "X_LCD.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_RTC.h"
#include "X_ENTITY.h"
#include "X_COMMON.h"

#include "..\at91sam3x8.h"

int pressureData[7][3] = {0}; //pressure data 0:avg 1:minimal 2:maximal
float temperatureData[7][3] = {0}; //temperature data 0:avg 1:minimal 2:maximal
int fixedPressureData[7][3];//pre-record data 0:avg 1:minimal 2:maximal
float fixedTemperatureData[7][3];//pre-record data 0:avg 1:minimal 2:maximal

float pressure, temperature;//save the current value
float avgPressure, avgTemperature; // save the average value for normal mode
char range = 1;//1 - 10 times per minute for normal mode

int recordDate = 0; //the day 0~6
int timeCounter = 0; // count the minute of one day 0~1439
int secondCounter = 0;//count second in normal mode
char isTest = 0;//0 means in normal mode, 1 means in test mode

void Init_Display(void);
unsigned char Read_Status_Display(void);
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void initial_LCD();
void simulation();

void printTemp_LCD_Week()
{
	moveTextPointer(0, 15);

	printLetter(' ');
	printLetter(' ');
	printLetter(' ');
	printLetter(' ');

	//write monday
	printLetter('M');//M
	printLetter('O');//o
	printLetter('N');//n

	printLetter(' ');
	printLetter(' ');

	printLetter('T');//T
	printLetter('U');//u
	printLetter('E');//e


	printLetter(' ');
	printLetter(' ');

	printLetter('W');//W
	printLetter('E');//E
	printLetter('D');//d

	printLetter(' ');
	printLetter(' ');

	printLetter('T');//T
	printLetter('H');//h
	printLetter('U');//u

	printLetter(' ');
	printLetter(' ');

	printLetter('F');//F
	printLetter('R');//r
	printLetter('I');//i

	printLetter(' ');
	printLetter(' ');

	printLetter('S');//S
	printLetter('A');//a
	printLetter('T');//t

	printLetter(' ');
	printLetter(' ');

	printLetter('S');//S
	printLetter('U');//u
	printLetter('N');//n

	moveTextPointer(0, 14);
	//moveGraghPointer(0, 115);
	int ii = 0;
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	moveTextPointer(0, 13);
	printLetter(' ');
	printLetter(' ');
	printLetter('0');
	moveGraghPointer(3, 111);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveGraghPointer(3, 87);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(0, 7);
	printLetter(' ');
	printLetter('5');
	printLetter('0');
	moveGraghPointer(3, 62);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveGraghPointer(3, 37);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(0, 1);
	printLetter('1');
	printLetter('0');
	printLetter('0');
	moveGraghPointer(3, 12);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(8, 0);
	printLetter('T');
	printLetter('e');
	printLetter('m');
	printLetter('p');
	printLetter(' ');
	printLetter('[');
	printLetter('A');
	printLetter('v');
	printLetter('g');
	printLetter(',');
	printLetter('M');
	printLetter('a');
	printLetter('x');
	printLetter(',');
	printLetter('M');
	printLetter('i');
	printLetter('n');
	printLetter(']');

	int jj;
	//draw data bar graph
	for(ii = 0; ii < 7; ii++)
		for(jj = 0; jj < 3; jj++)
		{
			if(isTest)
				printLine(ii, jj, fixedTemperatureData[ii][jj]);
			else
				printLine(ii, jj, temperatureData[ii][jj]);
		}

}

void printPressure_LCD_Week()
{
	moveTextPointer(0, 15);

	printLetter(' ');
	printLetter(' ');
	printLetter(' ');
	printLetter(' ');

	//write monday
	printLetter('M');//M
	printLetter('O');//o
	printLetter('N');//n

	printLetter(' ');
	printLetter(' ');

	printLetter('T');//T
	printLetter('U');//u
	printLetter('E');//e


	printLetter(' ');
	printLetter(' ');

	printLetter('W');//W
	printLetter('E');//E
	printLetter('D');//d

	printLetter(' ');
	printLetter(' ');

	printLetter('T');//T
	printLetter('H');//h
	printLetter('U');//u

	printLetter(' ');
	printLetter(' ');

	printLetter('F');//F
	printLetter('R');//r
	printLetter('I');//i

	printLetter(' ');
	printLetter(' ');

	printLetter('S');//S
	printLetter('A');//a
	printLetter('T');//t

	printLetter(' ');
	printLetter(' ');

	printLetter('S');//S
	printLetter('U');//u
	printLetter('N');//n

	moveTextPointer(0, 14);

	int ii = 0;
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	moveTextPointer(0, 13);
	printLetter(' ');
	printLetter('9');
	printLetter('7');
	moveGraghPointer(3, 111);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveGraghPointer(3, 87);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(0, 7);
	printLetter('1');
	printLetter('0');
	printLetter('1');
	moveGraghPointer(3, 62);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveGraghPointer(3, 37);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(0, 1);
	printLetter('1');
	printLetter('0');
	printLetter('3');
	moveGraghPointer(3, 12);
	printPixel(0x07);
	for(ii = 0; ii < 34; ii++)
	{
		printPixel(0x24);
	}

	moveTextPointer(8, 0);
	printLetter('P');
	printLetter('r');
	printLetter('e');
	printLetter('s');
	printLetter('s');
	printLetter('u');
	printLetter('r');
	printLetter('e');
	printLetter(' ');
	printLetter('[');
	printLetter('A');
	printLetter('v');
	printLetter('g');
	printLetter(',');
	printLetter('M');
	printLetter('a');
	printLetter('x');
	printLetter(',');
	printLetter('M');
	printLetter('i');
	printLetter('n');
	printLetter(']');

	int jj;
	//draw data bar graph
	for(ii = 0; ii < 7; ii++)
		for(jj = 0; jj < 3; jj++)
		{
			if(isTest)
			{
				if(fixedPressureData[ii][jj] - 9700 >= 0)
					printLine(ii, jj, (fixedPressureData[ii][jj] - 9700) / 6);        
			}
			else
			{
				if(pressureData[ii][jj] - 97000 >= 0)
					printLine(ii, jj, (pressureData[ii][jj] - 97000) / 60);        
			}
		}
}

void moveTextPointer(unsigned char column, unsigned char row)
{
	if(column < 40 && row < 16)
	{
		int tmp = 40 * row + column;
		moveAP(tmp & 0xFF, (tmp & 0xFF00) >> 8);
	}
}

void moveGraghPointer(unsigned char column, unsigned char row)
{
	if(column < 40 && row < 128)
	{
		int tmp = 40 * row + column;
		moveAP(tmp & 0xFF, ((tmp & 0xFF00) >> 8) + 0x40);
	}
}

void printPixel(char c)
{
	Write_Data_2_Display(c);
	Write_Command_2_Display(0xC0);
}

void printLetter(char c)
{
	if(c < 32 || c > 159)
		return;
	Write_Data_2_Display(c - 32);
	Write_Command_2_Display(0xC0);
}

void moveAP(char l, char h)
{
	Write_Data_2_Display(l);
	Write_Data_2_Display(h);
	Write_Command_2_Display(0x24);
}

void printLine(char day, char line, char value)
{
	int ii;
	for(ii = 0; ii < value; ii++)
	{
		moveGraghPointer(4 + 5 * day + line, 111 - ii);
		printPixel(0x1C);
	}
}

void printTemp2L()
{  
	printLine(0, 0, 25);
	printLine(0, 1, 50);
	printLine(0, 2, 75);

	printLine(3, 1, 25);

	printLine(6, 2, 77);
}

void initial_LCD()
{
	enableClock(PIOC_PIID);
	enableClock(PIOD_PIID);

	enablePin(PIOD_PIOS, 0);
	disablePullUp(PIOD_PIOS, 0);
	enableOutput(PIOD_PIOS, 0);

	enablePin(PIOC_PIOS, 2);
	enablePin(PIOC_PIOS, 3);
	enablePin(PIOC_PIOS, 4);
	enablePin(PIOC_PIOS, 5);
	enablePin(PIOC_PIOS, 6);
	enablePin(PIOC_PIOS, 7);
	enablePin(PIOC_PIOS, 8);
	enablePin(PIOC_PIOS, 9);
	enablePin(PIOC_PIOS, 12);
	enablePin(PIOC_PIOS, 13);
	enablePin(PIOC_PIOS, 14);
	enablePin(PIOC_PIOS, 15);
	enablePin(PIOC_PIOS, 16);
	enablePin(PIOC_PIOS, 17);
	enablePin(PIOC_PIOS, 18);
	enablePin(PIOC_PIOS, 19);

	disablePullUp(PIOC_PIOS, 12);
	disablePullUp(PIOC_PIOS, 13);
	disablePullUp(PIOC_PIOS, 14);
	disablePullUp(PIOC_PIOS, 15);
	disablePullUp(PIOC_PIOS, 16);
	disablePullUp(PIOC_PIOS, 17);
	enableOutput(PIOC_PIOS, 12);
	enableOutput(PIOC_PIOS, 13);
	enableOutput(PIOC_PIOS, 14);
	enableOutput(PIOC_PIOS, 15);
	enableOutput(PIOC_PIOS, 16);
	enableOutput(PIOC_PIOS, 17);

	disablePullUp(PIOC_PIOS, 2);
	disablePullUp(PIOC_PIOS, 3);
	disablePullUp(PIOC_PIOS, 4);
	disablePullUp(PIOC_PIOS, 5);
	disablePullUp(PIOC_PIOS, 6);
	disablePullUp(PIOC_PIOS, 7);
	disablePullUp(PIOC_PIOS, 8);
	disablePullUp(PIOC_PIOS, 9);

	Init_Display();

	simulation();
}

void Init_Display(void)
{
	clearPin(PIOD_PIOS, 0); //clear reset display
	Delay(10000);
	setPin(PIOD_PIOS, 0);//set reset display

	Write_Data_2_Display(0x00);
	Write_Data_2_Display(0x00);
	Write_Command_2_Display(0x40);//Set text home address
	Write_Data_2_Display(0x28);
	Write_Data_2_Display(0x00);
	Write_Command_2_Display(0x41); // Set text area

	Write_Data_2_Display(0x00);
	Write_Data_2_Display(0x40);
	Write_Command_2_Display(0x42); //Set graphic home address  
	Write_Data_2_Display(0x28);
	Write_Data_2_Display(0x00);
	Write_Command_2_Display(0x43); // Set graphic area

	Write_Command_2_Display(0x80); // text mode
	Write_Command_2_Display(0x9C); // Text on graphic off

	moveTextPointer(0, 0);

	//clear screen
	int i;
	for(i = 0; i < 640; i++)
	{
		printLetter(' ');
	}
	moveGraghPointer(0, 0);
	for(i = 0; i < 5120; i++)
	{
		printPixel(0x00);
	}
}

unsigned char Read_Status_Display(void)
{
	unsigned char Temp =0 ;

	//make databus as input 
	disableOutput(PIOC_PIOS, 2);
	disableOutput(PIOC_PIOS, 3);
	disableOutput(PIOC_PIOS, 4);
	disableOutput(PIOC_PIOS, 5);
	disableOutput(PIOC_PIOS, 6);
	disableOutput(PIOC_PIOS, 7);
	disableOutput(PIOC_PIOS, 8);
	disableOutput(PIOC_PIOS, 9);    

	setPin(PIOC_PIOS, 13);//set dir to 1 for 74chip, input
	clearPin(PIOC_PIOS, 12);//enable output 74chip
	setPin(PIOC_PIOS, 17);//set C/D to 1
	clearPin(PIOC_PIOS, 16);//clear CS
	clearPin(PIOC_PIOS, 15);//clear RD

	Delay(20);
	int t = (*AT91C_PIOC_PDSR )& 0x3FC;
	Temp = t>>2; 

	setPin(PIOC_PIOS, 16);//set CS
	setPin(PIOC_PIOS, 15);  //set RD
	setPin(PIOC_PIOS, 12);//disable output 74chip
	clearPin(PIOC_PIOS, 13);  //clear dir to 0 for 74chip, output
	return Temp;
}


void Write_Command_2_Display(unsigned char Command)
{
	while((Read_Status_Display()&0x3) != 0x3)
	{

	}  
	unsigned int x = 0;
	x = Command;
	x = x<<2;
	//clear databus
	clearPin(PIOC_PIOS, 2);
	clearPin(PIOC_PIOS, 3);
	clearPin(PIOC_PIOS, 4);
	clearPin(PIOC_PIOS, 5);
	clearPin(PIOC_PIOS, 6);
	clearPin(PIOC_PIOS, 7);
	clearPin(PIOC_PIOS, 8);
	clearPin(PIOC_PIOS, 9);   
	//set command to databus
	*AT91C_PIOC_SODR = x;
	clearPin(PIOC_PIOS, 13);//clear dir to 0 for 74chip, output
	clearPin(PIOC_PIOS, 12);//enable output 74chip
	//set databus as output
	enableOutput(PIOC_PIOS, 2);
	enableOutput(PIOC_PIOS, 3);
	enableOutput(PIOC_PIOS, 4);
	enableOutput(PIOC_PIOS, 5);
	enableOutput(PIOC_PIOS, 6);
	enableOutput(PIOC_PIOS, 7);
	enableOutput(PIOC_PIOS, 8);
	enableOutput(PIOC_PIOS, 9); 

	setPin(PIOC_PIOS, 17);//set C/D to 1
	clearPin(PIOC_PIOS, 16);//clear CS
	clearPin(PIOC_PIOS, 14);//clear WR
	Delay(20);
	setPin(PIOC_PIOS, 16);//set CS
	setPin(PIOC_PIOS, 14);//set WR  
	setPin(PIOC_PIOS, 12);//disable output 74chip  
	//clear databus as input 
	disableOutput(PIOC_PIOS, 2);
	disableOutput(PIOC_PIOS, 3);
	disableOutput(PIOC_PIOS, 4);
	disableOutput(PIOC_PIOS, 5);
	disableOutput(PIOC_PIOS, 6);
	disableOutput(PIOC_PIOS, 7);
	disableOutput(PIOC_PIOS, 8);
	disableOutput(PIOC_PIOS, 9);  
}

void Write_Data_2_Display(unsigned char Data)
{
	while((Read_Status_Display()&0x3) != 0x3)
	{

	}
	unsigned int x = 0 ;
	x = Data;
	x = x<<2;
	//clear databus
	clearPin(PIOC_PIOS, 2);
	clearPin(PIOC_PIOS, 3);
	clearPin(PIOC_PIOS, 4);
	clearPin(PIOC_PIOS, 5);
	clearPin(PIOC_PIOS, 6);
	clearPin(PIOC_PIOS, 7);
	clearPin(PIOC_PIOS, 8);
	clearPin(PIOC_PIOS, 9);  
	//set Data to databus
	*AT91C_PIOC_SODR = x;
	clearPin(PIOC_PIOS, 13);//clear dir to 0 for 74chip, output
	clearPin(PIOC_PIOS, 12);//enable output 74chip
	//set databus as output
	enableOutput(PIOC_PIOS, 2);
	enableOutput(PIOC_PIOS, 3);
	enableOutput(PIOC_PIOS, 4);
	enableOutput(PIOC_PIOS, 5);
	enableOutput(PIOC_PIOS, 6);
	enableOutput(PIOC_PIOS, 7);
	enableOutput(PIOC_PIOS, 8);
	enableOutput(PIOC_PIOS, 9); 

	clearPin(PIOC_PIOS, 17);//clear C/D
	clearPin(PIOC_PIOS, 16);//clear CS 
	clearPin(PIOC_PIOS, 14);//clear WR
	Delay(20);
	setPin(PIOC_PIOS, 16);//set CS
	setPin(PIOC_PIOS, 14);//set WR 
	setPin(PIOC_PIOS, 12);//disable output 74chip
	//set databus as input  
	disableOutput(PIOC_PIOS, 2);
	disableOutput(PIOC_PIOS, 3);
	disableOutput(PIOC_PIOS, 4);
	disableOutput(PIOC_PIOS, 5);
	disableOutput(PIOC_PIOS, 6);
	disableOutput(PIOC_PIOS, 7);
	disableOutput(PIOC_PIOS, 8);
	disableOutput(PIOC_PIOS, 9); 
}


///////////////////////Print Main Menu 2 LCD ///////////////////////////

void print_word_2_lcd(char *word,char col,char row){
	if ((row>=0)&& (col>=0)) 
		moveTextPointer(col, row);
	while (*word != '\0'){
		printLetter(*word);
		word++;
	}

}

//////////////////////////Print the main menu to the LCD ///////////////////////
void print_main_2_lcd(){
	int ii;
	print_word_2_lcd("Computer Engineering",10,0);
	moveGraghPointer(0,7); for(ii = 0; ii < 40; ii++) {   printPixel(0x3F);  }
	print_word_2_lcd("Press Red Button menu Number then #",0,1);
	moveGraghPointer(2,21); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("1#.Normal Mode",2,3);
	moveGraghPointer(2,37); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("2#.Fast Mode",20,3);
	moveGraghPointer(2,53); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("3#.Pressure GRAPH  ",2,5);
	moveGraghPointer(2,69); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("4#.Tempreture GRAPH ",2,7);
	moveGraghPointer(2,85); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("5#.Pressure and Tempreture in TXT ",2,9);
	moveGraghPointer(2,101); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("6#.Current Sun Direction ",2,11);
	moveGraghPointer(2,117); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("7#.Simulation",2,13); 
	print_word_2_lcd("*#.System Test",2,15); 
}

//////////////////////////// Prin the Fast mode to LCD /////////////////////////
void print_Fast_main_2_lcd(){
	print_word_2_lcd("Fast Mode",15,0);
	print_word_2_lcd("Date : ",2,2);
	//getTime();
	switch((recordDate % 7) + 1)
	{
	case 1 : print_word_2_lcd("Monday:",-1,-1);break;
	case 2 : print_word_2_lcd("Tuesday:",-1,-1);break;
	case 3 : print_word_2_lcd("Wednesday:",-1,-1);break;
	case 4 : print_word_2_lcd("Thursday:",-1,-1);break;
	case 5 : print_word_2_lcd("Friday:",-1,-1);break;
	case 6 : print_word_2_lcd("Saturday:",-1,-1);break;
	case 7 : print_word_2_lcd("Sunday:",-1,-1);break;

	}	 
	char word[6];
	time_2_string(timeCounter/60,word);
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd(":",-1,-1);  
	time_2_string(timeCounter%60,word);
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd(":",-1,-1);
	//time_2_string(0x0,word);
	print_word_2_lcd("00        ",-1,-1);
	print_word_2_lcd("Current Temp     : ",2,6);
	if(temperature != -1)
	{
		float_2_string(temperature, word);
		print_word_2_lcd(word,-1,-1);
	}  
	print_word_2_lcd("Current Pressure : ",2,8);
	if(pressure != -1)
	{
		int_2_string6(pressure, word);
		print_word_2_lcd(word,-1,-1);
	}    
	print_word_2_lcd("to return press # ",6,12);

}

//////////////////////////// Prin the Normal mode to LCD /////////////////////////
void print_Normal_main_2_lcd(){
	print_word_2_lcd("Normal Mode",15,0);
	print_word_2_lcd("Date : ",2,2);
	//getTime();
	switch((recordDate % 7) + 1)
	{
	case 1 : print_word_2_lcd("Monday:",-1,-1);break;
	case 2 : print_word_2_lcd("Tuesday:",-1,-1);break;
	case 3 : print_word_2_lcd("Wednesday:",-1,-1);break;
	case 4 : print_word_2_lcd("Thursday:",-1,-1);break;
	case 5 : print_word_2_lcd("Friday:",-1,-1);break;
	case 6 : print_word_2_lcd("Saturday:",-1,-1);break;
	case 7 : print_word_2_lcd("Sunday:",-1,-1);break;

	}	 
	char word[7];
	time_2_string(timeCounter / 60,word);
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd(":",-1,-1);
	time_2_string(timeCounter % 60,word);
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd(":",-1,-1);
	time_2_string(secondCounter,word);
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd("    ",-1,-1);
	int ii;
	moveTextPointer(0, 3);
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	print_word_2_lcd("Current Temp     : ",2,5);
	if(temperature != -1)
	{
		float_2_string(temperature, word);
		print_word_2_lcd(word,-1,-1);
	}  
	print_word_2_lcd("Current Pressure : ",2,7);
	if(pressure != -1)
	{
		int_2_string6(pressure, word);
		print_word_2_lcd(word,-1,-1);
	}    
	moveTextPointer(0, 9);
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	print_word_2_lcd("Input N times samples: ",1,10);
	if(range != 10)
	{
		printLetter(range + 48);
		printLetter(' ');
	}
	else
	{
		printLetter('1');
		printLetter('0');
	}
	print_word_2_lcd("Average Temp    : ",2,11);
	float_2_string(avgTemperature, word);
	print_word_2_lcd(word,-1,-1);

	print_word_2_lcd("Average Pressure: ",2,12);
	int_2_string6(avgPressure, word);
	print_word_2_lcd(word,-1,-1);

	moveTextPointer(0, 14);
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	print_word_2_lcd("To return press # ",1,15);

}

///////////// Print Pressure and Tempreture TXT style to the LCD //
void print_temp_Pressure_LCD_Week_txt()
{ 
	print_word_2_lcd("      MON  TUE  WED  THU  FRI  SAT  SUN",0,15);
	moveTextPointer(0, 14);
	int ii = 0,jj;
	for(ii = 0; ii < 40; ii++)
	{
		printLetter('-');
	}
	print_word_2_lcd(" Pressure & Tempreture ",7,0);
	print_word_2_lcd("Avg",1,3);
	print_word_2_lcd("Min",1,5);
	print_word_2_lcd("Max",1,7);
	print_word_2_lcd("Avg",1,9);
	print_word_2_lcd("Min",1,11);
	print_word_2_lcd("Max",1,13);
	print_word_2_lcd("P:X10",0,2);
	print_word_2_lcd("T:",0,8);
	moveGraghPointer(1, 64);
	for(jj = 0; jj < 7; jj++)    
		for(ii = 20; ii < 110; ii++)
		{
			moveGraghPointer(4+jj*5 + 1, ii);
			printPixel(ii%2 << 5);
		}
		moveGraghPointer(2, 64);
		for(ii = 0; ii < 37; ii++)
		{
			printPixel(0x2A);
		}

		for(ii = 0; ii < 7; ii++)
			for(jj = 0; jj < 3; jj++)
			{
				if(isTest)
					print_TXT_TMP_PRS(ii, jj, fixedPressureData[ii][jj]);
				else
					print_TXT_TMP_PRS(ii, jj, pressureData[ii][jj]);
			}
			for(ii = 0; ii < 7; ii++)
				for(jj = 3; jj < 6; jj++)
				{
					if(isTest)
						print_TXT_TMP_PRS(ii, jj, fixedTemperatureData[ii][jj - 3]);
					else
						print_TXT_TMP_PRS(ii, jj, temperatureData[ii][jj - 3]);
				}
} 


/////////////////////////////////// for time : Convert 2 digits into the string ////////
void time_2_string(int value, char * word)
{
	*word++ = (value - (value/100)*100)/10 + 48;
	*word++ = ((int)value)%10 + 48;
	*word = '\0';  
}
/////////////////////// Conver float to string "00.00" ////////////////////////////////////
void float_2_string(float value, char * word)
{
	// *word++ = (int)value%1000/100 +48;
	*word++ = (int)value%100/10 +48;
	*word++ = (int)value%10 +48;
	*word++ = '.';
	*word++ = (int)((value - (int)value)/0.1)+ 48;
	int temp = (int)((value - (int)value)/0.1);
	*word++ = (int)(((value - (int)value)-temp*0.1)/0.01)+48;
	*word = '\0';
}

///////////////////////Clear the txt are of LCD /////////////////////

void clear_txt_LCD(){
	moveAP(0x00, 0x00);
	//clear screen
	int i;
	for(i = 0; i < 640; i++)
	{
		printLetter(' ');
	}
}

///////////////////Clear the garphic area of the LCD ////////////////

void clear_graph_LCD(){
	int i;
	moveAP(0x00, 0x40);
	for(i = 0; i < 5120; i++)
	{
		Write_Data_2_Display(0x00);
		Write_Command_2_Display(0xC0);
	}
}

/////////////// Convert Int to String 5 digits "54321"///////////////
void int_2_string(int value, char * word)
{
	*word++ = (int)value%100000/10000 +48;
	*word++ = (int)value%10000/1000 +48;
	*word++ = (int)value%1000/100 +48;
	*word++ = (int)value%100/10 +48;
	*word++ = (int)value%10 +48;
	*word = '\0';
}

/////////////// Convert Int to String 5 digits "54321"///////////////
void int_2_string6(int value, char * word)
{
	*word++ = (int)value%1000000/100000 +48;
	*word++ = (int)value%100000/10000 +48;
	*word++ = (int)value%10000/1000 +48;
	*word++ = (int)value%1000/100 +48;
	*word++ = (int)value%100/10 +48;
	*word++ = (int)value%10 +48;
	*word = '\0';
}

//prepare data for test mode
void simulation()
{
	fixedPressureData[0][0] = 10100;
	fixedPressureData[0][1] = 9800;
	fixedPressureData[0][2] = 10300;
	fixedPressureData[1][0] = 10000;
	fixedPressureData[1][1] = 9900;
	fixedPressureData[1][2] = 10200;
	fixedPressureData[2][0] = 10211;
	fixedPressureData[2][1] = 10000;
	fixedPressureData[2][2] = 10300;
	fixedPressureData[3][0] = 10233;
	fixedPressureData[3][1] = 9800;
	fixedPressureData[3][2] = 10300;
	fixedPressureData[4][0] = 10243;
	fixedPressureData[4][1] = 10001;
	fixedPressureData[4][2] = 10290;
	fixedPressureData[5][0] = 10033;
	fixedPressureData[5][1] = 9810;
	fixedPressureData[5][2] = 10300;
	fixedPressureData[6][0] = 10100;
	fixedPressureData[6][1] = 9900;
	fixedPressureData[6][2] = 10300;

	fixedTemperatureData[0][0] = 22;
	fixedTemperatureData[0][1] = 11;
	fixedTemperatureData[0][2] = 30;
	fixedTemperatureData[1][0] = 19;
	fixedTemperatureData[1][1] = 8;
	fixedTemperatureData[1][2] = 25;
	fixedTemperatureData[2][0] = 20;
	fixedTemperatureData[2][1] = 19;
	fixedTemperatureData[2][2] = 30;
	fixedTemperatureData[3][0] = 30;
	fixedTemperatureData[3][1] = 25;
	fixedTemperatureData[3][2] = 33;
	fixedTemperatureData[4][0] = 56;
	fixedTemperatureData[4][1] = 40;
	fixedTemperatureData[4][2] = 70;
	fixedTemperatureData[5][0] = 50;
	fixedTemperatureData[5][1] = 25;
	fixedTemperatureData[5][2] = 75;
	fixedTemperatureData[6][0] = 80;
	fixedTemperatureData[6][1] = 66;
	fixedTemperatureData[6][2] = 90;
}

void print_simulation_menu()
{
	int ii;
	print_word_2_lcd("Simulation",15,0);
	moveGraghPointer(0,7); for(ii = 0; ii < 40; ii++) {   printPixel(0x3F);  }
	print_word_2_lcd("Press the menu Number then #",0,1);
	moveGraghPointer(2,21); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("1#.Text Mode",2,3);
	moveGraghPointer(2,37); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("2#.Pressure Graph Mode",2,5);
	moveGraghPointer(2,53); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("3#.Temperature Graph Mode",2,7);
	moveGraghPointer(2,69); for(ii = 8; ii < 41; ii++) {   printPixel(0x2a);  }
	print_word_2_lcd("#.Return back ",2,9);
}

/////////////////////////Print TXT for Temp and Pressure for avg,min,max////////////////////////////////
///// Line 0 to 2 for pressure and Line 3 to 5 for temp
void print_TXT_TMP_PRS(char day, char line, float value)
{ 
	if (line>5 || day >6) return;
	char word[5];
	if (line>=3){
		float_2_string(value, word);
		print_word_2_lcd(word,5+day*5,line*2+3);
	}else{
		if (line<3){
			int_2_string(value, word);
			print_word_2_lcd(word,5+day*5,line*2+3);
		}
	}

}

///////////// Sun Direction //////////////////////////////////

void Sun_direction(int jj){
	char word[4];
	int value = jj;
	print_word_2_lcd(" Sun Direction ",7,0);
	print_word_2_lcd(" Servo Angle : ",1,2);
//	if((word[0] != 0) || (word[1] !=0) || (word[2] != 0))
//	{
		word[0] = (int)value%1000/100 +48;
		word[1] = (int)value%100/10 +48;
		word[2] = (int)value%10 +48;
		word[3] = '\0';
//	}
	print_word_2_lcd(word,-1,-1);
	print_word_2_lcd("Sun rise -",10,5);
	print_word_2_lcd(" Morning -",10,7);
	print_word_2_lcd("    Noon -",10,9);
	print_word_2_lcd(" evening -",10,11);
	print_word_2_lcd("   night -",10,13);

	clear_graph_LCD();
	drawCircle(7,22,jj/2+23);
	//Delay(1000000);
}

void drawCircle(int r, char col, char row)

{

	int N = 2*r+1;
	int x, y;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <N; j++)
		{
			x = j-r ;
			y = i-r ;
			if (x*x + y*y <= r*r+1 ){
				moveGraghPointer(col+i, row+j);
				printPixel(0x3F);
			}
			else 
				printPixel(0x0);
		}
	}
}

void updateData(Entity * data, int time)
{
	pressureData[data->date][0] = (pressureData[data->date][0] * (time - 1) + data->pressure) / time;
	if(pressureData[data->date][1] == 0)
	{
		pressureData[data->date][1] = data->pressure;
	}else if(data->pressure < pressureData[data->date][1])
		pressureData[data->date][1] = data->pressure;
	if(data->pressure > pressureData[data->date][2])
		pressureData[data->date][2] = data->pressure;

	temperatureData[data->date][0] = (temperatureData[data->date][0] * (time - 1) + data->temperature) / time;
	if(temperatureData[data->date][1] == 0)
	{
		temperatureData[data->date][1] = data->temperature;
	}else if(data->temperature < temperatureData[data->date][1])
		temperatureData[data->date][1] = data->temperature;
	if(data->temperature > temperatureData[data->date][2])
		temperatureData[data->date][2] = data->temperature;
}