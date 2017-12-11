#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdbool.h>
#include <stdint.h>

#include "driver_defines.h"


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
bool gp_timer_config_32(uint32_t base_addr, uint32_t mode, bool count_up, bool enable_interrupts);


//*****************************************************************************
// Waits for 'ticks' number of clock cycles and then returns.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_wait(uint32_t base_addr, uint32_t ticks);

extern volatile int WATCHDOG_TESTING;

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
);



//*****************************************************************************
// Configure Timer A with specs outlined in project
//*****************************************************************************
static void blackjack_timerA(uint32_t base_address, uint32_t ticks, uint16_t prescalar, IRQn_Type irq_num, uint32_t priority); 

#endif
