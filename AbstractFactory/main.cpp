
//---------------------------------------------------------------------------------
// Title :
// Author:
// Date  :
// Descr :
//---------------------------------------------------------------------------------

#include <cstdio>
#include <cstddef>
#include <cassert>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

#include "GameFactory.h"

using namespace std;





// Finally, a simple game environment with a single player, obstacle, and 
// interaction.  Depending on the game factory that is provided, different
// game experiences result.
class GameEnvironment {
   GameElementFactory* gef;
   Player* p;
   Obstacle* ob;
   Interaction* iAct;
public:
   GameEnvironment ( GameElementFactory* factory ) 
   {
      gef = factory;
      p = gef->makePlayer();
      ob = gef->makeObstacle();
      iAct = gef->makeInteraction();
   }

   void play() { 
      cout << p->name() << ' '
           << iAct->descr() << ' '
           << ob->action() << endl;
   }

   ~GameEnvironment() {
      delete iAct;
      delete p;
      delete ob;
      delete gef;
   }
};



//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


GameElementFactory* randomGameFactory ( void )
{
   GameElementFactory* gef;
   
   switch ( rand() % GameElementFactory::NumGameTypes )
   {
   case GameElementFactory::WarmAndFuzzy:
      gef = new WarmAndFuzzy; 
      break;
   case GameElementFactory::BloodAndGuts:
      gef = new KillAndDismember;
      break;
   default:
      cout << "OOOPS - Bad GameElementFactory - Defaulting to BloodAndGuts!\n";
      break;
   }

   return gef;
}






int main ( /*int argc, char* argv[]*/ )
{
   srand( unsigned( time(NULL) ) );
   for (int i = 0; i < 10; i++)
   {
      GameEnvironment g( randomGameFactory() );
      g.play();
   }


   return 0;
}
