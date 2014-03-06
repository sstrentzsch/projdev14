

#pragma once

#include <iostream>

template<class T>
class CSingleton;

template<class T>
class Cleaner
{
public:
  
   Cleaner ( ) {
      std::cout << "CSingleton<T>::Cleaner::Cleaner\n";
      CSingleton<T>::getInstance();
   }
   ~Cleaner ( ) {
      std::cout << "CSingleton<T>::Cleaner::~Cleaner\n";
      CSingleton<T>::release();
   }

   void msg ( ) { cout << "Cleaner::msg\n"; }
};


template<class T>
class CSingleton
{
   friend class Cleaner<T>;

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
      delete myInstance;
      myInstance = NULL;
   }

protected:
   CSingleton() { }           // protected constructor to allow derived class to construct
   virtual ~CSingleton(){};

private:
   static T* myInstance;      // Instance pointer
public:
   static Cleaner<T> myCleaner;

private:
   // Especially important that singleton objects NOT be copyable/assignable
   CSingleton ( CSingleton const & );
   CSingleton & operator=( CSingleton const & );
};



template<class T>
T* CSingleton<T>::myInstance = NULL;


template<class T>
Cleaner<T> CSingleton<T>::myCleaner;



//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


template<class T>
class CRefCountedSingleton
{
public:

   static T& getInstance()
   {
      // Problem with this code in multi-threaded environments.
      if ( myInstance == NULL )
      {
         myInstance = new T;
      }
      ourRefCount++;
      return *myInstance;
   };

   void releaseInstance ( )
   {
      if ( myInstance && ourRefCount > 0 && --ourRefCount == 0 )
      {
         cout << "RefCountedSingleton - releasing unused myInstance\n";
         T* temp = myInstance;
         myInstance = NULL;
         delete temp;
      }
   }


protected:
   CRefCountedSingleton() {  

   }           // protected constructor to allow derived class to construct

   virtual ~CRefCountedSingleton() {
      
   }

private:
   static T* myInstance;      // Instance pointer
   static int ourRefCount;    // current use counter

private:
   // Especially important that singleton objects NOT be copyable/assignable
   CRefCountedSingleton ( CRefCountedSingleton const & );
   CRefCountedSingleton & operator=( CRefCountedSingleton const & );
};



template<class T>
T* CRefCountedSingleton<T>::myInstance = NULL;

template<class T>
int CRefCountedSingleton<T>::ourRefCount = 0;
