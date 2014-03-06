#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "SingletonTemplate.h"

class Printer
{
public:
   virtual ~Printer (  ) { }
public:
   virtual void print ( ) = 0;
   virtual void open ( ) = 0;
   virtual void close ( ) = 0;
};





//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

class SinglePrinterImpl : public CRefCountedSingleton<SinglePrinterImpl>, public Printer
{
public:
   friend class CRefCountedSingleton<SinglePrinterImpl>;

   friend ostream& operator<< ( ostream& strm, const SinglePrinterImpl& dev )
   {
      strm << "SinglePrinterImpl:" << dev.myString << ':' << (void*) &dev;
      return strm;
   }

   void open ( ) {
      cout << "Printer Open: this=" << (void*) this << endl;
   }

   void close ( ) {
      cout << "Printer Open: this=" << (void*) this << endl;
   }

   void print ( ) { 
      cout << "Printer Print: this=" << (void*) this << endl;
   }

protected:
   SinglePrinterImpl ( ) : myString("SinglePrinter") { }
   ~SinglePrinterImpl ( ) { cout << "SinglePrinterImpl::dtor: "; this->releaseInstance(); }


private:
   string   myString;
};



// Classic impl design pattern
class SinglePrinter : public Printer
{
public:
   SinglePrinter ( ) : impl( &SinglePrinterImpl::getInstance() ) { cout << "SinglePrinter ctor\n"; }
   ~SinglePrinter ( ) { cout << "SinglePrinter dtor\n"; impl->releaseInstance(); impl = NULL; }


   friend ostream& operator<< ( ostream& strm, const SinglePrinter& dev )
   {
      strm << *(dev.impl);
      return strm;
   }

   void open ( ) {
      return ( impl->open() );
   }

   void close ( ) {
      return( impl->close() );
   }

   void print ( ) { 
      return( impl->print() );
   }

private:
   SinglePrinterImpl* impl;

};
