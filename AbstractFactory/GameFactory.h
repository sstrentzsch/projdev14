
#pragma once

#include <string>
using std::string;


class Obstacle {
public:
   virtual string action() = 0;
};

class Player {
public:
   virtual string name() = 0;
};

class Interaction {
public:
   virtual string descr ( ) = 0;
};



class HappyPlayer: public Player {
   string name() { 
      string player[] = { "Soft Kitty", "Happy Pony", "Fuzzy Bear" };
      return player[ rand() % 3 ]; 
   }
};

class GoodGuy: public Player {
   string name() { 
      string player[] = { "Duke Nukem", "Scott Pilgrim", "Master Chief" };
      return player[ rand() % 3 ]; 
   }
};



class Puzzle: public Obstacle {
public:
   string action() { 
      string items[] = { "a Treasure Chest", "a Maze", "a magic door" };
      return items[ rand() % 3]; 
   }
};

class EnemyForce: public Obstacle {
public:
   string action() { 
      string items[] = { "a Barbarian Horde", "the Zombie Pirates", "the Android Army" };
      return items[ rand() % 3]; 
   }
};




class Encounter : public Interaction {
   string descr ( ) { 
      string items[] = { "opens", "finds", "sees" };
      return items[ rand() % 3]; 
   }
};


class Battle : public Interaction {
   string descr ( ) { 
      string items[] = { "battles against", "runs away from", "nukes" };
      return items[ rand() % 3]; 
   }
};





//----------------------------------------------------------------------------------------
// The abstract factory defines the interface for making game elements
class GameElementFactory {
public:
   virtual Player* makePlayer() = 0;
   virtual Obstacle* makeObstacle() = 0;
   virtual Interaction* makeInteraction() = 0;

   enum GameFactoryType { WarmAndFuzzy = 0, BloodAndGuts, NumGameTypes };

};



// Concrete factories provide implementations for specific games
class WarmAndFuzzy : public GameElementFactory {
public:
   virtual Player* makePlayer() { return new HappyPlayer; }
   virtual Obstacle* makeObstacle() { return new Puzzle; }
   virtual Interaction* makeInteraction() { return new Encounter; }
};

class KillAndDismember : public GameElementFactory {
public:
   virtual Player* makePlayer() { return new GoodGuy; }
   virtual Obstacle* makeObstacle() { return new EnemyForce; }
   virtual Interaction* makeInteraction() { return new Battle; }
};
