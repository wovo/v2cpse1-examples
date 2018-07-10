#include "hwlib.hpp"

hwlib::pin_out * x;
hwlib::pin_in * y;
hwlib::pin_in * z;

void my_wait_us( uint32_t t ){
   auto end = hwlib::now_us() + t;
   while( hwlib::now_us() < end ){
      x->set( y->get() && z->get() );
   }
}
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
    
   namespace target = hwlib::target;       
   auto led   = target::pin_out( target::pins::d42 );
   auto pin_x = target::pin_out( target::pins::d44 );
   auto pin_y = target::pin_in( target::pins::d43 );
   auto pin_z = target::pin_in( target::pins::d45 );
   
   x = & pin_x;
   y = & pin_y;
   z = & pin_z;

   for(;;){
      led.set( 1 );
      my_wait_us( 500'000 );
      led.set( 0 );
      my_wait_us( 500'000 );
   }
}