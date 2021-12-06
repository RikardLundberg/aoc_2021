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

	std::vector<long long int> fishSizes;
	for (int i = 1; i < 6; i++) {
		std::cout << "Calculating fish.. " << i;
		fishSizes.push_back(CalculateFishChildren(i+1, days));
		std::cout << " ... " << fishSizes[i-1] << std::endl;
	}
	/*
	fishSizes.push_back(6206821033);
	fishSizes.push_back(5617089148);
	fishSizes.push_back(5217223242);
	fishSizes.push_back(4726100874);
	fishSizes.push_back(4368232009);
	*/

	long long int totalCount = 0;
	for (int fish : fishes)
	{
		totalCount += fishSizes[fish-1];
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