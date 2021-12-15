#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

void parseInput();
int dijkstra(int x, int y);
//std::vector<int> risks;
std::vector<std::vector<int>> risks;
std::vector<std::vector<std::vector<std::pair<int, int>>>> neighbours;

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();
	parseInput();
	int result = dijkstra(0,0);
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Risk level: " << result << std::endl;
	auto time = end_time - start_time;
	std::cout << "Time elapsed: " << time / std::chrono::milliseconds(1) << "ms";
}

std::pair<int, int> miniDist(std::vector<std::vector<int>> distance, std::vector<std::vector<bool>> visited)
{
	int minimum = INT_MAX, ind;
	std::pair<int, int> result;

	for (int i = 0; i < risks.size(); i++)
	{
		for (int j = 0; j < risks[i].size(); j++) {
			if (visited[i][j] == false && distance[i][j] <= minimum)
			{
				minimum = distance[i][j];
				result.first = i;
				result.second = j;
			}
		}
	}
	return result;
}


int dijkstra(int x, int y)
{
	std::vector<std::vector<int>> distance;
	std::vector<std::vector<bool>> visited;
	//std::vector<std::vector<std::pair<int, int>>> prev;

	for (int i = 0; i < risks.size(); i++) {
		std::vector<int> distTmp;
		std::vector<bool> visitTmp;
		std::vector<int> prevTmp;
		for (int j = 0; j < risks[i].size(); j++) {
			distTmp.push_back(INT_MAX);
			visitTmp.push_back(false);
			prevTmp.push_back(-1);
		}
		distance.push_back(distTmp);
		visited.push_back(visitTmp);
		//prev.push_back(prevTmp);
	}

	distance[x][y] = 0;

	int visitCount = 0;
	int maxVisits = risks.size() * risks[0].size();
	while (visitCount < maxVisits)
	{
		std::pair<int, int> m = miniDist(distance, visited);
		visited[m.first][m.second] = true;
		visitCount++;

		if (m.first == risks.size() - 1 && m.second == risks[0].size() - 1)
		{
			return distance[m.first][m.second];
		}

		for (std::pair<int, int> neighbour : neighbours[m.first][m.second])
		{
			int alt = distance[m.first][m.second] + risks[neighbour.first][neighbour.second];
			if (alt < distance[neighbour.first][neighbour.second])
			{
				distance[neighbour.first][neighbour.second] = alt;
				//prev[neighbour.first][neighbour.second] = m;
			}
		}

	}
	return distance[risks.size() - 1][risks[0].size() - 1];
}

int rowLength = -1;
std::vector<std::pair<int, int>> getNeighbours(int x, int y)
{
	std::vector<std::pair<int, int>> neighbours;
	if (x > 0) neighbours.emplace_back(x - 1, y);
	if (x < risks[0].size() - 1) neighbours.emplace_back(x + 1, y);
	if (y > 0) neighbours.emplace_back(x, y - 1);
	if (y < risks.size() - 1) neighbours.emplace_back(x, y + 1);
	/*if (position > 0 && (position - 1 % rowLength) < rowLength - 1)
		neighbours.push_back(position - 1);
	if (position < risks.size() - 1 && position + 1 % rowLength != 0)
		neighbours.push_back(position + 1);
	if (position - rowLength > 0)
		neighbours.push_back(position - rowLength);
	if (position + rowLength < risks.size())
		neighbours.push_back(position + rowLength);*/
	return neighbours;
}

void parseInput()
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
}

