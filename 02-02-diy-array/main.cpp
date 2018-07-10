#include <iostream>

template< typename T, unsigned int N >
class array {
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
   T a[N];

   void check( int i ){
      if (( i < 0 ) || ( i >= N )){
         std::cout << "HELP!\n";
         while( true ){}
      }
   }

};

int main(){
   array< double , 9 > a;
   a[ 1 ] = 17.3;
   std:: cout << a[ 1 ] << "\n";
   a[ -1 ] = 0.0;
}
