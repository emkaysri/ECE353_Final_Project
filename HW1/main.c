//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include "main.h"
#include "hw1_lib.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
extern void hw1(void);

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  hw1_init();
  hw1_draw_up_arrow();  
  while(1)
  {
    hw1();
  }
}


