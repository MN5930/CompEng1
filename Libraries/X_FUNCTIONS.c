#include "X_FUNCTIONS.h"
#include "X_PHOTO.h"
#include "X_SERVO.h"
#include "X_LED.h"
#include "X_TEMP.h"
#include "X_KEYPAD.h"
#include "X_ENTITY.h"
#include "X_COMMON.h"
#include "X_LCD.h"

#include "stdlib.h"

static float angle;
char checkLinkList();

//track the sun
float trackSun()
{
  unsigned int a, b;
  a = 0;
  b = 0;
  
  getPhoto(&a, &b);
      
  if(a > b &&  (a - b) > 30)
  {
    angle = moveServo(LEFT);
    //Delay(10000);
  }else if(a < b && (b - a) > 30)
  {
    angle = moveServo(RIGHT);
    //Delay(10000);
  }
  return angle;
}

float getTemp()
{
  int ii;
  request_temp();
  for(ii = 0; ii < 20; ii++)
  {
    if(temp_ready == 1)
      break;
  }
  if(temp_ready == 1)
    return get_temp();
  else
    return -1;
}

void printSystemTest()
{
	int tmp;
	static char led_flag = 0;
	static float servo_angle = 0;
	static char servo_direction = LEFT;
	unsigned int photo1, photo2;
	
	print_word_2_lcd("System Test",15,0);
	//*********************keypad*********************************
	print_word_2_lcd("Keypad:", 2, 1);
	read_keyboard(&tmp);
	if(tmp == -1)
	{
	printLetter(' ');
	}else if(tmp == 10)
	printLetter('*');
	else if(tmp == 11)
	printLetter('0');
	else if(tmp == 12)
	printLetter('#');
	else
	printLetter(tmp%10 + 48);
	//*********************LED************************************
	print_word_2_lcd("LED: Blinking...", 2, 3);
	if(led_flag)
	{
	alarmLedOn();
	keyLedOn();
	}
	else
	{
	alarmLedOff();
	keyLedOff();
	}
	led_flag = !led_flag;
	//*********************photo*********************************
	getPhoto(&photo1, &photo2);
	char word[6];
	print_word_2_lcd("Photo1: ", 2, 5);
	int_2_string6(photo1, word);
	print_word_2_lcd(word, -1, -1);  
	print_word_2_lcd("Photo2: ", 20, 5);
	int_2_string6(photo2, word);
	print_word_2_lcd(word, -1, -1);
	//*********************temp and pressure*********************
	print_word_2_lcd("Temp: ",2,7);
	if(temperature != -1)
	{
		float_2_string(temperature, word);
		print_word_2_lcd(word,-1,-1);
	}  
	print_word_2_lcd("Pressure: ",2,9);
	if(pressure != -1)
	{
		int_2_string6(pressure, word);
		print_word_2_lcd(word,-1,-1);
	}
	//*********************Servo*********************************	
	print_word_2_lcd("Servo: Turning...", 2, 11);
	if(servo_angle == 0)
	  servo_direction = RIGHT;
	if(servo_angle == 180)
	  servo_direction = LEFT;
	servo_angle = moveServo(servo_direction);
	
	if(checkLinkList())
	{
	  print_word_2_lcd("Link list is good.     ", 2, 13);
	}else
	{
	  print_word_2_lcd("Link list is not good.  ", 2, 13);
	}
}

char checkLinkList()
{
	Entity * header, * tail;
	header = createEntity(21, 10000, 1);
	if(header == NULL)
		return -1;
	header->next = createEntity(22, 99999, 3);
	tail = header->next;
	if(tail == NULL)
	  return -1;
	
	decreaseDate(header);
	if(header->date != 0 || tail->date != 2)
	  return -1;
	
	header = deleteFirstDay(header);
	if(header->date != 2)
		return -1;
	return 1;
}