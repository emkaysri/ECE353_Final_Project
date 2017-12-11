#include "launchpad_io.h"
#include "timers.h"

volatile bool ALERT_1MS = false;
volatile bool ALERT_5000MS = false;

//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verify_base_addr(uint32_t base_addr)
{
   switch( base_addr )
   {
     case TIMER0_BASE:
     case TIMER1_BASE:
     case TIMER2_BASE:
     case TIMER3_BASE:
     case TIMER4_BASE:
     case TIMER5_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

//*****************************************************************************
// Returns the RCGC and PR masks for a given TIMER base address
//*****************************************************************************
static bool get_clock_masks(uint32_t base_addr, uint32_t *timer_rcgc_mask, uint32_t *timer_pr_mask)
{
  // Set the timer_rcgc_mask and timer_pr_mask using the appropriate
  // #defines in ../include/sysctrl.h
  switch(base_addr)
  {
    case TIMER0_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R0;
      *timer_pr_mask = SYSCTL_PRTIMER_R0;
      break;
    }
    case TIMER1_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R1;
      *timer_pr_mask = SYSCTL_PRTIMER_R1;
      break;
    }
    case TIMER2_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R2;
      *timer_pr_mask = SYSCTL_PRTIMER_R2;
      break;
    }
    case TIMER3_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R3;
      *timer_pr_mask = SYSCTL_PRTIMER_R3;
      break;
    }
    case TIMER4_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R4;
      *timer_pr_mask = SYSCTL_PRTIMER_R4;
      break;
    }
    case TIMER5_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R5;
      *timer_pr_mask = SYSCTL_PRTIMER_R5;
      break;
    }
    default:
    {
      return false;
    }
  }
  return true;
}


//*****************************************************************************
// Waits for 'ticks' number of clock cycles and then returns.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_wait(uint32_t base_addr, uint32_t ticks)
{
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }

  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;

  //*********************    
  // ADD CODE
  //*********************
	
  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
  gp_timer->TAILR = ticks;
	
	gp_timer->ICR |= TIMER_ICR_TATOCINT;
	
	gp_timer->CTL |= TIMER_CTL_TAEN;
	
	while((gp_timer->RIS & TIMER_RIS_TATORIS) == 0){}
  return true;
}


//*****************************************************************************
// Configure a general purpose timer to be a 32-bit timer.  
//
// Paramters
//  base_address          The base address of a general purpose timer
//
//  mode                  bit mask for Periodic, One-Shot, or Capture
//
//  count_up              When true, the timer counts up.  When false, it counts
//                        down
//
//  enable_interrupts     When set to true, the timer generates and interrupt
//                        when the timer expires.  When set to false, the timer
//                        does not generate interrupts.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_config_32(uint32_t base_addr, uint32_t mode, bool count_up, bool enable_interrupts)
{
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }
  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    
  //*********************    
  // ADD CODE
  //*********************
		//turn a and b timers off
  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
		
		//32 bit mode
  gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		
		//one shot count down mode
	gp_timer->TAMR &= ~(TIMER_TAMR_TAMR_M);   
	gp_timer->TAMR |=  mode;
		
	if(count_up) {
		gp_timer->TAMR |= TIMER_TAMR_TACDIR;
	} else {
		gp_timer->TAMR &= ~(TIMER_TAMR_TACDIR);
	}
	
	if(enable_interrupts) {
		gp_timer->IMR |= TIMER_IMR_TATOIM;
	} else {
		gp_timer->IMR &= ~TIMER_IMR_TATOIM;
	} 
		
  return true;  
}


