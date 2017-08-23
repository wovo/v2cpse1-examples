#include "hwlib.hpp"

template< typename T, unsigned int N >
class array {
public:
   T operator[]( int i ) const {
      return a[ i ];
   }

private:
   T a[N];

};

int main( void ){	
   global_counter1 = global_counter2 = 0;
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC terminal to start
   hwlib::wait_ms( 500 );
   
   start_interrupts();
   
   hwlib::wait_us( 1'000 );
   for(;;){
      increment_global_counters();
      hwlib::wait_us( 1'000 );
      if( interrupts > 100'000 ){
         HWLIB_TRACE << "interrupts=" << interrupts;
         for(;;);
      }
   }
}

