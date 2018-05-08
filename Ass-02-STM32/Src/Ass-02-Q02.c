//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"

#define MOVEMENT_THRESHOLD 10
#define ygrid (240-1)/5
#define xgrid (320)/5
#define BUTTONS_COUNT 17
#define FILL_COLOUR	0xFFFF
#define ALT_COLOUR	0x9CB2
#define TEXT_COLOUR 0x127C
#define MAX_LEN 18
bool KEY_DOWN;

typedef struct button{
	char * ID;
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
	BSP_LCD_SetBackColor(B.altfillColour);
	BSP_LCD_FillRect(B.x, B.y, B.width,	B.hight);
	BSP_LCD_SetTextColor(B.textColour);
	BSP_LCD_SetBackColor(B.altfillColour);
	BSP_LCD_DisplayStringAt(B.x+B.width/2, B.y+B.hight/2, B.text, CENTER_MODE);
}

bool is_pressed(struct button B,Coordinate *point){
	if (point->x > B.x && point->x < B.x+B.width && point->y > B.y && point->y < B.y+B.hight) return true;
	else return false;
}

int dist(Coordinate N1, Coordinate N2){
	int diff = (int)(N2.x-N1.x)^2+(N2.y-N1.y)^2;
	//if(USR_DBG)printf("DIST = %i\n",diff);
	return diff;
}

struct button buttons[BUTTONS_COUNT]={
		{"0",0*xgrid,4*ygrid,3*xgrid,ygrid,"0",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"1",0*xgrid,1*ygrid,xgrid,ygrid,"1",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"2",1*xgrid,1*ygrid,xgrid,ygrid,"2",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"3",2*xgrid,1*ygrid,xgrid,ygrid,"3",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"4",0*xgrid,2*ygrid,xgrid,ygrid,"4",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"5",1*xgrid,2*ygrid,xgrid,ygrid,"5",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"6",2*xgrid,2*ygrid,xgrid,ygrid,"6",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"7",0*xgrid,3*ygrid,xgrid,ygrid,"7",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"8",1*xgrid,3*ygrid,xgrid,ygrid,"8",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"9",2*xgrid,3*ygrid,xgrid,ygrid,"9",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"+",3*xgrid,1*ygrid,xgrid,ygrid,"+",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"-",3*xgrid,2*ygrid,xgrid,ygrid,"-",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{".",3*xgrid,3*ygrid,xgrid,ygrid,".",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"=",3*xgrid,4*ygrid,xgrid,ygrid,"=",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"*",4*xgrid,1*ygrid,xgrid,ygrid,"*",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"/",4*xgrid,2*ygrid,xgrid,ygrid,"/",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"C",4*xgrid,3*ygrid,xgrid,ygrid,"C",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR}
};

int itt = 0;
char ** opperands;
void button_pressed(struct button key){
	switch (key.ID[0]){
	case 'C':
		opperands[itt]=strcpy(opperands[itt],"\0");
		break;
	case '+':
	case '-':
	case '/':
	case '*':
		BSP_LCD_SetBackColor(0x0000);
		BSP_LCD_SetTextColor(0xffff);
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize(),LINE(0),key.ID,RIGHT_MODE);
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if (strlen(opperands[itt])<MAX_LEN){
			opperands[itt] = realloc(opperands[itt],(strlen(opperands[itt])+1)+(strlen(key.ID)+1));
			strcat(opperands[itt],key.ID);
			printf("\n:%s\n",opperands[itt]);
		}
		break;
	case '.':
		if (strchr(opperands[itt],'.')==NULL){
			strcat(opperands[itt],key.ID);
		}
		break;
	}

	BSP_LCD_SetTextColor(0x0000);
	BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize(),ygrid);
	BSP_LCD_SetBackColor(0x0000);
	BSP_LCD_SetTextColor(0xffff);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize(),LINE(1), opperands[itt] , RIGHT_MODE);
}


void CalculatorInit(void)
{
	sFONT font;
  // STEPIEN: Assume horizontal display
  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();
  if (USR_DBG);printf("Screen is %i X %i\n", BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  for (int i=0;i<BUTTONS_COUNT;i++){
	  button_show(buttons[i]);
  }
  opperands = malloc (2*sizeof(char*));
  if (opperands == NULL){
	  printf("MEMMORY ERROR");
  }else{
	  opperands[0]=malloc(1*sizeof(char));
	  opperands[1]=malloc(1*sizeof(char));
	  if (opperands[0]!=NULL){
		  opperands[0][0]='\0';
	  }else{
		  printf("MEMMORY ERROR");
	  }
	  if (opperands[1]!=NULL){
		  opperands[1][0]='\0';
	  	  }else{
	  		printf("MEMMORY ERROR");
	  	  }
  }
}


int debounce = 0;
void CalculatorProcess(void)
{
  int state = BSP_TP_GetDisplayPoint(&display);
  if (state == 0){
	  debounce = 0;
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_SET); // Toggle LED4
	  if (!KEY_DOWN){
		  if (USR_DBG) printf("TOUCH GOT (%i,%i)\n",display.x,display.y);
			for (int i=0;i<BUTTONS_COUNT;i++){
				  if (is_pressed(buttons[i],&display)){
					  if (USR_DBG) printf("%s PRESSED (%i,%i)",buttons[i].ID,display.x,display.y);
					  button_press(buttons[i]);
					  button_pressed(buttons[i]);
					  KEY_DOWN=true;
				  }else{
					  button_show(buttons[i]);
			}
	  	  }
	  }
  }else{
	  if (debounce++ > 30){
		  KEY_DOWN=false;
		  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_RESET);
	  }

  }
}
