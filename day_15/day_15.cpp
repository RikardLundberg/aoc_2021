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
std::chrono::time_point<std::chrono::steady_clock> start_time;

int main()
{
	parseInput();
	std::cout << "Finished parsing, starting clock.." << std::endl;
	start_time = std::chrono::high_resolution_clock::now();
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
		if ((visitCount % 1000) == 0) {
			std::cout << "Visitcount is now.. " << visitCount << ", TotalTime elapsed: " << (std::chrono::high_resolution_clock::now() - start_time) / std::chrono::milliseconds(1) << "ms" << std::endl;
		}
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
	std::vector<std::string> inputs;
	while (std::cin >> input && input != "eof") {
		int startSize = input.size();
		for (int j = 1; j < 5; j++) {
			for (int i = 0; i < startSize; i++)
			{
				int inp = input[i] - 48 + j;
				if (inp > 9) inp -= 9;
				input += std::to_string(inp);
			}
		}
		inputs.push_back(input);
	}

	std::vector<std::string> extraInputs;
	for (int j = 1; j < 5; j++)
	{
		int startSize = inputs.size();
		for (std::string newInput : inputs)
		{
			std::string extraInput;
			for (int i = 0; i < newInput.size(); i++) {
				int inp = newInput[i] - 48 + j;
				if (inp > 9) inp -= 9;
				extraInput += std::to_string(inp);
			}
			extraInputs.push_back(extraInput);
		}
	}

	for (std::string str : extraInputs)
		inputs.push_back(str);

	//while (std::cin >> input && input != "eof")
	for(std::string finalInput : inputs)
	{
		std::vector<node> nodeInput;
		for (int i = 0; i < finalInput.size(); i++) {
			node currentNode;
			currentNode.risk = finalInput[i] - 48;
			nodeInput.push_back(currentNode);
		}
		nodes.push_back(nodeInput);
	}

	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes[i].size(); j++)
			nodes[i][j].neighbours = getNeighbours(i, j);
	}
}