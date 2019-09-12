#include "hwlib.hpp"
#include "message.hpp"

int main( void ){	
   
   namespace target = hwlib::target;   
    
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   hwlib::cout << splash();
}
