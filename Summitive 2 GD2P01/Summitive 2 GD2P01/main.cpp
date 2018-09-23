#include "Board.h"
#include <iostream>

using namespace std;

Board* gameBoard;

//Entry Point
int main()
{
	gameBoard = new Board();
	gameBoard->generateMenu();
}