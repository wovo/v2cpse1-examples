#include <iostream>

template< typename T >
T max( const T & a, const T & b ){
   return ( a > b ) ? a : b;
}


int main( void ){	
	std::cout << max( 11, 12 ) << "\n";
	std::cout << max( 2.718, 3.14 ) << "\n";
	
	// this is a compiler error:
//	std::cout << max( "ab", "cd" ) << "\n";
}
