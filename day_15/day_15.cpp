#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

void parseInput();
int dijkstra(int pos);
std::vector<int> risks;
int rowLength = -1;

int main()
{
	parseInput();
	int result = dijkstra(0);
	std::cout << "Risk level: " << result;
}

int miniDist(std::vector<int> distance, std::vector<bool> visited)
{
	int minimum = INT_MAX, ind;

	for (int i = 0; i < risks.size(); i++)
	{
		if (visited[i] == false && distance[i] <= minimum)
		{
			minimum = distance[i];
			ind = i;
		}
	}
	return ind;
}

std::vector<int> getNeighbours(int position)
{
	std::vector<int> neighbours;
	if (position > 0 && (position - 1 % rowLength) < rowLength - 1)
		neighbours.push_back(position - 1);
	if (position < risks.size() - 1 && position + 1 % rowLength != 0)
		neighbours.push_back(position + 1);
	if (position - rowLength > 0)
		neighbours.push_back(position - rowLength);
	if (position + rowLength < risks.size())
		neighbours.push_back(position + rowLength);
	return neighbours;
}


int dijkstra(int pos)
{
	std::vector<int> distance;
	std::vector<bool> visited;
	std::vector<int> prev;

	for (int i = 0; i < risks.size(); i++)
	{
		distance.push_back(INT_MAX);
		visited.push_back(false);
		prev.push_back(-1);
	}

	distance[pos] = 0;

	int visitCount = 0;
	while (visitCount < risks.size()-1)
	{
		int m = miniDist(distance, visited);
		visited[m] = true;
		visitCount++;

		if (m == risks.size() - 1)
		{
			return distance[risks.size() - 1];
		}

		std::vector<int> neighbours = getNeighbours(m);
		for (int neighbour : neighbours)
		{
			int alt = distance[m] + risks[neighbour];
			if (alt < distance[neighbour])
			{
				distance[neighbour] = alt;
				prev[neighbour] = m;
			}
		}

	}
	return distance[risks.size() - 1];
}

void parseInput()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		rowLength = input.size();
		for (int i = 0; i < input.size(); i++)
			risks.push_back(input[i] - 48);
	}
}

