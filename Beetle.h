#ifndef BEETLE_H
#define BEETLE_H

#include "Creature.h"
#include <iostream>

class Beetle : public Creature
{
   public:
      Beetle();
      Beetle(int,int);
      void mover(int, int, int, Creature*[10][10]);
      void breeder(int, int, Creature*[10][10]);
      void starver(int,int, Creature*[10][10]);             //what a swag master, has his own starve function. So special.
      virtual ~Beetle();

   protected:

   private:
      int turns;
      int breedTimer;
      int directionMove(int,int,Creature*[10][10]);//All these are for checking the grid and determining action
      int whatsThis(int,int,Creature*[10][10]);
      int neighbors(int,int,Creature*[10][10]);        //Checks the spaces around an ant.
      int starveTimer;
};

#endif // BEETLE_H
