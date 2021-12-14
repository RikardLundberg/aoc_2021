#include <iostream>
#include <string>
#include <vector>

void parseInput();
void addPolym(std::string polym, std::vector<std::pair<std::string, int>>& polymer);

std::vector<std::pair<std::string, std::string>> rules;
std::vector<std::pair<std::string, int>> currentPolymer;
std::string first, last;

int main()
{
	parseInput();
	int steps = 10;

	for (int i = 0; i < steps; i++)
	{
		std::vector<std::pair<std::string, int>> newPolymer;
		for (int i = 0; i < currentPolymer.size(); i++)
		{
			if (currentPolymer[i].second > 0)
			{
				for (auto rule : rules) {
					if (rule.first == currentPolymer[i].first) {
						for (int j = 0; j < currentPolymer[i].second; j++) {
							auto first = currentPolymer[i].first.substr(0, 1) + rule.second;
							auto second = rule.second + currentPolymer[i].first.substr(1);
							addPolym(first, newPolymer);
							addPolym(second, newPolymer);
						}
					}
				}
			}
		}
		currentPolymer = newPolymer;
	}

	std::vector<std::pair<std::string, int>> countPolymer;
	for (auto polymPair : currentPolymer)
	{
		for (int i = 0; i < polymPair.second; i++) {
			addPolym(polymPair.first.substr(0, 1), countPolymer);
			addPolym(polymPair.first.substr(1), countPolymer);
		}
	}

	int high = -1, low = -1;
	for (auto polymPair : countPolymer)
	{
		int compareVal = polymPair.second;
		if (polymPair.first == first)
			compareVal++;
		if (polymPair.first == last)
			compareVal++;
		compareVal /= 2;
		if (compareVal > high)
			high = compareVal;
		if (compareVal < low || low == -1)
			low = compareVal;
	}

	std::cout << "Polymer output: " << high - low;
}


void parseInput()
{
	std::string input, startVal;
	std::cin >> startVal;
	while (std::cin >> input && input != "eof")
	{
		std::string input2;
		std::cin >> input2;
		std::cin >> input2;
		std::pair<std::string, std::string> rule;
		rule.first = input;
		rule.second = input2;
		rules.push_back(rule);
	}

	/*for (auto rule : rules)
	{
		std::pair<std::string, int> possibleVal;
		possibleVal.first = rule.first;
		possibleVal.second = 0;
		currentPolymer.push_back(possibleVal);
	}*/

	std::string previous = "/";
	for (int i = 0; i < startVal.size(); i++)
	{
		if (previous != "/")
		{
			std::string current = previous + startVal[i];
			addPolym(current, currentPolymer);
		}
		previous = startVal[i];
	}
	first = startVal[0];
	last = startVal[startVal.size() - 1];
}


void addPolym(std::string polym, std::vector<std::pair<std::string, int>>& polymer)
{
	for (auto &poly : polymer) {
		if (poly.first == polym) {
			poly.second++;
			return;
		}
	}
	polymer.emplace_back(polym, 1);
}
