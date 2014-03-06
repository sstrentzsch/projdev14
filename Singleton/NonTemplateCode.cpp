/*
   Two Singleton examples
   One - the direct implementation
   Two - a template implementation
*/

#include <iostream>
#include <string>



using namespace std;

class Singleton
{
private:
   static bool instanceFlag;
   static Singleton *single;
   Singleton() { /* private constructor prevents external construction */ }

public:
   static Singleton* getInstance();
   void method();
   ~Singleton()
   {
      instanceFlag = false;
   }
};

bool Singleton::instanceFlag = false;
Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
   // In a multi-threaded environment, this code is not sufficient and leads to 
   // (1) an initial race condition; and (2) subsequent inefficiencies.
   if(! instanceFlag)
   {
      single = new Singleton();
      instanceFlag = true;
      return single;
   }
   else
   {
      return single;
   }
}

void Singleton::method()
{
   cout << "Method of the singleton class - Instance (this) = " << (void*) this << endl;
}





//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------



int main()
{
   Singleton *sc1,*sc2;
   sc1 = Singleton::getInstance();
   sc1->method();
   sc2 = Singleton::getInstance();
   sc2->method();





   return 0;
}