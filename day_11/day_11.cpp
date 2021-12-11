#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void increaseNeighbours(int i, int j);
void increaseNeighbour(int i, int j);
std::vector<std::vector<int>> matrix;

int main()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		std::vector<int> newRow;
		for (int i = 0; i < input.size(); i++)
			newRow.push_back(input[i] - 48);
		matrix.push_back(newRow);
	}

	int currentStep = 0;
	int flashAmount = matrix.size() * matrix[0].size();
	while (true) {
		int flashCount = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j]++;
				if (matrix[i][j] == 10)
					increaseNeighbours(i, j);
			}
		}
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (matrix[i][j] > 9)
				{
					flashCount++;
					matrix[i][j] = 0;
				}
			}
		}
		currentStep++;
		if (flashCount == flashAmount)
			break;
	}

	std::cout << currentStep;
}


void increaseNeighbours(int i, int j)
{
	if (j != 0) increaseNeighbour(i, j - 1);
	if (j != 0 && i != 0) increaseNeighbour(i - 1, j - 1);
	if (j != 0 && i != matrix[i].size() - 1) increaseNeighbour(i + 1, j - 1);

	if (j != matrix.size() - 1) increaseNeighbour(i, j + 1);
	if (j != matrix.size() - 1 && i != 0) increaseNeighbour(i - 1, j + 1);
	if (j != matrix.size() - 1 && i != matrix[i].size() - 1) increaseNeighbour(i + 1, j + 1);

	if (i != 0) increaseNeighbour(i - 1, j);
	if (i != matrix.size() - 1) increaseNeighbour(i + 1, j);
}

void increaseNeighbour(int i, int j)
{
	matrix[i][j]++;

	if (matrix[i][j] == 10) {
		increaseNeighbours(i, j);
	}
}