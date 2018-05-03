//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"

#define MOVEMENT_THRESHOLD 10
#define grid 60
#define BUTTONS_COUNT 10
#define FILL_COLOUR	0xFFFF
#define ALT_COLOUR	0x9CB2
#define TEXT_COLOUR 0x127C

typedef struct button{
	char* ID;
	uint16_t x, y ,width, hight;
	char * text;
	uint16_t fillColour;
	uint16_t altfillColour;
	uint16_t textColour;
};


void button_show(struct button B){
	BSP_LCD_SetTextColor(B.fillColour);
	BSP_LCD_FillRect(B.x, B.y, B.width,	B.hight);
	BSP_LCD_SetTextColor(B.textColour);
	BSP_LCD_SetBackColor(B.fillColour);
	BSP_LCD_DisplayStringAt(B.x+B.width/2, B.y+B.hight/2, B.text, CENTER_MODE);
}

void button_press(struct button B){
	BSP_LCD_SetTextColor(B.fillColour);
	BSP_LCD_FillRect(B.x, B.y, B.width,	B.hight);
	BSP_LCD_SetTextColor(B.textColour);
	BSP_LCD_SetBackColor(B.altfillColour);
	BSP_LCD_DisplayStringAt(B.x+B.width/2, B.y+B.hight/2, B.text, CENTER_MODE);
}

bool is_pressed(struct button B,Coordinate *point){
	if (point->x > B.x && point->x < B.x+B.width) return true;
	else return false;
}

int dist(Coordinate N1, Coordinate N2){
	return (int)(N2.x-N1.x)^2+(N2.y-N1.y)^2;
}

struct button buttons[BUTTONS_COUNT]={
		{"0",0*grid,0*grid,grid+2,grid+2,"0",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"1",0*grid,0*grid,grid+2,grid+2,"1",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"2",0*grid,1*grid,grid+2,grid+2,"2",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"3",0*grid,2*grid,grid+2,grid+2,"3",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"4",1*grid,0*grid,grid+2,grid+2,"4",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"5",1*grid,1*grid,grid+2,grid+2,"5",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"6",1*grid,2*grid,grid+2,grid+2,"6",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"7",2*grid,0*grid,grid+2,grid+2,"7",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"8",2*grid,1*grid,grid+2,grid+2,"8",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"9",2*grid,2*grid,grid+2,grid+2,"9",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR}

};

Coordinate last;

void CalculatorInit(void)
{
  // STEPIEN: Assume horizontal display

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();

//  unsigned int X_SIZE = BSP_LCD_GetXSize();
//  unsigned int Y_SIZE = BSP_LCD_GetYSize();
  for (int i=0;i<BUTTONS_COUNT;i++){
	  button_show(buttons[i]);
  }
}

void CalculatorProcess(void)
{
	USR_DBG=true;
  // STEPIEN: Assume horizontal display
  // getDisplayPoint(&display, Read_Ads7846(), &matrix );
	int state = BSP_TP_GetDisplayPoint(&display);
  if (BSP_TP_GetDisplayPoint(&display) == 0){
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_SET); // Toggle LED4
	  printf("TOUCH GOT (%i,%i)",display.x,display.y);
	  if (USR_DBG) printf("TOUCH GOT (%i,%i)",display.x,display.y);
	    for (int i=0;i<BUTTONS_COUNT;i++){
			  if (is_pressed(buttons[i],&display)){
				  if (USR_DBG) printf("%s PRESSED (%i,%i)",buttons[0].ID,display.x,display.y);
				  button_press(buttons[i]);
			  }else{
				  button_show(buttons[i]);
			  }
	  	  }
  }else{
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_RESET);
	  printf("TOUCH CODE = %i\n", state);
  }
  last = display;
}
