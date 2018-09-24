#pragma once
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


class Cities
{
	const int numberOfCities = 6;
	std::vector <int> vectorOfCityDistances;
	std::vector <const char*> vectorOfCityNames;
	int previousCost;
	int newCost;
	int numberOfSwaps;

public:
	void hillClimbingAlgorythm();

	void generateRandomDistances(int numberOfCities);

	int distanceCalculation(int numberOfCities);

	void swapDistances(int x, int y);

	void printCityNamesAndDistances();

	Cities();
	~Cities();

};


