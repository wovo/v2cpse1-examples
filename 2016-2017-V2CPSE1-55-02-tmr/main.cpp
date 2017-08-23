#include "hwlib.hpp"

volatile int global_counter;

extern "C" void Int27_Handler(){
   //(void)REG_TC0_SR0; 
   (void)TC0->TC_CHANNEL[0].TC_SR;
   global_counter++;   
}

int main( void ){	
   global_counter = 0;
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   hwlib::wait_ms( 500 );
   
   // enable the clock to the TC0 (peripheral # 27)
   PMC->PMC_PCER0 = 1 << ID_TC0;

   // configure TC0 channel 0 for periodic interrupts
   TC0->TC_CHANNEL[0].TC_CMR =  TC_CMR_WAVE | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR; 
   
	//Set compare values 
	TC0->TC_CHANNEL[0].TC_RC = 1166;
   TC0->TC_CHANNEL[0].TC_RA = TC0->TC_CHANNEL[0].TC_RC / 2;
	
	// Enables the clock a software trigger is performed: 
   // the counter is reset and the clock is started 
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
   
   // enable interrupt generation by the counter
   TC0->TC_CHANNEL[0].TC_IER = 1 << 2;
   
   // enable interrupt in the NVIC
   NVIC_EnableIRQ( TC0_IRQn );

   int t = 0;
   for(;;){
      HWLIB_TRACE << ++t << " global_counter=" << global_counter;
      hwlib::wait_ms( 1'000 );
   }
}

