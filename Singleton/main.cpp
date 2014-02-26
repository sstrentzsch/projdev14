/*
   Two Singleton examples
   One - the direct implementation
   Two - a template implementation
*/

#include <iostream>
#include <string>

#include "SingletonTemplate.h"



using namespace std;



class Singleton
{
private:
   static bool instanceFlag;
   static Singleton *single;
   Singleton() { /* private constructor prevents external construction */ }

public:
   static Singleton* getInstance();

   // Application specific method(s)
   void somethingOfInterest();
      string stringVar;

public:
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
      single->stringVar = "A";
      return single;
   }
   else
   {
      return single;
   }
}



void Singleton::somethingOfInterest()
{
   cout << "Method of the singleton class - Instance (this) = " << (void*) this << endl;
   cout << "stringVar is " << stringVar << endl;
   stringVar += stringVar;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class Device : public CSingleton<Device>
{
public:
   friend class CSingleton<Device>;

   friend ostream& operator<< ( ostream& strm, const Device& dev )
   {
      strm << dev.myString << ':' << (void*) &dev;
      return strm;
   }

   bool open ( ) {
      cout << "Device Open: this=" << (void*) this << endl;
   }

   bool close ( ) {
      cout << "Device Open: this=" << (void*) this << endl;
   }

private:
   Device ( ) { }


private:
   string   myString;
};




//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------



int main()
{
   {
      Singleton *sc1,*sc2;
      sc1 = Singleton::getInstance();
      sc1->somethingOfInterest();
            // Another thread, another source file - running parallel      
            sc2 = Singleton::getInstance();
            sc2->somethingOfInterest();

      sc1->somethingOfInterest();
            // Another thread, another source file - running parallel      
            sc2->somethingOfInterest();


   }





      cout << "STOP!!\n";












   Device& device1 = Device::getInstance();
   
   cout << "Device 1 is " << device1 << endl;

   cout << "Device::getInstance() is " << Device::getInstance() << endl;



   return 0;
}