#ifndef X_LCD
#define X_LCD

#include "X_ENTITY.h"

extern int pressureData[7][3];//pressure data 0:avg 1:minimal 2:maximal
extern float temperatureData[7][3];//temperature data 0:avg 1:minimal 2:maximal
extern float pressure, temperature;//save the current value
extern float avgPressure, avgTemperature;// save the average value for normal mode
extern char range;//1 - 10 times per minute for normal mode
extern int recordDate;//the day 0~6
extern int timeCounter;// count the minute of one day 0~1439
extern int secondCounter;//count second in normal mode
extern char isTest;//0 means in normal mode, 1 means in test mode

void printTemp_LCD_Week();
void printPressure_LCD_Week();

void printLetter(char c);
void printPixel(char c);

void moveAP(char l, char h);

void moveTextPointer(unsigned char column, unsigned char row);
void moveGraghPointer(unsigned char column, unsigned char row);

void printTemp2L();
void printLine(char day, char line, char value); //print bar graphic

void initial_LCD();


void print_word_2_lcd(char *,char,char); // Print the word to the lcd in the given column and row

void print_main_2_lcd(); // Print the main menu to LCD

void time_2_string(int value, char * word); // change time to string
  
void print_Fast_main_2_lcd();// Print the fast mode menu to LCD

void print_Normal_main_2_lcd(); // Print the NORMAL mode into the LCD

void clear_txt_LCD(); // Clear the txt LCD

void clear_graph_LCD(); // Clear the graphic LCD

void float_2_string(float , char * ); // convert float to the string 

void print_temp_Pressure_LCD_Week_txt(); // Print Pressure and Tempreture TXT style to the LCD 

void print_TXT_TMP_PRS(char,char, float ); // Print the TXT for temp and press (AVG,MIN,MAX)
void int_2_string(int, char *); // Convert 5 digits to string
void int_2_string6(int value, char * word); // Convert 6 digits to string
void Sun_direction(); // Sun direction menu

void print_simulation_menu();

void Sun_direction(int); // Sun direction menu

void drawCircle(int r ,char , char);

void updateData(Entity * data, int time);

#endif