#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

class node {
public:
	//std::vector<node*> neighbours;
	int risk;
	bool visited = false;
	bool isGoal = false;
};

//std::vector<node> parseInput();
void parseInput();

//node bfs(node start);
//void visitNeighbours(node& node, int totalRisk);
void djikstra(int pos);
int dijkstra(int pos);

std::vector<bool> visited;
std::vector<int> risks;
int rowLength = -1;
//void visitNeighbours2(int position, std::string path, int totalRisk);
int lowestTotalRisk = -1;


//std::vector<node> nodes;

int main()
{
	parseInput();
	int result = dijkstra(0);
	//node start = nodes[0];
	//nodes[nodes.size() - 1].isGoal = true;
	

	//parseInput();
	//visitNeighbours2(0, "", 0);

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
		//dijkstraQ.push(i);
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
			/*int totalRisk = 0;
			if (prev[m] != -1)
			{
				int tmpPos = prev[m];
				while (tmpPos != -1)
				{
					totalRisk += distance[tmpPos];
					tmpPos = prev[tmpPos];
				}
				return totalRisk;
			}*/
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

	/*for (int i = 0; i < rowLength; i++)
	{
		int m = miniDist(distance, visited);
		visited[m] = true;
		for (int i = 0; i < rowLength; i++)
		{
			if (!visited[i] && risks[i] && distance[m] != INT_MAX && distance[m] + risks[i] < distance[i])
				distance[i] = distance[m] + risks[i];
		}
	}*/
	return distance[risks.size() - 1];
}

void djikstra(int pos)
{
	std::vector<int> distance;
	std::vector<bool> visited;

	for (int i = 0; i < risks.size(); i++)
	{
		distance.push_back(INT_MAX);
		visited.push_back(false);
	}

	distance[pos] = 0;        

	for (int i = 0; i < rowLength; i++)
	{
		int m = miniDist(distance, visited);
		visited[m] = true;
		//std::vector<int> neighbours = getNeighbours(i);
		//for (int j = 0; j < neighbours.size(); j++)
		for (int i = 0; i < rowLength; i++)
		{
			// updating the distance of neighbouring vertex
			//if (!visited[neighbours[j]] && risks[neighbours[j]] && distance[m] != INT_MAX && distance[m] + risks[neighbours[j]] < distance[j])
			//	distance[j] = distance[m] + risks[neighbours[j]];
			if (!visited[i] && risks[i] && distance[m] != INT_MAX && distance[m] + risks[i] < distance[i])
				distance[i] = distance[m] + risks[i];
		}
	}
	std::cout << distance[risks.size() - 1];
}



/*void visitNeighbours2(int position, std::string path, int totalRisk)
{
	if (lowestTotalRisk != -1 && totalRisk > lowestTotalRisk)
		return;
	path += std::to_string(position) + ",";
	if(position != 0)
		totalRisk += risks[position];
	if (position == risks.size() - 1)
	{
		if (lowestTotalRisk == -1 || totalRisk < lowestTotalRisk)
			lowestTotalRisk = totalRisk;
		return;
	}

	std::vector<int> neighbours = getNeighbours(position);

	for (int pos : neighbours)
	{
		bool visitNeighbour = true;
		if (path.find("," + std::to_string(pos) + ",") != std::string::npos)
			visitNeighbour = false;
		//if (visited[pos])
		//	continue;
		//visited[pos] = true;
		if(visitNeighbour)
			visitNeighbours2(pos, path, totalRisk);
	}
}*/


/*void visitNeighbours(node& node, int totalRisk)
{
	totalRisk += node.risk;
	if (node.isGoal)
	{
		if (lowestTotalRisk == -1 || totalRisk < lowestTotalRisk)
			lowestTotalRisk = totalRisk;
		return;
	}

	for (int i = 0; i < node.neighbours.size(); i++)
	{
		if (node.neighbours[i]->visited)
			continue;
		node.neighbours[i]->visited = true;
		visitNeighbours(*node.neighbours[i], totalRisk);
	}
}*/

/*node bfs(node start)
{
	std::queue<node> queue;
	start.visited = true;
	queue.push(start);
	node currentNode;
	while (!queue.empty())
	{
		currentNode = queue.front();
		queue.pop();
		for(node neighbour : currentNode.neighbours)
			if (!neighbour.visited) {
				neighbour.visited = true;
				queue.push(neighbour);
			}
	}
}*/

void parseInput()
{
	std::string input;
	//int current_y = 0;
	while (std::cin >> input && input != "eof")
	{
		rowLength = input.size();
		for (int i = 0; i < input.size(); i++)
		{
			risks.push_back(input[i] - 48);
			visited.push_back(false);
		}
		//current_y++;
	}
}


/*void parseInput()
{
	std::string input;
	//int rowLength = -1;
	int current_y = 0;
	std::vector<std::vector<int>> risks;
	while (std::cin >> input && input != "eof")
	{
		rowLength = input.size();
		std::vector<int> riskInput;
		for (int i = 0; i < input.size(); i++)
		{
			riskInput.push_back(input[i] - 48);
		}
		risks.push_back(riskInput);
		current_y++;
	}

	for (int i = 0; i < risks.size(); i++) {
		for (int j = 0; j < risks[i].size(); j++)
		{
			node node;
			node.risk = risks[i][j];
			/*if (j > 0) {
				node.neighbours.push_back(&nodes[nodes.size() - 1]);
				nodes[nodes.size() - 1].neighbours.push_back(&node);
			}
			if (nodes.size() > rowLength)
			{
				node.neighbours.push_back(&nodes[nodes.size() - rowLength - 1]);
				nodes[nodes.size() - rowLength - 1].neighbours.push_back(&node);
			}*/
			/*nodes.push_back(node);
		}
	}
}*/







