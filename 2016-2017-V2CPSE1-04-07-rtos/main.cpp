#include "hwlib.hpp"
#include "rtos.hpp"

class blinker : public rtos::task<> {
private:
   hwlib::pin_out & led;
   long long d;
public:
   blinker( hwlib::pin_out & led, long long d, const char * name ):
       task( name ), led( led ), d( d )
   {}
   
   void main() override {        
      for(;;){        
         led.set( 1 );             
         hwlib::wait_ms( d );        
         led.set( 0 );             
         hwlib::wait_ms( d );
      }
   }
};

class debugger : public rtos::task<> {
   hwlib::pin_in & button;      
public:
   debugger( hwlib::pin_in & button ):
       task( "debugger" ), button( button )
   {}
   
   void main() override {        
      for(;;){                    
         hwlib::wait_ms( 10 );        
         if( button.get() == 0 ){
            rtos::print( hwlib::cout );
            hwlib::wait_ms( 2'000 );
         }
      }
   }
};


namespace target = hwlib::target;    
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   
   
   auto led1 = target::pin_out( target::pins::d42 );
   auto b1 = blinker( led1, 50, "blink led1" );
   (void) b1;
   
   auto led2 = target::pin_out( target::pins::d44 );
   auto b2 = blinker( led2, 165,"blink led2" );
   (void) b2;
    
   auto button = target::pin_in( target::pins::d43 );
   auto log = debugger( button );
   (void) log;
    
   rtos::run();
}

