#ifndef CREATURE_H
#define CREATURE_H


class Creature
{
public:
    Creature(){}
    virtual void mover(int, int, int, Creature*[10][10]) =0;
    virtual void breeder(int, int, Creature*[10][10]) =0;               //Not much to explain, pure virtual functions.
    virtual ~Creature(){}



protected:

private:

    int turns;
    int breedTimer;
    int directionMove(int,int,Creature*[10][10]);
};

#endif // CREATURE_H
