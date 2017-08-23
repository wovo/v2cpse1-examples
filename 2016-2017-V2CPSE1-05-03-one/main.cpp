#include "hwlib.hpp"
#include <math.h>

int main( void ){	
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   hwlib::cout << "sine demo\n\n";
   
   volatile double a = 2.00;
   a = sin( a );
   
}

