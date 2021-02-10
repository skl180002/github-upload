#include "Beetle.h"
Beetle::Beetle()
{
    turns = 0;
    breedTimer = 8;
    starveTimer = 5;
}

Beetle::Beetle(int turnsElapsed, int breed)
{
    turns = turnsElapsed;
    breedTimer = breed;
    starveTimer = 5;
    //ctor
}
void Beetle::mover(int row, int collumn, int turnsElapsed, Creature* playingBoard[10][10])
{
    if (turns < turnsElapsed) //Once again, this is anti double move protection. Cannot have moved more times than turns passed.
    {
        turns++;
        int direction = directionMove(row,collumn,playingBoard);        //Determines which way the beetle moves.
        if (direction == 0 && row-1 > -1)
        {
            if (whatsThis(row-1,collumn,playingBoard)!= 1)
            {
                if (whatsThis(row-1,collumn,playingBoard)== 2)                //If the spot is empty or an ant, and in bounds, move
                    starveTimer=6;                                            //if also an ant, refill your gas tank.
                playingBoard[row-1][collumn]=this;
                playingBoard[row][collumn] = nullptr;
            }
        }
        else if (direction == 1 && collumn+1 < 10)
        {
            if (whatsThis(row,collumn+1,playingBoard)!= 1)
            {
                if (whatsThis(row,collumn+1,playingBoard)== 2)       //there's one for each direction.
                    starveTimer = 6;
                playingBoard[row][collumn+1]=this;
                playingBoard[row][collumn] = nullptr;
            }
        }
        else if (direction == 2 && row+1 < 10)
        {
            if (whatsThis(row+1,collumn,playingBoard)!= 1)
            {
                if (whatsThis(row+1,collumn,playingBoard)== 2)
                    starveTimer = 6;
                playingBoard[row+1][collumn]=this;
                playingBoard[row][collumn] = nullptr;
            }
        }
        else if (direction == 3 && collumn-1 > -1)
        {
            if (whatsThis(row,collumn-1,playingBoard)!= 1)
            {
                if (whatsThis(row,collumn-1,playingBoard)== 2)
                    starveTimer = 6;
                playingBoard[row][collumn-1]=this;
                playingBoard[row][collumn] = nullptr;
            }
        }
    }
}




void Beetle::breeder(int row, int collumn, Creature* playingBoard[10][10])
{
    breedTimer --;
    if (breedTimer==0)
    {
        breedTimer=8;                                          //If its time to breed, do so in the clockwise priority spot. Rest timer.
        if (row-1 > -1)
        {
            if (whatsThis(row-1,collumn,playingBoard)== 0)
            {
                playingBoard[row-1][collumn]= new Beetle(turns,8);
                  return;
            }
        }
         if (collumn+1 < 10)
        {

            if (whatsThis(row,collumn+1,playingBoard)== 0)
            {
                playingBoard[row][collumn+1]= new Beetle(turns,9);
                return;
            }
        }
        if (row+1 < 10)
        {

            if (whatsThis(row+1,collumn,playingBoard)== 0)
            {
                playingBoard[row+1][collumn]= new Beetle(turns,9);
                return;
            }
        }
        if (collumn-1 > -1)
        {

            if (whatsThis(row,collumn-1,playingBoard)== 0)
            {
                playingBoard[row][collumn-1]= new Beetle(turns,8);
                return;
            }
        }
    }
}





void Beetle::starver(int row, int collumn, Creature* playingBoard[10][10])      //Beetle gets hungrier. Too hungry? Delete yourself.
{
    starveTimer = starveTimer-1;
    if (starveTimer == 0)
        playingBoard[row][collumn] = nullptr;
}


