#include "hwlib.hpp"
#include <math.h>

namespace target = hwlib::target;

namespace hwlib {
   class pin_fixed {
   public:    
      pin_fixed( pin_out & pin, bool v ){
         pin.set( v );
      } 
   };
};

   // The OLED display is connected in a very funny way:
   // the I2C pins are reversed, and two GPIO pins are
   // (mis-) used as ground and power for the display.
   // This works, and makes it very easy to connect the LCD,
   // but don't take this as an advice to connect peripherals is this way
   // unless you know very well what you are doing.
class oled_buffered_d18_d21 {
   target::pin_oc scl, sda;
   hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
   target::pin_out pin_gnd, pin_vcc;
   hwlib::pin_fixed pin_gnd_fixed, pin_vcc_fixed;
   
public:
   hwlib::glcd_oled_buffered oled;

   oled_buffered_d18_d21():
      scl( target::pins::sda ),
      sda( target::pins::scl ),
      i2c_bus( scl, sda ),
      pin_gnd( target::pins::d18 ),
      pin_vcc( target::pins::d19 ),
      pin_gnd_fixed( pin_gnd, 0 ),
      pin_vcc_fixed( pin_vcc, 1 ),
      oled( i2c_bus, 0x3c )
   {}   
};

double pow( double g, int n ){
   return ( n < 1 ) ? 1 : g * pow( g, n - 1 ); 
}    

double fac( int n ){ 
   return ( n < 2 ) ? 1 : n * fac( n - 1 ); 
}

double taylor( double a, int n ){
    return ( n < 0 ) ? 0 : pow( a, n ) / fac( n ) - taylor( a, n - 2 );
}

double sin( double a ){
   return taylor( a, 13 );
}

double radians_from_degrees( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

int scaled_sine_from_degrees( int degrees, int scale ){
   return scale * sin( radians_from_degrees( degrees ));
}

int scaled_cosine_from_degrees( int degrees, int scale ){
   return scale * sin( radians_from_degrees( degrees - 90 ));
}

void clock_demo_draw_markers( 
   hwlib::glcd_oled_buffered & oled, 
   const hwlib::location & midpoint,
   int clock_radius,
   int circle_radius
){
   for( int angle = 0; angle < 360; angle += 30 ){
      hwlib::circle( 
         midpoint + hwlib::location( 
            scaled_sine_from_degrees( angle, clock_radius ),
            scaled_cosine_from_degrees( angle, clock_radius )
         ), 
         circle_radius 
      ).draw( oled );
   }   
   hwlib::circle( midpoint, circle_radius ).draw( oled );   
}   

void clock_demo_draw_line( 
   hwlib::glcd_oled_buffered & oled, 
   const hwlib::location & midpoint,
   int degrees,
   int radius
){  
   hwlib::line( 
      midpoint, 
      midpoint + hwlib::location(
         scaled_sine_from_degrees( degrees, radius ),
         scaled_cosine_from_degrees( degrees, radius )
   )).draw( oled );   
}

void clock_demo_draw(
   hwlib::glcd_oled_buffered & oled, 
   const hwlib::location & midpoint,
   int clock_radius,
   int time
){  
   oled.clear();   
   auto seconds = time % 60;
   auto minutes = ( time / 60 ) % 60;   
   auto hours   = ( time / ( 60 * 60 )) % 12;     
   clock_demo_draw_markers( oled, midpoint, clock_radius, 2 );
   clock_demo_draw_line( oled, midpoint, 6 * seconds, clock_radius -  3 );
   clock_demo_draw_line( oled, midpoint, 6 * minutes, clock_radius -  8 );
   clock_demo_draw_line( oled, midpoint, 30 * hours,  clock_radius - 14 );
   oled.flush();    
}

void clock_demo( 
   hwlib::glcd_oled_buffered & oled, 
   hwlib::pin_in & s,
   hwlib::pin_in & m,
   hwlib::pin_in & h
){
   const auto midpoint = hwlib::location( 64, 32 );
   const auto clock_radius = 25;
   int offset = 0;
   
   for(;;){
      offset = offset % ( 12 * 60 * 60 ); 
      auto time = offset + ( hwlib::now_us() / 1'000'000 );
      
      // hwlib::cout << time << " " << minutes << " " << seconds << "\n";
      
      clock_demo_draw( oled, midpoint, clock_radius, time );
      
      if( s.get() == 0 ){
         offset += 1;
      } else if( m.get() == 0 ){
         offset += 60;
      } else if( h.get() == 0 ){
         offset += 60 * 60;
      } else {
         hwlib::wait_ms( 200 );
      }   
   }    
}

int main( void ){	
   
   // kill the watchdog & wait for the PC console to start
   WDT->WDT_MR = WDT_MR_WDDIS;
   hwlib::wait_ms( 500 );   
   
   namespace target = hwlib::target;
   auto hw    = oled_buffered_d18_d21();
   auto sw_1  = target::pin_in( target::pins::d43 );
   auto sw_2  = target::pin_in( target::pins::d45 );
   auto sw_3  = target::pin_in( target::pins::d47 );

   clock_demo( hw.oled, sw_1, sw_2, sw_3 );
}

