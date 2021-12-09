#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int checkNeighbours(std::vector<std::vector<int>> matrix, int i, int j);
bool visited(int i, int j);
std::vector<std::vector<int>> visitedNodes;

int main()
{
	std::vector<std::vector<int>> matrix;
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		std::vector<int> newRow;
		for (int i = 0; i < input.size(); i++)
			newRow.push_back(input[i] - 48);
		matrix.push_back(newRow);
	}

	std::vector<int> basinSizes;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (j != 0) if (matrix[i][j - 1] <= matrix[i][j]) continue;
			if (i != 0) if (matrix[i - 1][j] <= matrix[i][j]) continue;
			if (j != matrix[i].size() - 1) if (matrix[i][j + 1] <= matrix[i][j]) continue;
			if (i != matrix.size() - 1) if (matrix[i + 1][j] <= matrix[i][j]) continue;
			int basinSize = checkNeighbours(matrix, i, j);
			basinSizes.push_back(basinSize);
		}
	}

	std::sort(basinSizes.begin(), basinSizes.end());

	int multipliedBasins = basinSizes[basinSizes.size() - 1] * basinSizes[basinSizes.size() - 2] * basinSizes[basinSizes.size() - 3];

	std::cout << multipliedBasins;
}

int checkNeighbours(std::vector<std::vector<int>> matrix, int i, int j)
{
	std::vector<int> node = { i,j };
	visitedNodes.push_back(node);
	int basinSize = 1;
	if (j != 0) if (!visited(i, j - 1) && matrix[i][j - 1] != 9) basinSize += checkNeighbours(matrix, i, j - 1);
	if (i != 0) if (!visited(i - 1, j) && matrix[i - 1][j] != 9) basinSize += checkNeighbours(matrix, i - 1, j);
	if (j != matrix[i].size() - 1) if (!visited(i, j + 1) && matrix[i][j + 1] != 9) basinSize += checkNeighbours(matrix, i, j + 1);
	if (i != matrix.size() - 1) if (!visited(i + 1, j) && matrix[i + 1][j] != 9) basinSize += checkNeighbours(matrix, i + 1, j);
	return basinSize;
}

bool visited(int i, int j)
{
	for (int c = 0; c < visitedNodes.size(); c++)
	{
		if (visitedNodes[c][0] == i && visitedNodes[c][1] == j)
			return true;
	}
	return false;
}