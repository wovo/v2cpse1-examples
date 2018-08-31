#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class logger : public rtos::task<> {
private:
   const char * text;
   rtos::clock clock;
public:
   logger( const char * text ): 
      text( text ), 
      clock( this, 1'000 * rtos::ms, "clock" )
   {}
   
   void print( int n, const char *s ){
      hwlib::cout << n;
      for( auto p = text; *p != '\0'; ++p ){
         hwlib::cout << *p;
         hwlib::wait_ms( 10 );
      }
   }
   
   void main() override {        
      for( int n = 0; ; ++n ){        
         print( n, text );
         wait( clock );        
      }
   }
};


int main( void ){	
   
   // kill the watchdog, wait for the PC to start the terminal
   WDT->WDT_MR = WDT_MR_WDDIS;
   hwlib::wait_ms( 1000 );
   
   auto t1 = logger( " Hello\n" );
   auto t2 = logger( " =========\n" );
   rtos::run();
   
}