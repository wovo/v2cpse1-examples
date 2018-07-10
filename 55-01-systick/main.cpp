#include "hwlib.hpp"

volatile int global_counter;

extern "C" void SysTick_Handler(){
   global_counter++; 
}

int main( void ){	
   global_counter = 0;
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // this starts the systick timer
   hwlib::wait_ms( 500 );
   
   // enable the systick interrupt
   SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

   int t = 0;
   for(;;){
      HWLIB_TRACE << ++t << " global_counter= " << global_counter;
      hwlib::wait_ms( 1'000 );
   }
}

