#include "hwlib.hpp"

template< int N >        
struct loop_unrolled{
   template< typename Body >
   loop_unrolled( const Body & body ){
      body();
      loop_unrolled< N - 1 > dummy( body );
   }      
};

template<>
struct loop_unrolled< 0 >{
   template< typename Body >
   loop_unrolled( const Body & body ){}      
};

template< int N, bool unroll = false, typename T >
void loop( const T & body ){
   if( unroll ){
      loop_unrolled< N >( body );
   } else {         
      for( int i = 0; i < N; ++i ){
         body();
      }
   }   
}

int main( void ){	
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   hwlib::cout << "loop demo\n\n";
   
   int n = 0;
   
   loop< 10 >( [&]() __attribute__ ((always_inline)) {
      hwlib::cout << ++n << "\n";
   });
   
}