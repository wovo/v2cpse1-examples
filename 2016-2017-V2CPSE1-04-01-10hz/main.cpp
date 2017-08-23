#include "hwlib.hpp"

void wait_us( long long int t ){
   auto end = hwlib::now_us() + t;
   while( hwlib::now_us() < end ){
      // waste time
   }
}
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
    
   namespace target = hwlib::target;       
   auto led = target::pin_out( target::pins::d42 );

   for(;;){
      led.set( 1 );
      wait_us( 50'000 );
      led.set( 0 );
      wait_us( 50'000 );
   }
}

