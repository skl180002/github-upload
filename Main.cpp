// Scott Kelly Lorance SKL180002
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include "Creature.h"
#include "Beetle.h"
#include "Ant.h"
using namespace std;

void boardMaker(Creature*[10][10],ifstream&);
void boardPrinter(char,char,Creature*[10][10]); //some prototypes. gotta sub divide tasks.
void beetleMover(int, Creature*[10][10]); //takes the current turn and the board in, applies the indicated change
void antMover(int,Creature*[10][10]);
void beetleStarver(Creature*[10][10]);
void antBreeder(Creature*[10][10]);
void beetleBreeder(Creature*[10][10]);


int main()
{

   //The holy, all mighty playing board. Stores ants beetles and null pointers.
    Creature* board[10][10];
    //prepare a variable so we know what file we will read from
    string fileName;
    cin >> fileName;
    //now we open the file name stored with file name
    ifstream inputData;
    //make sure it actually opened
    inputData.open(fileName);
    if (!inputData.is_open())
    {
        cout << "Could not open file " << fileName << endl;
        return 1;
    }
    char antChar;
    cin >> antChar;
    char beetleChar;      //All the user input gets stored ass a variable.
    cin >> beetleChar;
    int maxTurns;
    cin >> maxTurns;

    boardMaker(board,inputData); //Build the board

    for (int i = 1; i<= maxTurns; i++)
    {
        cout<< "TURN " << i << endl;
        beetleMover(i,board);
        antMover(i,board);                      //Run each turn step by step, plus a little bit of formatting.
        beetleStarver(board);
        antBreeder(board);
        beetleBreeder(board);
        boardPrinter(antChar,beetleChar, board);
        cout<< endl;

    }
    inputData.close(); //Good practice
}

void boardMaker(Creature* board[10][10], ifstream& input)
{
   //This function takes the board and the file as imput, and parses the file to populate the board
    char current;
    int row = 0;           //I prefer this to for loops, easier for me to understand.
    int collumn = 0;
    // int counter = 0;
    string dump;
    while (row<10)
    {
        while (collumn < 10)
        {
            current = (char)input.get();      //But basically what happens here is we use the input as a key and make them into bugs!
            if(current == 'a')
            {
                board[row][collumn] = new Ant;
            }
            else if (current == 'B')
            {
                board[row][collumn] = new Beetle;               //NOTE << This is in the wrong order! Read japanese style!
            }
            else
            {
                board[row][collumn] = nullptr;          //Not technically needed, but it makes me more comfortable.
            }
            collumn = collumn +1;
        }
        collumn = 0;
        row = row+1;
        getline(input, dump);                //After 10 characters we look at the next line.
    }
}


void boardPrinter(char antChar, char beetleChar, Creature* board[10][10])
{
   //This function uses the board and the output symbols to represent the creature array in the output.
    int row = 0;
    int collumn = 0;               //Last function turned letters into bugs, this turns bugs into letters.

    while (row<10)
    {
        while (collumn < 10)
        {
            if(dynamic_cast<Ant*>(board[row][collumn]))
            {
                cout << antChar;
            }
            else if (dynamic_cast<Beetle*>(board[row][collumn]))     // We print out each bug's chosen character.
            {
                cout << beetleChar;
            }
            else
            {
                cout << ' ';
            }
            collumn = collumn +1;
        }
        cout <<endl;
        collumn = 0;
        row = row+1;
    }
   // cout<< "-------------------------------------------------------------" <<endl; During early code this made for easy reading
}


void beetleMover(int turnsElapsed, Creature* board[10][10])
{
   //This takes the number of turns (so as to prevent moving twice) and the board to run the move function of each beetle.
    int row = 0;
    int collumn = 0;

    while (collumn<10)
    {
        while (row < 10)
        {
            if(dynamic_cast<Beetle*>(board[row][collumn]))
            {
                board[row][collumn]->mover(row,collumn,turnsElapsed,board);           //We  find if a spot is a beetle, if it is, it moves.
            }
            row = row +1;                                    //Defense against double move is inside the beetle class.
        }
        row = 0;
        collumn = collumn+1;
    }

}
void antMover(int turnsElapsed, Creature* board[10][10])
{
   //Same as the beetle mover, but with ants.
    int row = 0;
    int collumn = 0;

    while (collumn<10)
    {
        while (row < 10)
        {
            if(dynamic_cast<Ant*>(board[row][collumn]))
            {
                board[row][collumn]->mover(row,collumn,turnsElapsed,board);          //The same as the beetlemover, except with ants.
            }                                                                        //Once again, double move defense built in.
            row = row +1;
        }
        row = 0;
        collumn = collumn+1;
    }
}

void beetleStarver(Creature* board[10][10])
{
   //Takes in the board, and calls the starve function of each beetle present.
    int row = 0;
    int collumn = 0;

    while (collumn<10)
    {
        while (row < 10)
        {
            if(Beetle* thisguy = dynamic_cast<Beetle*>(board[row][collumn]))      //we use thisguy because you cant use beetle actions on a creature
            {
                thisguy->starver(row,collumn,board);
            }
            row = row +1;
        }
        row = 0;
        collumn = collumn+1;
    }
}
void beetleBreeder(Creature* board[10][10])
{
   //The board is taken in, and much like starve, it runs each beetle's breed function.
    int row = 0;
    int collumn = 0;

    while (collumn<10)
    {
        while (row < 10)
        {
            if(dynamic_cast<Beetle*>(board[row][collumn]))
            {
                board[row][collumn]->breeder(row,collumn,board);         //Ngl these functions are really similar.
            }
            row = row +1;
        }
        row = 0;
        collumn = collumn+1;
    }
}

void antBreeder(Creature* board[10][10])                        //Ah, yes, functions that just loop call functions.
{
   //same as beetle breeder.
    int row = 0;
    int collumn = 0;

    while (collumn<10)
    {
        while (row < 10)
        {
            if(dynamic_cast<Ant*>(board[row][collumn]))
            {
                board[row][collumn]->breeder(row,collumn,board);
            }
            row = row +1;
        }
        row = 0;
        collumn = collumn+1;
    }
}