//*****************************************************************************
// Configure Timer A with specs outlined in project
//*****************************************************************************
static void blackjack_timerA(uint32_t base_address, uint32_t ticks, uint16_t prescalar, IRQn_Type irq_num, uint32_t priority)
	{
	
  TIMER0_Type *gp_timer;
  
  // type cast base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_address;
      
  // clear timer mode 
  gp_timer->TAMR &= ~TIMER_TAMR_TAMR_M;
  
  // set mode
  gp_timer->TAMR |= TIMER_TAMR_TAMR_PERIOD;
    
  // set timer direction.  count_up: 0 for down, 1 for up.
  gp_timer->TAMR &= ~TIMER_TAMR_TACDIR;

  // set period
  gp_timer->TAILR = ticks-1;
  
  // set prescalar
  gp_timer->TAPR = prescalar;
  
  // set interrupt mask
  gp_timer->IMR |= TIMER_IMR_TATOIM;
  
  // clear any previous interrupts
  gp_timer->ICR = 0xFFFFFFFF;
  
  // enable interrupt
  NVIC_EnableIRQ(irq_num);
  
  // set priority
  NVIC_SetPriority(irq_num, priority);	
}
	
//*****************************************************************************
// initialize timers for blackjack game
//*****************************************************************************
bool timers_init(
  uint32_t  base1_address, 
  uint16_t  timer1A_ticks, 
  uint8_t   timer1A_prescalar,
  IRQn_Type timer1A_irq_num,
  uint32_t  timer1A_priority,
  uint32_t  base5_address,
  uint32_t  timer5A_ticks,
  uint16_t  timer5A_prescalar,
  IRQn_Type timer5A_irq_num,
  uint32_t  timer5A_priority
) {
	
	TIMER0_Type *gp1_timer;
	TIMER0_Type *gp5_timer;

	  // Verify the base address.
  if (!verify_base_addr(base1_address) || !verify_base_addr(base5_address))
  {
    return false;
  }
  
	// Turn on clock for timers
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R1;
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R5;

  // Wait for the timers to turn on
  while((SYSCTL->PRTIMER & (SYSCTL_PRTIMER_R0 | SYSCTL_PRTIMER_R1 | SYSCTL_PRTIMER_R2 | SYSCTL_PRTIMER_R3)) == 0) {};

  // Type cast the base address to a TIMER0_Type
  gp1_timer = (TIMER0_Type *)base1_address;
	gp5_timer = (TIMER0_Type *)base5_address;

    
  // Stop the timers
	gp1_timer->CTL &= ~( TIMER_CTL_TAEN | TIMER_CTL_TBEN);
	gp5_timer->CTL &= ~( TIMER_CTL_TAEN | TIMER_CTL_TBEN);
  
  // Set the timer to be a correct bit number
	gp1_timer->CFG = TIMER_CFG_32_BIT_TIMER;
  gp5_timer->CFG = TIMER_CFG_16_BIT;
    
 blackjack_timerA(base5_address,timer5A_ticks, timer5A_prescalar, timer5A_irq_num, timer5A_priority);
 blackjack_timerA(base1_address,timer1A_ticks, timer1A_prescalar, timer1A_irq_num, timer1A_priority);
		
  // Start the timers
	gp1_timer->CTL |= TIMER_CTL_TAEN;
	gp5_timer->CTL |= TIMER_CTL_TAEN;
  
  // Turn on the SysTick Timer
  // SysTick_Config(QUARTER_SEC);
  
  return true;
}



//*****************************************************************************
//*****************************************************************************
// Interrupt Service Routines
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
// Timer 1A Handler - Configured to 5000 ms
//*****************************************************************************
void TIMER1A_Handler(void)
{
  TIMER1->ICR |= TIMER_ICR_TATOCINT;
  ALERT_5000MS = true;
}


//*****************************************************************************
//	Timer 5A Handler - 1 ms - used for ADC
//*****************************************************************************
void TIMER5A_Handler(void)
{
  TIMER5->ICR |= TIMER_ICR_TATOCINT;
	
	// Start the ADC Conversion
	ADC0->PSSI |= ADC_PSSI_SS2;
  
  ALERT_1MS = true;
}
