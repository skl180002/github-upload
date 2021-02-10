#include "Ant.h"
#include <iostream>
Ant::Ant()
{
    turns=0;
    breedTimer=3;
}
Ant::Ant(int turnsElapsed, int breed)
{
    breedTimer=breed;
    turns=turnsElapsed;
    //ctor
}
void Ant::mover(int row, int collumn, int turnsElapsed, Creature* playingBoard[10][10])
{
    if (turns<turnsElapsed)     //Turns elapsed prevents ant from moving twice in a turn, by comparing to the for loop.
    {
        turns++;
        int direction = directionMove(row,collumn,playingBoard);           //directionMove does the leg work, and tells the ant where to move.

        if(direction == -1)    //Don't move.
        {
            return;
        }
        if (direction == 0 && row-1 > -1)
        {

            if (playingBoard[row-1][collumn] == nullptr) //up
            {
                playingBoard[row-1][collumn] = this;
                playingBoard[row][collumn] = nullptr;
            }
        }
        if (direction == 1 && collumn+1 < 10)
        {

            if (playingBoard[row][collumn+1] == nullptr)              //The actual moving of the ant. Copies itself somewhere new, deletes old spot.
            {
                playingBoard[row][collumn+1] = this;                    //Includes defense against out of bounds exceptions.
                playingBoard[row][collumn] = nullptr;   //right
            }
        }
        if (direction == 2 && row+1 < 10)
        {

            if (playingBoard[row+1][collumn] == nullptr)
            {
                playingBoard[row+1][collumn] = this;
                playingBoard[row][collumn] = nullptr;       //down
            }
        }
        if (direction == 3 && collumn-1 > -1)
        {

            if (playingBoard[row][collumn-1] == nullptr)
            {
                playingBoard[row][collumn-1] = this;
                playingBoard[row][collumn] = nullptr;       //left
            }
        }
    }
}
void Ant::breeder(int row, int collumn, Creature* playingBoard[10][10])
{
    breedTimer --;


    if (breedTimer==0)
    {
        breedTimer=3;
        if (row-1 > -1)
        {
            if (whatsThis(row-1,collumn,playingBoard)== 0)
            {
                playingBoard[row-1][collumn]= new Ant(turns,3);            //Counts down to breed, if it can breed, breed.
                return;                                                    //once breeding it makes new ant if space available
                                                                           //Goes NESW
            }
        }
        if (collumn+1 < 10)
        {

            if (whatsThis(row,collumn+1,playingBoard)== 0)
            {
                playingBoard[row][collumn+1]= new Ant(turns,4);
                return;

            }
        }
        if (row+1 < 10)
        {

            if (whatsThis(row+1,collumn,playingBoard)== 0)
            {
                playingBoard[row+1][collumn]= new Ant(turns,4);
                return;

            }
        }
        if (collumn-1 > -1)
        {

            if (whatsThis(row,collumn-1,playingBoard)== 0)
            {
                playingBoard[row][collumn-1]= new Ant(turns,3);
                return;

            }
        }
    }
}
int Ant::whatsThis(int row, int collumn, Creature* board[10][10])
{
    if (board[row][collumn] == nullptr)
    {
        return 0;
    }
    else if (dynamic_cast<Ant*>(board[row][collumn]))                         //Rather than copy paste this alot, I just made a function.
    {                                                                         //This sees if the spot is null, itself (an ant) or
        return 1;                                                             //Not itself, aka a beetle
    }
    else
    {
        return 2;
    }
}
int Ant::directionMove(int row,int collumn,Creature* board[10][10])
{

    int distDown = 23;
    int distLeft = 22;
    int distUp = 25;
    int distRight = 24;            //By starting with these values, NESW priority is built in when there's no beetle in 2 directions.
    int dist = 0;
    int rSpot = row;
    int cSpot = collumn;
    while(rSpot> -1 && rSpot < 10 && cSpot > -1&& cSpot<10)            //effectively, the ant shoots a beetle range finder
    {
        if (whatsThis(rSpot,cSpot,board)==2)                           //If it hits we record that distance.
        {
            distDown = dist;
            break;
        }
        dist++;
        rSpot++;
    }

    rSpot =row;
    cSpot=collumn;
    dist=0;

    while( rSpot >-1 && rSpot < 10 && cSpot>-1 && cSpot < 10)
    {
        if (whatsThis(rSpot,cSpot,board)==2)
        {
            distLeft = dist;
            break;
        }
        dist++;
        cSpot--;
    }

    rSpot =row;
    cSpot=collumn;
    dist=0;

    while( rSpot > -1 && rSpot < 10 && cSpot > -1 && cSpot < 10)
    {
        if (whatsThis(rSpot,cSpot,board)==2)
        {
            distUp = dist;
            break;
        }
        dist++;
        rSpot--;
    }

    rSpot =row;
    cSpot=collumn;
    dist=0;

    while(rSpot > -1 && rSpot < 10 && cSpot > -1 && cSpot < 10)
    {
        if (whatsThis(rSpot,cSpot,board)==2)
        {
            distRight = dist;
            break;
        }
        dist++;
        cSpot++;
    }

    rSpot =row;
    cSpot=collumn;
    dist=0;

    if (distDown>10 && distLeft> 10 && distUp >10 && distRight >10)             //This is "Coast is clear"
    {
        return -1; //
    }
    if (distDown < distLeft && distDown < distUp && distDown < distRight)         //these 4 are "Run from the closest"
    {
        return 0; //
    }
    if (distLeft < distDown && distLeft < distUp && distLeft < distRight)
    {
        return 1;
    }
    if (distUp < distLeft && distUp < distDown && distUp < distRight)
    {
        return 2;
    }
    if (distRight < distLeft && distRight < distUp && distRight < distDown)
    {
        return 3;
    }
    if (distRight == distLeft || distRight == distUp || distRight == distDown || distLeft == distUp || distLeft == distDown || distDown == distUp)
    {

        if (distUp >= distLeft && distUp >= distRight && distUp >= distDown)    //In the event there's a tie, follow farthest and NESW priority.
        {
            return 0;
        }

        if (distRight >= distLeft && distRight >= distUp && distRight >= distDown)
        {
            return 1;
        }

        if (distDown >= distRight && distDown >= distUp && distDown >= distLeft)
        {
            return 2;
        }

        if (distLeft >= distRight && distLeft >= distUp && distLeft >= distDown)
        {
            return 3;
        }
    }
    return 0; //This just avoids a warning message
}



Ant::~Ant()
{
    //dtor
}
