#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

class node {
public:
	//std::vector<node*> neighbours;
	std::vector<std::pair<int, int>> neighbours;
	int risk;
	bool visited = false;
	int distance = INT_MAX;
	bool isGoal = false;
};

void parseInput();
int dijkstra(int x, int y);
//std::vector<int> risks;
//std::vector<std::vector<int>> risks;
//std::vector<std::vector<std::vector<std::pair<int, int>>>> neighbours;
std::vector<std::vector<node>> nodes;

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();
	parseInput();
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
		{
			return m->distance;
		}

		for (std::pair<int, int> n : m->neighbours)
		{
			//node* neighbour = &nodes[n.first][n.second];
			int alt = m->distance + nodes[n.first][n.second].risk;
			if (alt < nodes[n.first][n.second].distance)
			{
				nodes[n.first][n.second].distance = alt;
				//prev[neighbour.first][neighbour.second] = m;
			}
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
	/*if (position > 0 && (position - 1 % rowLength) < rowLength - 1)
		neighbours.push_back(&nodes[position - 1]);
	if (position < nodes.size() - 1 && position + 1 % rowLength != 0)
		neighbours.push_back(&nodes[position + 1]);
	if (position - rowLength > 0)
		neighbours.push_back(&nodes[position - rowLength]);
	if (position + rowLength < nodes.size())
		neighbours.push_back(&nodes[position + rowLength]);*/
	return neighbours;
}

void parseInput()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		//rowLength = input.size();
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

/*void parseInput()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		rowLength = input.size();
		std::vector<int> riskInput;
		for (int i = 0; i < input.size(); i++)
			riskInput.push_back(input[i] - 48);
		risks.push_back(riskInput);
	}
	for (int i = 0; i < risks.size(); i++) {
		std::vector<std::vector<std::pair<int, int>>> neighbourInputs;
		for (int j = 0; j < risks[i].size(); j++) {
			std::vector<std::pair<int, int>> neighboursInput = getNeighbours(i, j);
			neighbourInputs.push_back(neighboursInput);
		}
		neighbours.push_back(neighbourInputs);
	}
}*/

