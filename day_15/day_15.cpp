#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

class node {
public:
	std::vector<std::pair<int, int>> neighbours;
	int risk;
	bool visited = false;
	int distance = INT_MAX;
	bool isGoal = false;
};

void parseInput();
int dijkstra(int x, int y);
std::vector<std::vector<node>> nodes;

int main()
{
	parseInput();
	auto start_time = std::chrono::high_resolution_clock::now();
	int result = dijkstra(0, 0);
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Risk level: " << result << std::endl;
	auto time = end_time - start_time;
	std::cout << "Time elapsed: " << time / std::chrono::milliseconds(1) << "ms";
}

node* miniDist()
{
	int minimum = INT_MAX;
	node* result = nullptr;

	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes.size(); j++)
		{
			if (nodes[i][j].visited == false && nodes[i][j].distance <= minimum)
			{
				minimum = nodes[i][j].distance;
				result = &nodes[i][j];
			}
		}
	}
	return result;
}


int dijkstra(int x, int y)
{
	int visitCount = 0;
	int maxVisits = nodes.size() * nodes[0].size();
	nodes[x][y].distance = 0;
	while (visitCount < maxVisits)
	{
		node* m = miniDist();
		m->visited = true;
		visitCount++;

		if (m->isGoal)
			return m->distance;

		for (std::pair<int, int> n : m->neighbours)
		{
			int alt = m->distance + nodes[n.first][n.second].risk;
			if (alt < nodes[n.first][n.second].distance)
				nodes[n.first][n.second].distance = alt;
		}

	}
	return nodes[nodes.size() - 1][nodes[0].size() - 1].distance;
}

int rowLength = -1;
std::vector<std::pair<int, int>> getNeighbours(int x, int y)
{
	std::vector<std::pair<int, int>> neighbours;
	if (x > 0) neighbours.emplace_back(x - 1, y);
	if (x < nodes[0].size() - 1) neighbours.emplace_back(x + 1, y);
	if (y > 0) neighbours.emplace_back(x, y - 1);
	if (y < nodes.size() - 1) neighbours.emplace_back(x, y + 1);
	return neighbours;
}

void parseInput()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		std::vector<node> nodeInput;
		for (int i = 0; i < input.size(); i++) {
			node currentNode;
			currentNode.risk = input[i] - 48;
			nodeInput.push_back(currentNode);
		}
		nodes.push_back(nodeInput);
	}

	for (int i = 0; i < nodes.size(); i++) {
		for(int j = 0; j < nodes[i].size(); j++)
			nodes[i][j].neighbours = getNeighbours(i, j);
	}
}