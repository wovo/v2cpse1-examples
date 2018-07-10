#include <iostream>

template< typename T, unsigned int N >
class array {
public:
   T operator[]( int i ) const {
      return a[ i ];
   }

   T operator[]( int i ) {
      return a[ i ];
   }

private:
   T a[N];

};

template< unsigned int N >
class array< bool, N > {
public:
   bool get( int i ) const {
      return (( a[ i / 8 ] >> ( i % 8 ) ) & 0x01 ) != 0;
   }
   
   void set( int i, bool b ){
      if( b ){
         a[ i / 8 ] |= ( 0x01 << ( i % 8 ));
      } else {
         a[ i / 8 ] &= ~ ( 0x01 << ( i % 8 ));         
      }
   }
   
   bool operator[]( int i ) const {
      return get( i );
   }
   
   class reference {
   private:
      array & subject;
      int n;
   public:   
      reference( array & subject, int n ): subject( subject ), n( n ){}
      
      reference & operator=( bool b ){
         subject.set( n, b );
         return *this;
      }
      
      operator bool() const { 
         return subject.get(n ); 
      }
      
      reference & operator=( const reference & bit ){
         subject.set( n, bit );
         return *this;
      }
      
   };
   
   reference operator[]( int i ){
      return reference( *this, i );
   }   
   
   friend std::ostream & operator<<( std::ostream & lhs, const array & a ){
      char c = '['  ;
      for( int i = 0; i < N; ++i ){
         lhs << c << a.get( i );
         c = ',';
      }      
      return lhs << "]";
   } 
   
private:
   unsigned char a[ ( N + 7 ) / 8 ];
};


int main(){
   array< bool, 10 > b;
   for( int i = 0; i < 10; ++i ){ 
      b[ i ] = ( ( i % 3 ) == 0 );
   }
   
   std::cout << b << "\n";

   for( int i = 0; i < 10; ++i ){ 
      std::cout << "b[" << i << "]=" << b.get( i ) << "\n";
   }      
   
   b[ 0 ] = bool( b[ 1 ] );
   array< bool, 10 >::reference rhs = b.operator[]( 1 );
   bool value = rhs;
   array< bool, 10 >::reference lhs = b.operator[]( 0 );
   lhs.operator=( value );

   // this requires the reference & operator=( const reference & bit )
   b[ 0 ] = b[ 1 ];

}

