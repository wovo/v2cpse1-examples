#include "hwlib.hpp"

hwlib::pin_out * led1;
hwlib::pin_out * led2;

void led1_update(){
   static long long int last_toggle = 0;
   static bool level = 0;
   auto t = hwlib::now_us();
   if( t - last_toggle > 50'000 ){
      level = ! level;
      led1->set( level );
      last_toggle = t;
   }
}

 
void led2_update(){
   static long long int last_toggle = 0;
   static bool level = 0;
   auto t = hwlib::now_us();
   if( t - last_toggle > 165'000 ){
      level = ! level;
      led2->set( level );
      last_toggle = t;
   }
}

 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
    
   namespace target = hwlib::target;       
   auto led_1 = target::pin_out( target::pins::d42 );
   auto led_2 = target::pin_out( target::pins::d44 );
   
   led1 = & led_1;
   led2 = & led_2;

   for(;;){
      led1_update();
      led2_update();
   }
}