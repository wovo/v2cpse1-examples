#include <iostream>

template< int N >
struct is_even {
   static constexpr bool value = is_even< N - 2 >::value;
};

template<>
struct is_even< 0 >{
   static constexpr bool value = true;
};

template<>
struct is_even< 1 >{
   static constexpr bool value = false;
};

int main( void ){	
   
   const auto x = 5;
   const auto y = 90;
   
   std::cout << x << " is even? " << is_even< x >::value << "\n";
   std::cout << y << " is even? " << is_even< y >::value << "\n";
   
}