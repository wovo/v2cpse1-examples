#include <iostream>

template< typename T >
T max( const T & a, const T & b ){
   return ( a > b ) ? a : b;
}


int main( void ){	
   int a, b;
	std::cout << max( 11, 12 ) << "\n";
	std::cout << max( 2.718, 3.14 ) << "\n";
	std::cout << max( "ab", "cd" ) << "\n";
}
