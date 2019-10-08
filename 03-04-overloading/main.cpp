void f( double x ){ }
void f( char x ){ } // overloading, not a re-definition

int main( void ){
   f( 3.14 );          
   f( '?' );
//   f( 12 ); // ambiguous
}
