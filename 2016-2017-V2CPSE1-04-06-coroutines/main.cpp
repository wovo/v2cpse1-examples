#include "hwlib.hpp"
#include "coroutine.hpp"

namespace target = hwlib::target;    

coroutine< 2048 > * c1, * c2;

void wait_us( long long int t, coroutine< 2048 > * other ){
   auto end = hwlib::now_us() + t;
   while( hwlib::now_us() < end ){
      other->resume();
   }
}
 
void body_1(){
   auto led = target::pin_out( target::pins::d42 );
   for(;;){
      led.set( 1 );
      wait_us( 50'000, c2 );
      led.set( 0 );
      wait_us( 50'000, c2 );
   }
}

void body_2(){
   auto led = target::pin_out( target::pins::d44 );
   for(;;){
      led.set( 1 );
      wait_us( 165'000, c1 );
      led.set( 0 );
      wait_us( 165'000, c1 );
   }
} 
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto coroutine_1 = coroutine< 2048 >( body_1 );
   auto coroutine_2 = coroutine< 2048 >( body_2 );
   c1 = & coroutine_1;
   c2 = & coroutine_2;
    
   c1->resume();
}