#include <iostream>

void print( int a[2] ){
   // for( auto x : a ) won't work because the size of a is not known
   
   for( unsigned int i = 0; i < 2; ++i ){
      std::cout << a[ i ] << "\n";
   }
}

int main(){
   int a2[ 2 ] = { 1, 2 };
   int a4[ 4 ] = { 5, 6, 7, 8 };
   print( a2 );
   print( a4 );
   
   int a1[ 1 ] = { 42 };
   print( a1 );   // undefined behaviour!
}

