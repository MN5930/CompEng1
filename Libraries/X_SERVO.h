#ifndef X_SERVO
#define X_SERVO

#define NUETRAL_POSITION 0xF60
#define LEFT_POSITION    0x1794
#define RIGHT_POSITION   0x72C
#define INTERVAL         0xD2

#define LEFT 1
#define RIGHT 2

//move servo , 1 is left , 2 is right
float moveServo(int value);

#endif