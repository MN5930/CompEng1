#ifndef X_RTC
#define X_RTC

extern char second, minute, hour;
extern char centery, year, month, date, day;
extern char isSecond, isMinute, isWeek;

void enableSecondEvent();
void enableTimeEvent();
void enableCalendar();

void disableSecondEvent();
void disableTimeEvent();
void disableCalendar();

void getTime();
void getRTCStatus();

void initial_RTC();

#endif