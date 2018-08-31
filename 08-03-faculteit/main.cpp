#include <iostream>

template< int N >
struct fac {
   static constexpr int value = N * fac< N - 1 >::value;
};

template<>
struct fac< 0 >{
   static constexpr int value = 1;
};

int main( void ){	
   
   const auto x = 12;
   
   std::cout << "fac< " << x << " >::value = " << fac< x >::value << "\n";
   
}