#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

template< typename C, typename D >
class resource {
private:
   D destruct;   
public:
   resource ( C create, D destruct ):
      destruct( destruct )
   {
      create();
   }
   
   ~resource(){
      destruct();
   }
};

/* would be needed before C++17
template< typename C, typename D >
resource< C, D > make_resource( C create, D destruct ){
   return resource( C, D >( create, destruct );
}
*/

class logger : public rtos::task<> {
private:
   rtos::mutex & cout_mutex;
   const char * text;
   rtos::clock clock;
public:
   logger( rtos::mutex & cout_mutex, const char * text ): 
      cout_mutex( cout_mutex ), 
      text( text ), 
      clock( this, 1'000 * rtos::ms, "clock" )
   {}
   
   void print( int n, const char *s ){
      auto exclusive_use = resource(
         [&](){ cout_mutex.wait(); },
         [&](){ cout_mutex.signal(); }
      );   
      hwlib::cout << n;
      for( auto p = text; *p != '\0'; ++p ){
         hwlib::cout << *p;
         hwlib::wait_ms( 10 );
      }
   }
   
   void main() override {        
      for( int n = 0; ; ++n ){        
         print( n, text );
         wait( clock );        
      }
   }
};

int main( void ){	
   
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );
   
   rtos::mutex cout_mutex( "cout_mutex" );
   auto t1 = logger( cout_mutex, " Hello\n" );
   auto t2 = logger( cout_mutex, " =========\n" );
   rtos::run();
   
}