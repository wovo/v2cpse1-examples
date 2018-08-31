#include <iostream>
#include <array>

int main(){
   std::array< int, 10 > int_10;
   std::cout << "size of int_10 = " << sizeof( int_10 ) << "\n";
   
   std::array< bool, 10 > bool_10;
   std::cout << "size of bool_10 = " << sizeof( bool_10 ) << "\n";

}
