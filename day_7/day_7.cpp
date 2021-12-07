#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

int main()
{
	std::string crabString;
	std::vector<int> crabs;
	std::cin >> crabString;
	int highestCrabPos = 0;
	while (crabString.find(',') != std::string::npos)
	{
		int newCrab = std::stoi(crabString.substr(0, crabString.find(',')));
		if (newCrab > highestCrabPos) highestCrabPos = newCrab;
		crabs.push_back(newCrab);
		crabString = crabString.substr(crabString.find(',') + 1);
	}
	crabs.push_back(std::stoi(crabString));

	int lowestFuelCount = -1;
	for (int i = 0; i < highestCrabPos; i++)
	{
		int totalFuelCost = 0;
		for (int crab : crabs)
		{
			int crabDistance = crab - i;
			if (crabDistance < 0)
				crabDistance *= -1;

			int fuelCost = 0;
			for (int j = 1; j < crabDistance + 1; j++)
				fuelCost += j;
			
			totalFuelCost += fuelCost;
		}

		if (lowestFuelCount == -1 || totalFuelCost < lowestFuelCount)
			lowestFuelCount = totalFuelCost;
		else if (lowestFuelCount < totalFuelCost)
			break;
	}

	std::cout << lowestFuelCount;

}
