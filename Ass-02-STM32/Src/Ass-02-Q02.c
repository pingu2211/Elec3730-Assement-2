//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"




typedef struct button{
	uint16_t x, y ,width, hight;
	char * text;
	uint16_t fillColour;
	uint16_t textColour;
};


void button_show(struct button B){
	BSP_LCD_SetTextColor(B.fillColour);
	BSP_LCD_FillRect(B.x, B.y, B.width,	B.hight);
	BSP_LCD_SetTextColor(B.textColour);
	BSP_LCD_SetBackColor(B.fillColour);
	BSP_LCD_DisplayStringAt(B.x+B.width/2, B.y+B.hight/2, B.text, CENTER_MODE);
}

bool button_pressed(struct button B,Coordinate *point){
	if (point->x > B.x && point->x < B.x+B.width) return true;
	else return false;
}


struct button test;

void CalculatorInit(void)
{
  // STEPIEN: Assume horizontal display

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();

  unsigned int X_SIZE = BSP_LCD_GetXSize();
  unsigned int Y_SIZE = BSP_LCD_GetYSize();
  struct button new= {X_SIZE/4,Y_SIZE/4,X_SIZE/2,Y_SIZE/2,"test",0x9CB2,0x127C};
  test = new;

  button_show (test);
}

void CalculatorProcess(void)
{
  // STEPIEN: Assume horizontal display
  // getDisplayPoint(&display, Read_Ads7846(), &matrix );
	Coordinate last;
  if (BSP_TP_GetDisplayPoint(&display) == 0){
	  if (button_pressed(test,&display)){
		  printf("pressed test");
	  }


  }
}
