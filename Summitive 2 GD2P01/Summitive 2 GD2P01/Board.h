#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <vector>
#include <random>
#include <array>

class Board
{

	struct Node
	{
		int y;
		int x;
		bool isObsticle = false;
		bool isStartPosition = false;
		bool isEndPosition = false;
		int parentX;
		int parentY;
		int parentValue = 0;
		float gValue = 0;
		float hValue;
		float fValue;
	};

	std::vector <Node> vectorOfNodes;

	Node destinationNode;
	Node startNode;
	Node currentNode;

public:
	Board();
	~Board();

	void generateMenu();

	void generateBoard();

	void displayBoard();

	void insertObsticles();

	bool placeObject(int x, int y, int typeToPlace);

	void placeStartPoint();

	void placeEndPoint();

	bool isMoveValid(int x, int y);

	bool isFinalDestination(int x, int y);

	void calculateHValue(Node finalNode);

	void calculateGValue(Node currentNode);

	void calculateFValue();

	void aStarAlgorythm(Node currentNode, Node finalNode);
};

