

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
   }
   ~CSingletonKiller ( ) {
      std::cout << "CSingleton<T>::CSingletonKiller::~CSingletonKiller\n";
      CSingleton<T>::release();
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
         // myCSingletonKiller;  //forces CSingletonKiller<T> myCSingletonKiller to be instantiated once (static).
         myInstance = new T;
      }
      return *myInstance;
   };

private:
   static void release ( void )
   {
      delete myInstance;
      myInstance = NULL;
   }

protected:              // protected constructor to allow derived class to construct
   CSingleton() { 
      myCSingletonKiller;        // no-op reference, forces instantiation of template CSingleton<T>::myCSingletonKiller
   }           
   virtual ~CSingleton(){};

private:
   static T* myInstance;      // Instance pointer
public:
   static CSingletonKiller<T> myCSingletonKiller;

private:
   // Especially important that singleton objects NOT be copyable/assignable
   CSingleton ( CSingleton const & );
   CSingleton & operator=( CSingleton const & );
};



template<class T>
T* CSingleton<T>::myInstance = NULL;


template<class T>
CSingletonKiller<T> CSingleton<T>::myCSingletonKiller;


// template class CSingleton<int>;
