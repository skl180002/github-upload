#ifndef ANT_H
#define ANT_H

#include "Creature.h"


class Ant : public Creature
{
   public:
      Ant();
      Ant(int, int);
      void mover(int, int, int, Creature*[10][10]);
      void breeder(int, int, Creature*[10][10]);
      virtual ~Ant();

   protected:

   private:
      int directionMove(int,int,Creature*[10][10]);
      int breedTimer;
      int turns;
      int whatsThis(int,int,Creature*[10][10]);               //Private functions that make choosing where to move easier.
};

#endif // ANT_H
