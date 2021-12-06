#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

long long int CalculateFishChildren(int daysPassed, int days);

int main()
{
	int days = 256;

	std::string fishString;
	std::vector<int> fishes;
	std::cin >> fishString;
	while (fishString.find(',') != std::string::npos)
	{
		fishes.push_back(std::stoi(fishString.substr(0,fishString.find(','))));
		fishString = fishString.substr(fishString.find(',') + 1);
	}
	fishes.push_back(std::stoi(fishString));

	long long int totalCount = 0;
	for (int fish : fishes) {
		//totalCount++;
		std::cout << "Calculating fish.. " << fish;
		totalCount += CalculateFishChildren(fish+1, days);
		std::cout << " ... " << totalCount << std::endl;
	}

	std::cout << "Number of lanternfish: " << totalCount;
}

long long int CalculateFishChildren(int daysPassed, int days)
{
	long long int totalCount = 1;
	while (daysPassed <= days)
	{
		totalCount += CalculateFishChildren(9+daysPassed, days);
		daysPassed += 7;
	}
	return totalCount;
}