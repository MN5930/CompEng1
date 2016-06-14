# CompEng1
Computer Engineering 1 course - Embedded programming

Software Function description:
Report
The Internal Time Clock (RTC) is a very good reference to measure the time very precisely. The program uses RTC interrupt in different methods (Seconds, minutes and days) to increase the program main counter. This counter represents a day when is equal to 1440 minutes although in fast mode the counter increases every second. In another word, every second counts as a minute, Minutes as Hours and etc.
The program’s data structure is composed of a single link list. The internal memory is full when new node cannot be memory allocated. According to the test procedure, Data sample exceeding a day and half would not get any memory. Therefore, for some time, the main time counter value was changed to smaller value (from 1440 to 200) to cover the whole week’s data. Also, to avoid software crash because of lack of memory, due to the need of calling a new function’s variables, any time before a new node allocation the memory’s free space would be checked.
Furthermore with the testing of components procedure, to make sure that the hardware works properly, extra devices such as a fan (to test the air pressure), hair dryer and rapped ice cubes were used. An actual test of one week performed and the system worked fine without any crash.
Delay function is being used fewer and for smaller periods to make sure of a fast and well performed operating system.
One problem that the system is facing is there is not actual output for minus temperature in the LCD. Although the system uses both LCD modes but there is not enough space to show minus degrees of the temperature.
The project is included the following Library:
X_BUTTON X_COMMON X_ENTITY X_FUNCTIONS X_KEYPAD X_LCD
X_LED X_NVIC X_PHOTO X_PIO X_PMC
provides functions to get button’s status and provide interrupt provides common functions like delay function.
provides data structure and data manage functions.
provides functions like track sun’s position, get temperature’s value. provides functions to read keypad’s value
provides functions show text and diagram provides functions to control LED’s status provides function to configure NVIC interrupt provides functions to get photos’ values. provides functions to manage pins.
provides functions to manage PMC.
X_PRESSURE X_RTC X_SERVO X_TEMP
Air pressure sensor:
provides functions to get pressure’s value.
provides functions to get real time clock and interrupt provides functions to control servo
provides functions to get temperature’s value
Two Wire Interface is being used, One for Clock (SCL) and second for Data (SDA). The designed protocol in this program uses single data read/write mode with internal addressing. First the device’s mode set to standby. Changing the mode from standby to active enables 128 bits resolution. Between all the functions that sensor offers just altimeter is being used. To make sure that the device is ready the system begins with reading the status register. On the next step, the program reads 3 bytes of the data register to calculate the value of the air pressure. The clock’s speed in the normal mode is 100 KHz.
Servo:
PWM is the technique being used to control the servo. The signal starts with low level. Therefore the high width modulation is 19.3ms for complete left and 17.7ms for complete right while the whole pulse width is 20ms. By changing the high width from 19.3ms to 17.7ms the signal are able to control the position of the servo smoothly. It’s been consider in this program that complete left is 0 degree angle and complete right is 180 degree angle.
LCD:
LCD uses three different buses. Data bus is a shared bus with the keypad. LCD control bus, used to control read, write or reset and to control the direction of data between the LCD and the microprocessor. With the address bus (enable pin of two 74chips) the selection of communication is performed for LCD or keypad. Both of the LCD modes is performed. Text mode uses 0000H to 3FFFH address and graphic mode uses 4000H t0 7FFFH of the LCD RAM.
Temperature sensor:
Temperature sensor uses single wire interface. In this procedure, the system uses interrupt to count the time period between rising edge and falling edge of an analog wave. Interrupt happens when the analog signal rises (register B loads). Register A loads when the edge is falling, the difference between register A and register B gives us the value to measure the temperature.
Photo sensor:
To read the photo sensors ADC has been used. Channel 1 is dedicated to sensor 2 and channel 2 is dedicated to sensor 1.
To find the sun direction the value of the sensor 1 is compared with the value of the sensor 2 (ignoring the differences of 30 for lower sensitivity). By moving the servo it finds the position where both values are equal. Brighter light gives high value.
Keypad:
The 4 bits shared data bus with the LCD is being might conflict the data of the keypad. Therefore, a 74chip separates the data from LCD. When the data bus is not needed for keypad the 74chip is disabled. There are 3 bits output pins feed the keypad for the columns. The 4 bits data bus is used to scan the output of the keypad to identify which button has been pushed.
Button:
The bouncing problem with the button is solved by using the bouncing filter embedded in the microchip. When the button is pressed interrupt happens and the certain value then can be read.
LED:
Two different LEDs are identifier as alarm and enable keypad input. The first LED alarms when the temperature is higher than 35 or lower than 0. The second LED turns on when user can input a value through keypad.
Specification
On the main menu there are seven options. By pressing the main button the keypad becomes active to input the option number into the system.
Option 1(Normal mode): It shows the current data, current temperature and current pressure. The user is also able to input N times desired sample of the temperature and pressure within one minute. The system then will show the average of these N times’ samples for pressure and temperature individually. To return to the main menu press the main button then pound (#).
Option 2(Fast mode): This mode will change the recording period from 1 minute to 1 second. It also shows the time in fast mode and current temperature and current pressure. To return to the main menu press the main button then pound (#).
Option 3(Pressure Graph): This mode shows the average, minimum and maximum of each week day’s pressure separately as bar graphs. If there is not any data exist for special day, the bar graph will be empty. To return to the main menu press the main button then pound (#).
Option 4(Temperature Graph): This mode shows the average, minimum and maximum of each week day’s temperature separately as bar graphs. If there is not any data exist for special day, the bar graph will be empty. Temperature below 0 degree or higher than 100 is not considered. To return to the main menu press the main button then pound (#).
Option 5(Text mode): This mode shows the average, minimum and maximum of each week day’s pressure and temperature separately as text. If there is not any data exist for special day, the value of 0 will be displayed. To return to the main menu press the main button then pound (#).
Option 6(Sun direction): This mode shows and tracks the direction of the sun as 0 for sun rise and 180 as night. To return to the main menu press the main button then pound (#).
Option 7(Test mode): The system has prerecord data. This mode displays these data to test, in text or graphic for both pressure and temperature accordingly.
Option 1(Text Mode):
Option 2(Pressure Graph Mode): Option 3(Temperature Mode): Option 4(Return):
Alarm: The LED is considered as an alarm for the temperature above 35 and below 0 degrees. For instance the LED stays on for a 40 degree temperature unless the temperature drops below 35 degrees.
Logic Diagram
 Screenshot of the TWI communication signal.
 --M.Nazari
