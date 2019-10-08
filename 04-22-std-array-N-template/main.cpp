#include <iostream>
#include <array>

template< long unsigned int N >
void print( const std::array< int, N > & a  ){
   for( const auto & x : a ){
      std::cout << x << "\n";
   }
}

int main(){
   std::array< int, 2 > a2 = { 1, 2 };
   std::array< int, 4 > a4 = { 5, 6, 7, 8 };
   print( a2 );
   print( a4 );
}

