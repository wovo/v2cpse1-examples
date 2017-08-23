#include "hwlib.hpp"
#include "coroutine.hpp"

class thread;
thread * first_thread = nullptr;
thread *current_thread;

class thread {
private:
   coroutine< 2048 > cor;
   long long wakeup_time;
   thread * next;
   
   static void trampoline(){        
      current_thread->main();
   }

public:   
   virtual void main() = 0;
   
   void wait( long long t ){
      wakeup_time = hwlib::now_us() + t;
      while( wakeup_time > hwlib::now_us() ){         
         current_thread = ( next != nullptr ) ? next : first_thread;         
         current_thread->cor.resume();       
      }         
   }
   
   thread():
      cor( trampoline ),
      wakeup_time( 0 ),
      next( first_thread )
   {
      first_thread = this;        
   }
   
   void start(){           
      current_thread = this;          
      cor.resume();
   }
   
};

void scheduler(){
   // what if there are zero threads?      
   first_thread->start();
}

class blinker : public thread {
private:
   hwlib::pin_out & led;
   long long d;
public:
   blinker( hwlib::pin_out & led, long long d ):
       led( led ), d( d )
   {}
   
   void main() override {        
      for(;;){        
         led.set( 1 );             
         wait( d );        
         led.set( 0 );             
         wait( d );
      }
   }
};

namespace target = hwlib::target;    
 
int main(){	        
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );   
   
   auto led1 = target::pin_out( target::pins::d42 );
   auto b1 = blinker( led1, 50'000 );
   (void) b1;
   
   auto led2 = target::pin_out( target::pins::d44 );
   auto b2 = blinker( led2, 165'000 );
   (void) b2;
    
   scheduler();
}