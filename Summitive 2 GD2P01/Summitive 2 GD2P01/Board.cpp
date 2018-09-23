#include "Board.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <vector>
#include <random>
#include <array>


using namespace std;


enum boardStates
{
	//defines the different states the board can be in
	emptySpace = '.',
	obsticle = 'O',
	path = '@',
	start = 'S',
	endPoint = 'E',

};

boardStates** dynamicArray = NULL;  // Pointer to boardStates, initialize to nothing.
int xSize;
int ySize;

//std::vector char


Board::Board()
{
}


Board::~Board()
{
}

void Board::generateMenu()
{
	
	//Cout the menu
	cout << "  _____________________________  " << endl;
	cout << "||                             ||" << endl;
	cout << "||Welcome to Tom's A* Algorythm||" << endl;
	cout << "||                             ||" << endl;
	cout << "||    Press Enter too Begin    ||" << endl;
	cout << "||_____________________________||" << endl;

	cin.ignore();

	
	//Clears window
	system("CLS");
	//sets the game to easy
	generateBoard();
	displayBoard();
	insertObsticles();
	placeStartPoint();
	placeEndPoint();
	displayBoard();
	aStarAlgorythm(startNode, destinationNode);

	char temp;
	cin >> temp;
	return;
	
}

void Board::generateBoard()
{
	cout << "Please enter the size of the board you wish too create: X Coordinate: ";
	cin >> xSize;        // Read in the size
	cout << "Please enter the size of the board you wish too create: Y Coordinate: ";
	cin >> ySize;        // Read in the size.

	//Creates a dynamic 2D array
	dynamicArray = new boardStates*[xSize];
	for (int i = 0; i < xSize; ++i)
		dynamicArray[i] = new boardStates[ySize];

	for ( int i = 0; i < xSize; i++)
	{
		for ( int j = 0; j < ySize; j++)
		{
			dynamicArray[i][j] = emptySpace;
			Node newNode;
			newNode.x = i;
			newNode.y = j;
			vectorOfNodes.push_back(newNode);
		}
	}
}

void Board::displayBoard()
{
	system("cls");
	//Cout the current game board
	
	for (int i = 0; i < xSize; i++)
	{
		cout << "\n|";
		for (int j = 0; j < ySize; j++)
		{
			cout << setw(3) << static_cast<char>(dynamicArray[i][j]) << setw(3) << " |";
		}
	}
	
	cin.ignore();
}

void Board::insertObsticles()
{
	int numberOfObsticles;
	cout << endl;
	cout << "Please enter the amount of obsticles you wish too place: ";
	cin >> numberOfObsticles;
	int x;
	int y;
	for (int i = 0; i < numberOfObsticles; i++)
	{
		cout << "Please enter the X coordinate of the obsticle you wish too place: (e.g 2) ";
		cin >> x;
		cout << "Please enter the Y coordinate of the obsticle you wish too place: (e.g 2) ";
		cin >> y;

		if (placeObject(x, y, 1) == true)
		{
			placeObject(x, y, 1);
		}

		else
		{
			cout << "Invalid Placement! There is already an Obsticle here or it is out of bounds!" << endl;
		}	
		
	}
	
	displayBoard();
}

bool Board::placeObject(int x, int y, int typeToPlace)
{
	int positionOfNodeCalculation = ((y * ySize) + x);

	if (x >= xSize || y >= ySize || x <= 0 || y <= 0)
	{
		return false;
	}

	if (dynamicArray[x][y] == emptySpace && typeToPlace == 1)
	{
		dynamicArray[x][y] = obsticle;
		int positionOfNode = positionOfNodeCalculation;
		vectorOfNodes.at(positionOfNode).isObsticle = true;
		return true;
	}

	if (dynamicArray[x][y] == emptySpace && typeToPlace == 2)
	{
		dynamicArray[x][y] = start;
		int positionOfNode = positionOfNodeCalculation;
		vectorOfNodes.at(positionOfNode).isStartPosition = true;
		startNode = vectorOfNodes.at(positionOfNode);
		
		return true;
	}

	if (dynamicArray[x][y] == emptySpace && typeToPlace == 3)
	{
		if (x != 9 && y != 9)
		{
			dynamicArray[x][y] = endPoint;
			int positionOfNode = positionOfNodeCalculation;
			vectorOfNodes.at(positionOfNode).isEndPosition = true;
			destinationNode = vectorOfNodes.at(positionOfNode);
			return true;
		}
	}

	return false;
}

