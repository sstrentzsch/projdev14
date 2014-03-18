

#pragma once

#include <iostream>

template<class T>
class CSingleton;



// CSingletonKiller<T>'s whole purpose is to ensure destruction of the
// corresponding CSingleton<T>.  It works by ensuring a private, inaccessible
// static - thus global - CSingletonKiller<T> instance can be declared as a 
// member of CSingleton<T> - the static instance both constructs and destructs,
// 
template<class T>
class CSingletonKiller
{
private:                            // Make EVERYTHING in CSingletonKiller private...
   friend class CSingleton<T>;      // ... so only our friend CSingleton<T> can create a CSingletonKiller<T> object...
  
   CSingletonKiller ( ) {
      std::cout << "CSingleton<T>::CSingletonKiller::CSingletonKiller\n";
      
      // Uncommenting this line performs "eager instantiation".  Leaving it commented out
      // causes on-demand initialization.  There are static object/dynamic memory order of
      // initialization issues to be considered with *both* mechanisms.
      //CSingleton<T>::getInstance();
   }
   ~CSingletonKiller ( ) {
      CSingleton<T>::release();
      std::cout << "CSingleton<T>::CSingletonKiller::~CSingletonKiller\n";
   }
};



template<class T>
class CSingleton
{
   friend class CSingletonKiller<T>;

public:
   static T& getInstance()
   {
      // Problem with this code in multi-threaded environments.
      if ( myInstance == NULL )
      {
         myInstance = new T;
      }
      return *myInstance;
   };

private:
   static void release ( void )
   {
      // Ditto problem here with multithreaded environments
      T* tmp = myInstance;
      myInstance = NULL;
      delete tmp;
   }

protected:              
   // protected ctor/dtor allow derived class to construct/destruct
   CSingleton() { 
      // no-op reference forces instantiation of template CSingleton<T>::myCSingletonKiller
      // A template classes static data members *won't* be instantiated without at least one
      // reference to the data member.  
      myCSingletonKiller;        
   }
   virtual ~CSingleton() { } 

private:
   static T* myInstance;      // Instance pointer
   static CSingletonKiller<T> myCSingletonKiller;  // non-dynamic member object to ensures destruction

private:
   // Especially important that singleton objects NOT be copyable/assignable
   CSingleton ( CSingleton const & );
   CSingleton & operator=( CSingleton const & );
};


// declaration of singleton templates static instance pointer
template<class T>
T* CSingleton<T>::myInstance = NULL;

// declaration of singleton templates static data member that forces cleanup
template<class T>
CSingletonKiller<T> CSingleton<T>::myCSingletonKiller;


// template class CSingleton<int>;
