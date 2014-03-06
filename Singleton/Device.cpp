
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




