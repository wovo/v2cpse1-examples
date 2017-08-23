#include "hwlib.hpp"

template< int N, typename T >
void loop( const T & body ){
   for( int i = 0; i < N; ++i ){
      body();
   }
}

int main( void ){	
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   hwlib::cout << "loop demo\n\n";
   
   int n = 0;
   
   loop< 10 >( [&](){
      hwlib::cout << ++n << "\n";
   });
   
}