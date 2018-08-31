#include <iostream>

int max1( int a, int b ){
   if( a > b ){
      return a;
   } else {
      return b;
   }
}

int max2( int a, int b ){
   return ( a > b ) ? a : b;
}

int main( void ){	
	std::cout << max1( 11, 12 ) << "\n";
	std::cout << max2( 11, 12 ) << "\n";
}