int Beetle::directionMove(int row, int collumn, Creature* playingBoard[10][10])
{
    int maxNeighbors = 0;
    int minDist = 10;
    int dist = 0;
    int dir = 0;
    int rSpot = row;
    int cSpot=collumn;
    while (rSpot> -1)
    {
        if(whatsThis(rSpot,cSpot,playingBoard)==2)             //As opposed to the ants, beetles find shortest ant with most friends.
        {
            minDist = dist;
            dir = 0;
            maxNeighbors = neighbors(rSpot, cSpot, playingBoard);         //Neighbor tells how many other snacks are close to the target.
            break;
        }
        rSpot=rSpot-1;
        dist=dist+1;
    }
    dist = 0;
    rSpot = row;
    while (cSpot<10)
    {
        if(whatsThis(rSpot,cSpot,playingBoard)==2)
        {
            if(dist<minDist)
            {
                minDist = dist;
                dir = 1;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            else if (dist == minDist && maxNeighbors<neighbors(rSpot, cSpot, playingBoard))       //If in ant is closer or more popular, chase it!
            {
                dir = 1;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            break;
        }
        cSpot=cSpot+1;
        dist=dist+1;
    }
    cSpot=collumn;
    dist=0;

    while (rSpot<10)
    {
        if(whatsThis(rSpot,cSpot,playingBoard)==2)
        {
            if(dist<minDist)
            {
                minDist = dist;
                dir = 2;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            else if (dist == minDist && maxNeighbors<neighbors(rSpot, cSpot, playingBoard))
            {
                dir = 2;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            break;
        }
        rSpot=rSpot+1;
        dist=dist+1;
    }
    rSpot=row;
    dist=0;
    while (cSpot>-1)
    {
        if(whatsThis(rSpot,cSpot,playingBoard)==2)
        {
            if(dist<minDist)
            {
                minDist = dist;
                dir = 3;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            else if (dist == minDist && maxNeighbors<neighbors(rSpot, cSpot, playingBoard))
            {
                dir = 3;
                maxNeighbors = neighbors(rSpot, cSpot, playingBoard);
            }
            break;
        }
        cSpot=cSpot-1;
        dist=dist+1;
    }
    cSpot=collumn;
    dist=0;

    if (minDist<10)
    {
        return dir;                  //if you found an ant, chase it
    }
    if (row>=collumn && row >= 9-row && row >= 9-collumn)
    {
        return 0;
    }
    if (9-collumn >=row && 9-collumn >= collumn && 9-collumn >= 9-row)      //otherwise, head for the furthest edge. NESW priority.
    {
        return 1;
    }
    if (9-row>= collumn && 9-row >= row && 9-row >= 9-collumn)
    {
        return 2;
    }
    if (collumn >=row && collumn >= 9-collumn && collumn >= 9-row)
    {
        return 3;
    }
    return 0; //Juusssst in case
}


int Beetle::neighbors(int row, int collumn, Creature* board[10][10])
{
    int neighNum = 0;
    if (row+1<10)
    {
        if(whatsThis(row+1,collumn, board)==2)
            neighNum++;
    }
    if (row+1<10&&collumn+1<10)
    {
        if(whatsThis(row+1,collumn+1, board)==2)
            neighNum++;
    }
    if (row-1>-1)
    {
        if(whatsThis(row-1,collumn, board)==2)                     //+1 neighbors for each occupied nearby spot.
            neighNum++;
    }
    if (row-1>-1&&collumn-1>-1)
    {
        if(whatsThis(row-1,collumn-1, board)==2)
            neighNum++;
    }
    if (collumn+1<10)
    {
        if(whatsThis(row,collumn+1, board)==2)
            neighNum++;
    }
    if (row+1<10&&collumn-1>-1)
    {
        if(whatsThis(row+1,collumn-1, board)==2)
            neighNum++;
    }
    if (collumn-1>-1)
    {
        if(whatsThis(row,collumn-1, board)==2)
            neighNum++;
    }
    if (row-1>-1&&collumn+1<10)
    {
        if(whatsThis(row-1,collumn+1, board)==2)
            neighNum++;
    }
    //std::cout<<std::endl<< this << " " << row <<" , "<< collumn<<" Has "<<neighNum<<std::endl;
    return neighNum;
}

int Beetle::whatsThis(int row, int collumn, Creature* board[10][10])
{
    if (board[row][collumn] == nullptr)                 //Once again just saves lots and lots of typing.
    {
        return 0;
    }
    else if (dynamic_cast<Beetle*>(board[row][collumn]))
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
Beetle::~Beetle()
{
    //dtor
}
