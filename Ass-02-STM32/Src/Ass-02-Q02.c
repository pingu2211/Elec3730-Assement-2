//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"

#define MOVEMENT_THRESHOLD 10
#define ygrid (240-1)/5
#define xgrid (320)/5
#define FILL_COLOUR	0xFFFF
#define ALT_COLOUR	0x9CB2
#define TEXT_COLOUR 0x127C
#define COLOUR_BLACK 0xFFFF
#define COLOUR_WHITE 0x0000
#define MAX_LEN 18
bool _KEY_DOWN;

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

struct button buttons[]={
		{"0",0*xgrid,4*ygrid,2*xgrid,ygrid,"0",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
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
		{"^",4*xgrid,3*ygrid,xgrid,ygrid,"POW",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{"C",4*xgrid,4*ygrid,xgrid,ygrid,"C",0xFA8A,0xA000,TEXT_COLOUR},
		{"`",2*xgrid,4*ygrid,xgrid,ygrid,"+/-",FILL_COLOUR,ALT_COLOUR,TEXT_COLOUR},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

int _ITT = 0;
char ** opperands;
char _OPPERATOR=NULL;
void button_pressed(struct button key){
	char * scratch;
	BSP_LCD_SetTextColor(COLOUR_WHITE);
	BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize(),ygrid);
	double result=0;
	switch (key.ID[0]){
	case '`':
		if (opperands[_ITT][0]=='-'){
			opperands[_ITT][0]='+';
		}else if (opperands[_ITT][0]=='+'){
			opperands[_ITT][0]='-';
		}else{
			scratch = malloc(MAX_LEN);
			strcpy(scratch,"-");
			opperands[_ITT]=strcat(scratch,opperands[_ITT]);
			scratch=NULL;
		}
		break;
	case 'C':
		if (strlen(opperands[_ITT])>0)opperands[_ITT]=strcpy(opperands[_ITT],"\0");
		else {
			_ITT=0;
			strcpy(opperands[0],"\0");
			strcpy(opperands[1],"\0");
			_OPPERATOR=NULL;
		}
		break;
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
	case '=':
		if (_OPPERATOR==NULL||(strlen(opperands[1])<1)){
			_OPPERATOR=key.ID[0];
			if(_ITT<1){
				_ITT=(_ITT+1)%2;
			}
		}else{
			double n1 = atof(opperands[0]);
			double n2 = atof(opperands[1]);
			switch(_OPPERATOR){
			case '+':
				result = n1+n2;
				break;
			case '*':
				result = n1*n2;
				break;
			case '/':
				result = n1/n2;
				break;
			case '-':
				result = n1-n2;
				break;
			case '^':
				result = pow(n1,n2);
				break;
			case '=':
				break;
			}
			_OPPERATOR=key.ID[0];
			strcpy(opperands[1],"\0");
			opperands[0]=realloc(opperands[0],MAX_LEN);
			snprintf(opperands[0],MAX_LEN,"%lf",result);
			_ITT=1;
		}
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
		if (strlen(opperands[_ITT])<MAX_LEN){
			opperands[_ITT] = realloc(opperands[_ITT],(strlen(opperands[_ITT])+1)+(strlen(key.ID)+1));
			strcat(opperands[_ITT],key.ID);
			printf("\n%i:%s\n",_ITT,opperands[_ITT]);
		}
		break;
	case '.':
		if (strchr(opperands[_ITT],'.')==NULL){
			strcat(opperands[_ITT],key.ID);
		}
		break;
	}

	if(strlen(opperands[_ITT])>1&&opperands[_ITT][0]=='0'){
			char* new=strpbrk(opperands[_ITT], "-123456789.");
			if (new!=NULL){
				opperands[_ITT]=new;
			}
	}
	int width=(((sFONT *)BSP_LCD_GetFont())->Width);
	BSP_LCD_SetBackColor(COLOUR_WHITE);
	BSP_LCD_SetTextColor(COLOUR_BLACK);
	if (_OPPERATOR!=NULL)BSP_LCD_DisplayChar(BSP_LCD_GetXSize()-width,LINE(0), _OPPERATOR);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()-width,LINE(0), opperands[(_ITT+1)%2] , RIGHT_MODE);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize(),LINE(1), opperands[_ITT] , RIGHT_MODE);
}


void CalculatorInit(void)
{
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();
  if (USR_DBG)printf("Screen is %i X %i\n", BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  for (int i=0;buttons[i].ID!=NULL;i++){
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


int _DEBOUNCE = 0;
void CalculatorProcess(void)
{
  int state = BSP_TP_GetDisplayPoint(&display);
  if (state == 0){
	  _DEBOUNCE = 0;
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_SET); // Toggle LED4
	  if (!_KEY_DOWN){
		  if (USR_DBG) printf("TOUCH GOT (%i,%i)\n",display.x,display.y);
			for (int i=0;buttons[i].ID!=NULL;i++){
				  if (is_pressed(buttons[i],&display)){
					  if (USR_DBG) printf("%s PRESSED (%i,%i)",buttons[i].ID,display.x,display.y);
					  button_press(buttons[i]);
					  button_pressed(buttons[i]);
					  _KEY_DOWN=true;
				  }else{
					  button_show(buttons[i]);
			}
	  	  }
	  }
  }else{
	  if (_DEBOUNCE++ > 30){
		  _KEY_DOWN=false;
		  HAL_GPIO_WritePin(GPIOD, LD4_Pin,GPIO_PIN_RESET);
	  }

  }
}
