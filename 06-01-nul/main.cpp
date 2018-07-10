#include <iostream>

template< int N >
struct is_nul {
   static constexpr const char * text = "is not nul";
};

template<>
struct is_nul< 0 >{
   static constexpr const char * text = "is nul";
};

int main(){	
   
   const auto x = 0;
   const auto y = 1;
   
   std::cout << x << " " << is_nul< x >::text << "\n";
   std::cout << y << " " << is_nul< y >::text << "\n";
   
}
   
