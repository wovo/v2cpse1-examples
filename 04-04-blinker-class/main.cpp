#include "hwlib.hpp"

class blinker {
private:
   hwlib::pin_out & led;
   long long interval, last_toggle;
   bool led_state;  
   
public:
   blinker( hwlib::pin_out & led, long long interval ):
      led( led ), interval( interval ),
      last_toggle( 0 ), led_state( false )
   {}

   void update( const long long now ){ 
      if( now - last_toggle > interval ){
         led.set( led_state = ! led_state );
         last_toggle = now;
      }
   }
};

int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
    
   namespace target = hwlib::target;       
   auto led1 = target::pin_out( target::pins::d42 );
   auto led2 = target::pin_out( target::pins::d44 );
   
   auto b1 = blinker( led1, 50'000 );
   auto b2 = blinker( led2, 165'000 );

   for(;;){
      auto now = hwlib::now_us();
      b1.update( now );
      b2.update( now );
   }
}