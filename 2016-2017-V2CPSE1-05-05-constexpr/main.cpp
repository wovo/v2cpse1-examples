#include "hwlib.hpp"

constexpr double pow( double g, int n ){
   double result = 1;
   while( n > 0 ){
       result *= g;
       --n;
   }
   return result;
}

constexpr double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

constexpr double sin( double a ){
   return 
      a 
      - pow( a, 3 ) / fac( 3 ) 
      + pow( a, 5 ) / fac( 5 ) 
      - pow( a, 7 ) / fac( 7 )
      + pow( a, 9 ) / fac( 9 ) 
      - pow( a, 11 ) / fac( 11 ) 
      + pow( a, 13 ) / fac( 13 );
}

constexpr double radians_from_degrees( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

constexpr int scaled_sine_from_degrees( int degrees ){
   return 30 * ( 1.0 + sin( radians_from_degrees( degrees )));
}

int main( void ){	
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   hwlib::cout << "sine demo\n\n";
   
   constexpr const int table[ 36 ] = {
      scaled_sine_from_degrees(   0 ),
      scaled_sine_from_degrees(  10 ),
      scaled_sine_from_degrees(  20 ),
      scaled_sine_from_degrees(  30 ),
      scaled_sine_from_degrees(  40 ),
      scaled_sine_from_degrees(  50 ),
      scaled_sine_from_degrees(  60 ),
      scaled_sine_from_degrees(  70 ),
      scaled_sine_from_degrees(  80 ),
      scaled_sine_from_degrees(  90 ),
      scaled_sine_from_degrees( 100 ),
      scaled_sine_from_degrees( 110 ),
      scaled_sine_from_degrees( 120 ),
      scaled_sine_from_degrees( 130 ),
      scaled_sine_from_degrees( 140 ),
      scaled_sine_from_degrees( 150 ),
      scaled_sine_from_degrees( 160 ),
      scaled_sine_from_degrees( 170 ),
      scaled_sine_from_degrees( 180 ),
      scaled_sine_from_degrees( 190 ),
      scaled_sine_from_degrees( 200 ),
      scaled_sine_from_degrees( 210 ),
      scaled_sine_from_degrees( 220 ),
      scaled_sine_from_degrees( 230 ),
      scaled_sine_from_degrees( 240 ),
      scaled_sine_from_degrees( 250 ),
      scaled_sine_from_degrees( 260 ),
      scaled_sine_from_degrees( 270 ),
      scaled_sine_from_degrees( 280 ),
      scaled_sine_from_degrees( 290 ),
      scaled_sine_from_degrees( 300 ),
      scaled_sine_from_degrees( 310 ),
      scaled_sine_from_degrees( 320 ),
      scaled_sine_from_degrees( 330 ),
      scaled_sine_from_degrees( 340 ),
      scaled_sine_from_degrees( 350 )
   };
   
   for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
      for( int i = 0; i < table[ angle_degrees / 10 ]; ++i ){
         hwlib::cout << " ";
      }
      hwlib::cout << "*\n";
   } 
   
}