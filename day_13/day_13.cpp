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

	int high_x = 0;
	int high_y = 0;
	for (auto coord : coords)
	{
		if (coord[0] > high_x)
			high_x = coord[0];
		if (coord[1] > high_y)
			high_y = coord[1];
	}

	int n = 0;
	std::vector<int> currCoord = coords[n]; //they are sorted
	std::vector<std::string> outputRows;
	for (int i = 0; i < high_y + 1; i++)
		outputRows.push_back("");
	for (int i = 0; i < high_x + 1; i++)
	{
		for (int j = 0; j < high_y + 1; j++)
		{
			if (currCoord[0] == i && currCoord[1] == j)
			{
				outputRows[j] += "#";
				if (n < coords.size() - 1)
					currCoord = coords[++n];
				else
					break;
			}
			else
				outputRows[j] += ".";
		}
	}
	for (int i = 0; i < outputRows.size(); i++)
	{
		std::cout << outputRows[i] << std::endl;
	}
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