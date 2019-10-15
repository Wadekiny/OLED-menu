#include "init.h"
#include "oled.h"

enum main_catalog{LEFT,RIGHT,MODE,PID,MESSAGE,DESIGNED,};
enum mode_catalog{AUTO,MANUAL,};
enum pid_catalog{KP,KI,KD,};

extern enum main_catalog main_first;
extern enum main_catalog main_pointer;
extern u8 main_pointer_y;

extern enum mode_catalog mode_pointer;
extern u8 mode_pointer_y;

extern enum pid_catalog pid_pointer;
extern u8 pid_pointer_y;

extern u8 mode;

void Init()
{
	OLED_Display_Off();	
	OLED_Display_On();
	OLED_Init();	
	OLED_Clear();
	main_first = LEFT;
	main_pointer = LEFT;
	main_pointer_y = 0;
	
	mode_pointer = AUTO;
	mode_pointer_y = 0;

	pid_pointer = KP;
	pid_pointer_y = 0;
	
	mode = AUTO;
}