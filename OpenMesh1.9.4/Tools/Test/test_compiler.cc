#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <OpenMesh/Core/System/compiler.h>

#define SIZE(T) \
   std::cout << std::setw( 4) << typeid(T).name() \
             << std::setw(20) << #T << ": " << sizeof(T) << std::endl

int main(int argc, char *argv[])
{
  std::cout << "Compiler: " << OM_CC << std::endl;
  std::cout << " Version: " << OM_CC_VERSION << std::endl;

  std::cout << std::endl;
  std::cout << "size of primitives:\n";

  SIZE(bool);
  SIZE(char);
  SIZE(unsigned char);
  SIZE(short);
  SIZE(unsigned short);
  SIZE(int);
  SIZE(unsigned int);
  SIZE(long);
  SIZE(unsigned long);
  SIZE(long long);
  SIZE(unsigned long long);
  SIZE(float);
  SIZE(double);
  SIZE(long double);
  return 0;
}
