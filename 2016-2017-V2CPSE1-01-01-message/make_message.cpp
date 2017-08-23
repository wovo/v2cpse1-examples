#include <iostream>

int main( int argc, char **argv ){
   std::cout 
      << "#include \"message.hpp\"\n"
      << "const char * " << argv[ 1 ] << "(){\n"
      << "   return \"" << argv[ 2 ] << "\";\n"
      << "}\n";
}