#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class mutex_resource {
private:   
   rtos::mutex & mutex;
   
public:
   mutex_resource( rtos::mutex & mutex ):
      mutex( mutex )
   {
      HWLIB_TRACE << "claim";
      mutex.wait();
   }
   
   ~mutex_resource(){
      HWLIB_TRACE << "release";
      mutex.signal();
   }
};

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
      auto exclusive_use = mutex_resource( cout_mutex );
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
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   hwlib::wait_ms( 500 );
   
   rtos::mutex cout_mutex( "cout_mutex" );
   auto t1 = logger( cout_mutex, " Hello\n" );
   auto t2 = logger( cout_mutex, " =========\n" );
   rtos::run();
   
}