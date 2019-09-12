#include "hwlib.hpp"

int main( void ){	
   
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );  

   hwlib::cout << "sine demo\n\n";
   
   const int table[ 36 ] = {
      30, // 0
      35, // 10
      40, // 20
      44, // 30
      49, // 40
      52, // 50
      55, // 60
      58, // 70
      59, // 80
      59, // 90
      59, // 100
      58, // 110
      55, // 120
      53, // 130
      49, // 140
      45, // 150
      40, // 160
      35, // 170
      30, // 180
      24, // 190
      19, // 200
      15, // 210
      10, // 220
       7, // 230
       4, // 240
       1, // 250
       0, // 260
       0, // 270
       0, // 280
       2, // 290
       5, // 300
       9, // 310
      13, // 320
      20, // 330
      27, // 340
      36  // 350
   };
   
   for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
      for( int i = 0; i < table[ angle_degrees / 10 ]; ++i ){
         hwlib::cout << " ";
      }
      hwlib::cout << "*\n";
   } 
   
}