//     $Date: 2018-03-26 08:32:18 +1100 (Mon, 26 Mar 2018) $
// $Revision: 1217 $
//   $Author: Peter $

#include "Ass-02.h"

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

void CalculatorInit(void)
{
  // STEPIEN: Assume horizontal display

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_TP_Init();

}

void CalculatorProcess(void)
{

  uint16_t linenum = 0;

  // getDisplayPoint(&display, Read_Ads7846(), &matrix );
  //if (BSP_TP_GetDisplayPo2int(&display) == 0);


}
