// ============================================================================
// $Id: test_StoreRestore.cc,v 1.1.1.1 2006-03-22 20:12:01 marinov Exp $
// ----------------------------------------------------------------------------

#include <OpenMesh/Core/System/config.h>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#if defined(OM_CC_MIPS)
#  include <ctype.h>
#  include <limits.h>
#else
#  include <cctype>
#  include <limits>
#endif
#include <OpenMesh/Core/IO/BinaryHelper.hh>
#include <OpenMesh/Tools/Utils/TestingFramework.hh>

// ----------------------------------------------------------------------------

using OpenMesh::Utils::TestingFramework;


// ----------------------------------------------------------------------------

template<typename V>
struct test_reverse_byte_order : public TestingFramework::TestFunc
{
   typedef V                          value_type;
   typedef TestingFramework::TestFunc Inherited;
   typedef test_reverse_byte_order Self;
   
   value_type val_a_;
   value_type val_b_;

   test_reverse_byte_order( TestingFramework& _test, const std::string& _n,
                            V _val_a, V _val_b)
         : Inherited( _test, _n ),
           val_a_(_val_a), val_b_(_val_b)
   { }
   
   test_reverse_byte_order( Self& _cpy ) : TestingFramework::TestFunc(_cpy) { }
   
   ~test_reverse_byte_order()
   { }
   
//    bool equal(value_type a, value_type b)
//    {
//      return a == b;
//    }

   void write( std::ostream& ostr, value_type val )
   {
      using namespace std;      
      unsigned char *a = (unsigned char*)&val;      
      ostr << setw(2) << hex << (unsigned int)a[0];      
      for (size_t i=1; i < sizeof(value_type); ++i)
         ostr << '|' << setw(2) << hex << (unsigned int)a[i];      
      ostr << dec << ", " << val;

      if ( std::string(typeid( value_type ).name()) ==
	   std::string(typeid( long double ).name()) )
      {
	ostr << "\n    ";

	if (isprint(a[0]))
	  ostr << setw(2) << a[0];
	else
	  ostr << setw(2) << hex << (unsigned int)a[0] << dec;

	for (size_t i=1; i < sizeof(value_type); ++i)
	{
	  if (isprint(a[i]))
	    ostr << '|' << setw(2) << a[i];
	  else
	    ostr << '|' << setw(2) << hex << (unsigned int)a[i] << dec;
	}
      }
   }
   
   void body(void)
   {
      using namespace std;
      using namespace OpenMesh;

      // ---------------------------------------- start the game

      {
         ostringstream ostr;

         ostr << "Value of type " << typeid(value_type).name()
              << " with size " << sizeof(value_type) << " bytes.";
         info( ostr );
      }

      {
         ostringstream ostr;
         write( ostr, val_a_);
         info(ostr);
      }
         
      {
         ostringstream ostr;
         write(ostr, val_b_);
         info(ostr);
      }         
      IO::reverse_byte_order(val_a_);
      {
         ostringstream ostr;
         write(ostr, val_a_);
         info(ostr);
      }         
      TH_VERIFY( val_a_, val_b_ );
      
      info("End");
   }
   
};
// ----------------------------------------------------------------------------

int main(void)
{
  TestingFramework testSuite(std::cout);

  std::string pattern = "abcdefghijklmnop";
  std::string rpattern;
   
  union
  {
    char     pattern[32];
      
    char              c;
    unsigned char     uc;
    short             s;
    unsigned short    us;
    int               i;
    unsigned int      ui;      
    long              l;
    unsigned long     ul;
#if defined(OM_CC_MSVC)
    __int64           ll;
    unsigned __int64  ull;
#else
    long long         ll;
    unsigned long long ull;
#endif
    float             f;
    double            d;
    long double       ld;
  } a, b;

  a.c  = '1';
  b.c  = '1';
  new test_reverse_byte_order<char>( testSuite, "char", a.c, b.c );
  new test_reverse_byte_order<unsigned char>( testSuite, "unsigned char", a.uc, b.uc );

  a.s  = 0x0102;
  b.s  = 0x0201;
  new test_reverse_byte_order<short>(  testSuite, "short", a.s, b.s );

  a.s  = 0x0102;
  b.s  = 0x0201;
  new test_reverse_byte_order<unsigned short>( testSuite, 
					       "unsigned short", 
					       a.us  , b.us );

  a.i  = 0x01020304;
  b.i  = 0x04030201;
  new test_reverse_byte_order<int>(  testSuite, "int", a.i, b.i );
  a.i = 0x01020304;
  new test_reverse_byte_order<unsigned int>( testSuite, 
					     "unsigned int", a.ui  , b.ui );
  a.l = 0x01020304;
  new test_reverse_byte_order<long>(  testSuite, "long", a.l, b.l );
  a.ul = 0x01020304;
  new test_reverse_byte_order<unsigned long>( testSuite, 
					      "unsigned long", a.ul  , b.ul );

  a.ll = 0x0102030405060708ll;
  b.ll = 0x0807060504030201ll;
#if defined(OM_CC_MSVC)
  new test_reverse_byte_order<__int64>( testSuite, "int64", a.ll, b.ll );
  a.ll = 0x0102030405060708;
  new test_reverse_byte_order<unsigned __int64>( testSuite, 
						 "int64", a.ull, b.ull );
#else
  new test_reverse_byte_order<long long>(  testSuite, 
					   "long long", a.ll, b.ll );
  a.ll = 0x0102030405060708ll;
  new test_reverse_byte_order<unsigned long long>( testSuite, 
						   "unsigned long long", 
						   a.ull  , b.ull );
#endif
  a.l = 0x01020304;
  b.l = 0x04030201;
  new test_reverse_byte_order<float>(  testSuite, "float", a.f, b.f );

  a.ll = 0x0102030405060708ll;
  b.ll = 0x0807060504030201ll;
  new test_reverse_byte_order<double>( testSuite, "double", a.d  , b.d );

  long double d1, d2;

  memset( &d1, 0, sizeof(a.ld) );
  memset( &d2, 0, sizeof(b.ld) );

  strncpy( (char*)&d1, pattern.c_str(), sizeof(d1)); 
  rpattern = pattern;
  std::reverse(rpattern.begin(),rpattern.end());
  strncpy( (char*)&d2, rpattern.c_str(), sizeof(d2)); 

  new test_reverse_byte_order<long double>( testSuite, "long double", 
					    d1  , d2 );
   
  return testSuite.run();
}

