#ifndef _MATCH_HPP
#define _MATCH_HPP

#include <iostream>

// a match found in the previously processed characters:
// the start offset (negative), and the number of characters
struct match {
   
   int offset;
   int length;
   
   match( int offset = 0, int length = 0 ): 
      offset( offset ), length( length ) {}
      
   friend std::ostream & operator<<( std::ostream & lhs, const match & m ){
      return lhs << "[" << m.offset << ";" << m.length << "]";
   }
   
   bool operator<( const match & rhs ) const {
      return length < rhs.length;
   }
};

#endif