#include "hwlib.hpp"

// ===========================================================================
//
// standard notes
//
// ===========================================================================

class note {
public:
   const int frequency;
   const int duration;
   
   // from https://www.seventhstring.com/resources/notefrequencies.html
   static const int A4  = 440;
   static const int A4s = 466;
   static const int B4  = 494;
   static const int C5  = 523;
   static const int C5s = 554;
   static const int D5  = 587;
   static const int D5s = 622;
   static const int E5  = 659;
   static const int F5  = 698;
   static const int F5s = 740;
   static const int G5  = 784;
   static const int G5s = 830;
   static const int A5  = 880;
   static const int A5s = 932;
   static const int B5  = 987;
   
   static const int dF = 1'000'000;
   static const int dH = dF / 2;
   static const int dQ = dF / 4;
};


// ===========================================================================
//
// interface for a note player
//
// ===========================================================================

class player {
public:   
   virtual void play( const note & n ) = 0;
};


// ===========================================================================
//
// simple note player for a speaker connected to a GPIO pin
//
// ===========================================================================

class lsp_player : public player {
private:   
   hwlib::pin_out & lsp;
public: 
   lsp_player( hwlib::pin_out & lsp ):
      lsp( lsp )
   {}
   
   void play( const note & n ) override {
      if( n.frequency == 0 ){
         hwlib::wait_us( n.duration );
      } else {
         auto end = hwlib::now_us() + n.duration;
         auto half_period = 1'000'000 / ( 2 * n.frequency );    
         while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
         }
      }     
   }
};


// ===========================================================================
//
// rtttl string player
//
// ===========================================================================

bool is_digit( char c ){ return ( c >= '0' ) && ( c <= '9' ); }
bool is_lowercase( char c ){ return ( c >= 'a' ) && ( c <= 'z' ); }

class melody {
public:
   virtual void play( player & p );
};

class fur_elise : public melody {
public:
   void play( player & p ){
      p.play( note{ note::E5,  note::dQ } );
      p.play( note{ note::D5s, note::dQ } );
      p.play( note{ note::E5,  note::dQ } ); 
      p.play( note{ note::D5s, note::dQ } ); 
      p.play( note{ note::E5,  note::dQ } );
      p.play( note{ note::B4,  note::dQ } );
      p.play( note{ note::D5,  note::dQ } );
      p.play( note{ note::C5,  note::dQ } );
      p.play( note{ note::A4,  note::dH } );
    }
};

int frequencies[] = { 440, 494, 523, 587, 659, 698, 784 };

void play(player & lsp, const char *s ){
   int def_duration = 4, def_octave = 6, value;
   int duration, octave, frequency;
   int state = 0;
   char def;
   bool dot;
   for( const char * p = s; state >= 0; p++ ){
      const char c = *p;
      switch(state ){
             
         // title 
         case 0:
            if( c == ':' ){
               state = 1;
            } else {
               hwlib::cout << c;
            } 
            break;
               
          // defaults  
          case 1:
            if( c == ':' ){
               state = 3;
            } if( is_lowercase( c )){
               def = c;
               value = 0;
               state = 2;
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            } 
            break;   

         // defaults, letter stored in def
         case 2:
            if( c == '=' ){
               // ignore the =
            } else if( is_digit( c )){
               value = ( 10 * value ) + ( c - '0' );
            } else if(( c == ':' ) || ( c == ',' )) {
               if( def == 'o'){
                  def_octave = value;
               } else if( def == 'd' ){
                  def_duration = value;
               } else if( def == 'b' ){
                  // ignore
               } else {
                  HWLIB_TRACE << "def=[" << def << "]";
               }   
               state = ( c == ':' ) ? 3 : 1;
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }
            break;
            
         // note start, set defaults
         case 3:  
            duration = def_duration;
            octave = def_octave;
            state = 4;
            dot = 0;
            // fallthrough!!
               
         // duration 1  
         case 4:   
            if( c == '\0' ){
               state = -1;
               break;
            } else if( is_digit( c )){
               duration = c -'0';
               state = 5;
               break;
            }            
            // fallthrough!
            
         // duration 2 
         case 5:   
            if( is_digit( c )){
               duration = ( duration * 10 ) + ( c -'0' );
               state = 6;
               break;
            }            
            // fallthrough!
               
         // note letter   
         case 6:   
            if( is_lowercase( c )){
               if( c == 'p' ){
                   frequency = 0;
               } else {
                  frequency = frequencies[ c - 'a' ]; 
               }   
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }   
            state = 7;
            break;
               
         // optional #   
         case 7:   
            if( c == '#' ){
               frequency = 10595 * frequency / 10000;
               state = 8;
               break;
            }
            // fallthrough!

         // optional .
         case 8:
            if( c == '.' ){
               dot = 1;
               state = 9;
               break;
            }            
            // fallthrough!

         case 9:
            if( is_digit( c )){
               octave = c - '0';
               state = 10;
               break;
            }        
            // fallthrough!
               
         case 10:   
            if( ( c == ',' ) || ( c == '\0') ){
               while( octave > 5 ){ --octave; frequency *= 2; }
               duration = 2'000'000 / duration;
               if( dot ){
                  duration = 3 * duration / 2;
               }

               lsp.play( note{ frequency, duration } ); 
               state = 4;
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }
            if( c == '\0' ){
               state = -1;
            }
            break;            
      }         
   }
   HWLIB_TRACE << "done";
}   
   
   
// ===========================================================================
//
// main: play an rtttl string
//
// ===========================================================================   

int main( void ){	
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;   
    
      // wait for the PC console to start
   hwlib::wait_ms( 500 );

   auto lsp = target::pin_out( target::pins::d7 );
   auto p = lsp_player( lsp );
   //auto fe = fur_elise();
   //fe.play( p );
   // play( p, "we-rock:d=4,o=6,b=140:32d#.5,32d.5,32d#.5,8f#.5,32g#.5,32f#.5,32f.5,32f#.5,8a#.5,16b5,16a#5,16a5,16a#5,16f6,16d#6,16d6,16d#6,16f6,16d#6,16d6,16d#6,8f#.6,8d#6,8f#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8c6,4a#5,16f5,32d#5,16d5,16d#5,4f#5,16g#5,16f#5,16f5,16f#5,4a#5,16b5,16a#5,16a5,16a#5,16f6,16d#6,16d6,16d#6,16f6,16d#6,16d6,16d#6,4f#6,8d#6,8f#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8d#6,32c#6,32d#6,16f6,8d#6,8c#6,8c6,4a#5,8a#5,8b5,8c#6,8c#6,16d#6,16c#6,16b5," );
   play( p, "Beatles Let It Be:d=4,o=5,b=100:16e6,8d6,c6,16e6,8g6,8a6,8g.6,16g6,8g6,8e6,16d6,8c6,16a,8g,e.6,p,8e6,16e6,8f.6,8e6,8e6,8d6,16p,16e6,16d6,8d6,2c.6" );
}
