#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void fold_x(int x);
void fold_y(int y);
void removeDuplicates();

std::vector<std::vector<int>> coords;
int main()
{
	std::string input;
	while (std::cin >> input && input != "fold")
	{
		std::vector<int> coord;
		coord.push_back(std::stoi(input.substr(0, input.find(','))));
		coord.push_back(std::stoi(input.substr(input.find(',') + 1)));
		coords.push_back(coord);
	}

	while (std::cin >> input && input != "eof")
	{
		if (input == "fold" || input == "along")
			continue;
		if (input.substr(0, 1) == "x")
			fold_x(std::stoi(input.substr(2)));
		else
			fold_y(std::stoi(input.substr(2)));
		removeDuplicates();
	}

	std::cout << "Coord count: " << coords.size();
}

void fold_x(int x)
{
	for (auto &coord : coords)
	{
		if (coord[0] > x)
		{
			int diff = coord[0] - x;
			coord[0] = x - diff;
		}
	}
}

void fold_y(int y)
{
	for (auto &coord : coords)
	{
		if (coord[1] > y)
		{
			int diff = coord[1] - y;
			coord[1] = y - diff;
		}
	}
}

void removeDuplicates()
{
	std::sort(coords.begin(), coords.end(),
		[](const std::vector<int>& first, const std::vector<int>& second) {
			if (first[0] != second[0]) {
				return first[0] < second[0];
			}
			return first[1] < second[1];
		});
	std::vector<int> prevCoord = {-1,-1};
	std::vector<int> markedForDeletion;
	for (int i = 0; i < coords.size(); i++)
	{
		if (coords[i][0] == prevCoord[0] && coords[i][1] == prevCoord[1])
			markedForDeletion.push_back(i);
		else
			prevCoord = coords[i];
	}

	for (int i = markedForDeletion.size() - 1; i >= 0; i--)
		coords.erase(coords.begin() + markedForDeletion[i]);
}