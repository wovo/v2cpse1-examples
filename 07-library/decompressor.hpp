#ifndef _DECOMPPRESSOR_HPP
#define _DECOMPRESSOR_HPP

#include <array>
#include "match.hpp"

class lz_decompressor {
private:

   static const auto buffer_length = 100;
   std::array< char, buffer_length > buffer;
   
   template< typename F >
   void add( char c, F write ){
      write( c );
      for( int i = buffer_length; i > 0; --i ){
         buffer[ i ] = buffer[ i - 1 ];
      }
      buffer[ 0 ] = c;
   }

   template< typename F >   
   void add( match m, F write ){
      while( m.length-- ){
         add( buffer[ m.offset ], write );
      }
   }

   
public: 

   template< typename S, typename D >
   void decompress( S read, D write ){
      for(;;){
         auto c = read();
         if( c == '\0' ){
            return;
         }
         if( c != '@' ){
            add( c, write );
         } else {
            int offset = read() - '0';
            int length = read() - '0';
            add( match( offset, length ), write );
         }
      }         
   }
   
};


#endif