void Board::placeStartPoint()
{
	int x;
	int y;
	cout << endl;
	cout << "Please enter the X coordinate of the Start Postition: ";
	cin >> x;
	cout << "Please enter the Y coordinate of the Start Postition: ";
	cin >> y;

	if (placeObject(x, y, 2) == true)
	{
		placeObject(x, y, 2);
		return;
	}

	else
	{
		cout << "Invalid Placement! There is an Obsticle here or it is out of bounds!" << endl;
		placeStartPoint();
	}
}

void Board::placeEndPoint()
{
	int x;
	int y;
	cout << endl;
	cout << "Please enter the X coordinate of the End Postition: ";
	cin >> x;
	cout << "Please enter the Y coordinate of the End Postition: ";
	cin >> y;

	if (placeObject(x, y, 3) == true)
	{
		placeObject(x, y, 3);
		return;
	}

	else
	{
		cout << "Invalid Placement! There is an Obsticle here or it is out of bounds!" << endl;
		placeEndPoint();
	}
}

bool Board::isMoveValid(int x, int y)
{
	if (vectorOfNodes.at(((y * ySize) + x)).isObsticle == true)
		return false;

	else
		return true;
}

bool Board::isFinalDestination(int x, int y)
{
	if (vectorOfNodes.at(((y * ySize) + x)).isEndPosition == true)
		return true;

	else
		return false;
}

void Board::calculateHValue(Node finalNode)
{
	for (unsigned int i = 0; i < vectorOfNodes.size(); i++)
	{
		vectorOfNodes.at(i).hValue = (finalNode.x - vectorOfNodes.at(i).x) + (finalNode.y - vectorOfNodes.at(i).y);
	}
	
}

