#include "hwlib.hpp"
#include <math.h>

int main( void ){	
   
   // wait for the PC console to start
   hwlib::wait_ms( 2000 ); 

   hwlib::cout << "sine demo\n\n";
   
   volatile double a = 2.00;
   a = sin( a );
   
}

