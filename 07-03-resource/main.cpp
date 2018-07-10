#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

template< typename C, typename D >
class resource_class {
private:
   D destruct;   
public:
   resource_class( C create, D destruct ):
      destruct( destruct )
   {
      create();
   }
   
   ~resource_class(){
      destruct();
   }
};

template< typename C, typename D >
resource_class< C, D > resource( C create, D destruct ){
   return resource_class< C, D >( create, destruct );
}

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
         sleep( 10 * rtos::ms );
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
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   hwlib::wait_ms( 500 );
   
   rtos::mutex cout_mutex( "cout_mutex" );
   auto t1 = logger( cout_mutex, " Hello\n" );
   auto t2 = logger( cout_mutex, " =========\n" );
   rtos::run();
   
}