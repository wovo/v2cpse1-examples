#include <iostream>
#include <array>

int main(){
   std::array< double , 9 > a;
   a[ 1 ] = 17.3;
   std:: cout << a[ 1 ] << "\n";
   a[ -1 ] = 0.0;
   std:: cout << a[ -1 ] << "\n";
   std:: cout << a.at( -1 ) << "\n";
}

