#include "hwlib.hpp"

double pow( double g, int n ){
   double result = 1;
   while( n > 0 ){
       result *= g;
       --n;
   }
   return result;
}

double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

double sin( double a ){
   return 
      a 
      - pow( a, 3 ) / fac( 3 ) 
      + pow( a, 5 ) / fac( 5 ) 
      - pow( a, 7 ) / fac( 7 )
      + pow( a, 9 ) / fac( 9 ) 
      - pow( a, 11 ) / fac( 11 ) 
      + pow( a, 13 ) / fac( 13 );
}

double radians_from_degrees( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

int scaled_sine_from_degrees( int degrees ){
   return 30 * ( 1.0 + sin( radians_from_degrees( degrees )));
}

int main( void ){	
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   hwlib::cout << "sine demo\n\n";
   
   for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
      for( int i = 0; i < scaled_sine_from_degrees( angle_degrees ); ++i ){
         hwlib::cout << " ";
      }
      hwlib::cout << "*\n";
   } 
   
}