#include <iostream>

template< typename T, unsigned int N >
class array {
public:
   T operator[]( int i ) const {
      return a[ i ];
   }

private:
   T a[N];

};

template< unsigned int N >
class array< bool, N > {
public:
   bool operator[]( int i ) const {
      return ( a[ i / 8 ] >> ( i % 8 ) ) & 0x01;
   }

private:
   unsigned char a[ ( N + 7 ) / 8 ];

};


int main(){
   array< int, 10 > int_10;
   std::cout << "size of int_10 = " << sizeof( int_10 ) << "\n";
   
   array< bool, 10 > bool_10;
   std::cout << "size of bool_10 = " << sizeof( bool_10 ) << "\n";
}

