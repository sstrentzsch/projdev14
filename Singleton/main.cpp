/*
   Two Singleton examples
   One - the direct implementation
   Two - a template implementation
*/

#include <iostream>
#include <string>


#include "SingletonTemplate.h"


using namespace std;

class Random : public CSingleton<Random>
{
private:
   // Private constructor ensures Random can't be directly declared by client,
   // Parent class must be a friend so its getInstance() can create its child :-)
   friend class CSingleton<Random>;       
   Random ( ) { cout << "Random instantiated\n"; }
   ~Random ( ) { cout << "Random dtor\n"; }

public:
   int getNext ( void )
   {
      return rand();
   }

   int getRange ( int lo = 0, int hi = RAND_MAX )
   {
      int range = (rand() % (abs(hi - lo) + 1)) + min(hi,lo);
      return range;
   }

   float getFloat ( void )
   {
      float f = (rand() / float(RAND_MAX) );
      return f;
   }
   
};



//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------



int main()
{
   cout << "Entering main\n";
   // Random r; // this line must not work.
   
   for (int i = 0; i < 20; i++)
   {
      cout << Random::getInstance().getRange( -10, 10 ) << endl;
   }


   cout << "Exiting main\n";
   
   return 0;
}