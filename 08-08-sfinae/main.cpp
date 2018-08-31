#include <iostream>

// =====================================================

template< typename T >
struct is_floating {
};

template<>
struct is_floating< float > {
   typedef void marker;
};

template<>
struct is_floating< double >  {
   typedef void marker;
};

// =====================================================

template< typename T, typename M = void >
struct what_is_it {
   static constexpr const char * text 
      = "not a floating point type ...";
};

template< typename T >
struct what_is_it< T, typename is_floating< T >::marker > {
   static constexpr const char * text 
      = "a floating point type!!";
};

// =====================================================

int main( void ){	

   std::cout << "sfinae demo\n\n";
   
   std::cout 
      << "double : " 
      << what_is_it< double >::text 
      << "\n";
   std::cout 
      << "int    : " 
      << what_is_it< int >::text 
      << "\n";
   
}