void Board::calculateGValue(Node currentNode)
{
	int maxPosition = ySize * xSize;
	//Calculating the position of the node in the vector
	//The position of the curent Node
	int positionOfNodeCalculation = ((currentNode.y * ySize) + currentNode.x);
	//Position of the Node too the Right of the current Node
	int positionOfRightNode = (positionOfNodeCalculation + 1);
	//Position of the Node too the Left of the current Node
	int positionOfLeftNode = positionOfNodeCalculation - 1;
	//Position of the node Above the current Node
	int positionOfNodeAbove = (positionOfNodeCalculation - xSize);
	//Position of the node Above and too the right of the current Node
	int positionOfNodeAboveRight = (positionOfNodeCalculation - xSize + 1);
	//Position of the node Above and too the right of the current Node
	int positionOfNodeAboveLeft = (positionOfNodeCalculation - xSize - 1);
	//Position of the node Below
	int positionOfNodeBelow = (positionOfNodeCalculation + xSize);
	//Position of the node Below and too the right of the current Node
	int positionOfNodeBelowRight = (positionOfNodeCalculation + xSize + 1);
	//Position of the node Below and too the right of the current Node
	int positionOfNodeBelowLeft = (positionOfNodeCalculation + xSize - 1);

	for (unsigned int i = 0; i < sizeof(vectorOfNodes); i++)
	{
		vectorOfNodes.at(i).parentValue = vectorOfNodes.at(i).gValue;
	}

	//Now sets the GValue of the surrounding nodes
	//Horizontals
	if (vectorOfNodes[positionOfRightNode].x < xSize && vectorOfNodes[positionOfRightNode].y < ySize)
	{
		vectorOfNodes.at(positionOfRightNode).gValue = 10 + vectorOfNodes.at(positionOfRightNode).parentValue;
		vectorOfNodes.at(positionOfRightNode).parentX = currentNode.x;
		vectorOfNodes.at(positionOfRightNode).parentY = currentNode.y;
	}
	if (vectorOfNodes[positionOfLeftNode].x >= 0 && vectorOfNodes[positionOfLeftNode].y < ySize)
	{
		vectorOfNodes.at(positionOfLeftNode).gValue = 10 + vectorOfNodes.at(positionOfLeftNode).parentValue;
		vectorOfNodes.at(positionOfLeftNode).parentX = currentNode.x;
		vectorOfNodes.at(positionOfLeftNode).parentY = currentNode.y;
	}

	//Verticals
	if (vectorOfNodes[positionOfNodeAbove].x < xSize && vectorOfNodes[positionOfNodeAbove].y < ySize)
	{
		vectorOfNodes.at(positionOfNodeAbove).gValue = 10 + vectorOfNodes.at(positionOfNodeAbove).parentValue;
		vectorOfNodes.at(positionOfNodeAbove).parentX = currentNode.x;
		vectorOfNodes.at(positionOfNodeAbove).parentY = currentNode.y;
	}
	if (vectorOfNodes[positionOfNodeBelow].x < xSize && vectorOfNodes[positionOfNodeBelow].y < ySize)
	{
		vectorOfNodes.at(positionOfNodeBelow).gValue = 10 + vectorOfNodes.at(positionOfNodeBelow).parentValue;
		vectorOfNodes.at(positionOfNodeBelow).parentX = currentNode.x;
		vectorOfNodes.at(positionOfNodeBelow).parentY = currentNode.y;
	}

	//Diagonals
	vectorOfNodes.at(positionOfNodeAboveRight).gValue = 14 + vectorOfNodes.at(positionOfNodeAboveRight).parentValue;
	vectorOfNodes.at(positionOfNodeAboveRight).parentX = currentNode.x;
	vectorOfNodes.at(positionOfNodeAboveRight).parentY = currentNode.y;

	vectorOfNodes.at(positionOfNodeAboveLeft).gValue = 14 + vectorOfNodes.at(positionOfNodeAboveLeft).parentValue;
	vectorOfNodes.at(positionOfNodeAboveLeft).parentX = currentNode.x;
	vectorOfNodes.at(positionOfNodeAboveLeft).parentY = currentNode.y;

	vectorOfNodes.at(positionOfNodeBelowRight).gValue = 14 + vectorOfNodes.at(positionOfNodeBelowRight).parentValue;
	vectorOfNodes.at(positionOfNodeBelowRight).parentX = currentNode.x;
	vectorOfNodes.at(positionOfNodeBelowRight).parentY = currentNode.y;

	vectorOfNodes.at(positionOfNodeBelowLeft).gValue = 14 + vectorOfNodes.at(positionOfNodeBelowLeft).parentValue;
	vectorOfNodes.at(positionOfNodeBelowLeft).parentX = currentNode.x;
	vectorOfNodes.at(positionOfNodeBelowLeft).parentY = currentNode.y;


	return;
}

void Board::calculateFValue()
{
	for (unsigned int i = 0; i < vectorOfNodes.size(); i++)
	{
		vectorOfNodes.at(i).fValue = vectorOfNodes.at(i).gValue + vectorOfNodes.at(i).hValue;
	}
}

void Board::aStarAlgorythm(Node currentNode, Node finalNode)
{
	while (currentNode.x != finalNode.x || currentNode.y != finalNode.y)
	{
		if (dynamicArray[currentNode.x][currentNode.y] != start)
		{
			dynamicArray[currentNode.x][currentNode.y] = path;
		}
		
		calculateHValue(finalNode);
		calculateGValue(currentNode);
		calculateFValue();

		int lowestFValue = numeric_limits<int>::max();
		Node locationOfLowestValue;
		for (unsigned int i = 0; i < vectorOfNodes.size(); i++)
		{
			if (vectorOfNodes.at(i).fValue < lowestFValue)
			{
				if (isMoveValid(vectorOfNodes.at(i).x, vectorOfNodes.at(i).y))
				{
					if (vectorOfNodes.at(i).gValue != 0)
					{
						lowestFValue = vectorOfNodes.at(i).fValue;
						locationOfLowestValue = vectorOfNodes.at(i);
					}
				}
				
			}
		}

		currentNode = locationOfLowestValue;
		displayBoard();
		
	}

	
}










