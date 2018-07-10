#include <iostream>

void f();
extern char *m;

int main(){    
  f();
  std::cout << m;
}
