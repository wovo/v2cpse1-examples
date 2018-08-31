#include <iostream>
#include <array>

template< typename T, int N >
class my_array {
public:
   T operator[]( int i ) const {
      check( i );
      return a[ i ];
   }

   T & operator[]( int i ){
      check( i );
      return a[ i ];
   }

private:
   std::array< T, N > a;

   void check( int i ){
      if (( i < 0 ) || ( i >= N )){
         std::cout << "HELP!\n";
         while( true ){}
      }
   }

};

int main(){
   my_array< double , 9 > a;
   a[ 1 ] = 17.3;
   std:: cout << a[ 1 ] << "\n";
   a[ -1 ] = 0.0;
}
