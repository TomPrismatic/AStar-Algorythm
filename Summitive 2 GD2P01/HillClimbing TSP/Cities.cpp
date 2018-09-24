#include "Cities.h"
#include <vector>
#include <ctime>  
#include <cstdlib>
#include <iostream>
using namespace std;

void Cities::hillClimbingAlgorythm()
{
	generateRandomDistances(numberOfCities);
	printCityNamesAndDistances();

	previousCost = distanceCalculation(numberOfCities);

	while (previousCost > 0)
	{
		for (int i = 0; i < numberOfCities - 1; ++i)
		{
			swapDistances(i, i + 1);
			newCost = distanceCalculation(numberOfCities);

			if (previousCost > newCost)
			{
				numberOfSwaps++;

				printf("After swap %d: \n", numberOfSwaps);
				for (int i = 0; i < numberOfCities; ++i)
				{
					cout << vectorOfCityDistances.at(i) << endl;
					previousCost = newCost;
				}
			}
			else
			{
				swapDistances(i, i + 1);
			}
		}
	}

	cout << "\nOur journey will look something like this: \n";
	for (int i = 0; i < numberOfCities; ++i)
	{
		cout << vectorOfCityDistances.at(i) << "km." << endl;
	}

	int iTemp = 0;
	cin >> iTemp;
}

void Cities::generateRandomDistances(int numberOfCities)
{
	//Using the time as the random seed
	srand(time(0));
	//Adding each of the city names too the vecotr of names
	vectorOfCityNames.push_back("North Shore");
	vectorOfCityNames.push_back("Auckland");
	vectorOfCityNames.push_back("Christchurch");
	vectorOfCityNames.push_back("Nelson");
	vectorOfCityNames.push_back("Wellington");
	vectorOfCityNames.push_back("Dunedin");

	int temp;
	//Populating the distances of the cities randomly
	for (int i = 0; i < numberOfCities; ++i)
	{
		temp = rand() % 100 + 1;
		vectorOfCityDistances.push_back(temp);
		temp = 0;
	}
}

int Cities::distanceCalculation(int numberOfCities)
{
	//Funtion too compare the distance between locations stored in the vector
	int distance = 0;

	//Loops through the vector, if the distance at location j is higher than that of the location at i the distance variable increases
	for (int i = 0; i < numberOfCities; ++i)
	{
		for (int j = i + 1; j < numberOfCities; ++j)
		{
			if (vectorOfCityDistances.at(j) < vectorOfCityDistances.at(i))
			{
				distance++;
			}
		}
	}
	return distance;
}

void Cities::swapDistances(int x, int y)
{
	//Swaps the distance at location x with the distance at location y
	int temp = vectorOfCityDistances.at(x);
	vectorOfCityDistances.at(x) = vectorOfCityDistances.at(y);
	vectorOfCityDistances.at(y) = temp;
}

void Cities::printCityNamesAndDistances()
{
	//Prints the names of the cities in the vectorOfCityNames
	cout << "List of cities: \n";
	for (auto i = vectorOfCityNames.begin(); i != vectorOfCityNames.end(); ++i)
	{	
		std::cout << *i << ' ' << "\n";		
	}
	//Prints the distances of the cities in the vectorOfCityDistances
	cout << "Distances of these Cities: \n";
	for (auto j = vectorOfCityDistances.begin(); j != vectorOfCityDistances.end(); ++j)
	{
		std::cout << *j << ' ';
	}

}

Cities::Cities()
{
}


Cities::~Cities()
{
}
