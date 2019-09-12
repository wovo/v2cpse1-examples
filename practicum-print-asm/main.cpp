#include "hwlib.hpp"

void uart_put_char( char c ){
   hwlib::cout << c;
}

void print_asciz( const char * s ){
   while( *s != '\0'){
      uart_put_char( *s );
      ++s;
   }
}

void application(){
   print_asciz( "Hello world, the ANSWER is 42! @[]`{}~\n" );	
}

int main( void ){	
   
   namespace target = hwlib::target;   
    
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}