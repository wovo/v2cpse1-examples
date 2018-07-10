#include "hwlib.hpp"
#include "coroutine.hpp"

namespace target = hwlib::target;    

coroutine<> * cor_ptr;

void wait_us_cor( long long int t ){
   auto end = hwlib::now_us() + t;
   while( hwlib::now_us() < end ){
      coroutine<>::resume_main();
   }
}
 
void cor(){
   auto led = target::pin_out( target::pins::d42 );
   for(;;){
      led.set( 1 );
      wait_us_cor( 50'000 );
      led.set( 0 );
      wait_us_cor( 50'000 );
   }
}

void wait_us_main( long long int t ){
   auto end = hwlib::now_us() + t;
   while( hwlib::now_us() < end ){
      cor_ptr->resume();
   }
}
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto coroutine_1 = coroutine< 2048 >( cor );
   cor_ptr = & coroutine_1;
   
   auto led = target::pin_out( target::pins::d44 );
   for(;;){
      led.set( 1 );
      wait_us_main( 165'000 );
      led.set( 0 );
      wait_us_main( 165'000 );
   }
}