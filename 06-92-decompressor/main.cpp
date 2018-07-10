/*
#include <iostream>

template< int N, int M > 
class compresor {
private:   
   char buffer[ N ];
   int used;
   
public: 
   
   template< typename D, typename S >
   void compress( D destination, S source ){
      
      // fill the buffer
      used = 0;
	  char c;
      while( ( c = S()) != '\0' ){
         if( used == N ){
            //std::err << "buffer overflow";
            break;
         }
         if( c == '@' ){
            //std::err << "text contains @";
            break;
         }
         // ?? input[ input_used++ ] = c;
      }            
      
      // go through the buffer and compress
      for( int i = 0; i < used; ++i ){
         
      }
      
      // output the buffer
      for( int i = 0; i < used; ++i ){
         // ?? D( input[ i ] );   
      }      
   }
   
};

*/

int main( void ){	
   //auto f = fopen( "input.txt" );
   //compressor< 1 > c;
   //c.compress( std::cout.putc, f.getc );   
}