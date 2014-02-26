
#pragma once

template<class T>
class CSingleton
{
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

   static const T* ptrInstance ( )  { return myInstance; }

protected:
   CSingleton() { }           // protected constructor to allow derived class to construct
   virtual ~CSingleton(){};

private:
   static T* myInstance;      // Instance pointer

private:
   // Especially important that singleton objects NOT be copyable/assignable
   CSingleton ( CSingleton const & );
   CSingleton & operator=( CSingleton const & );
};



template<class T>
T* CSingleton<T>::myInstance = NULL;