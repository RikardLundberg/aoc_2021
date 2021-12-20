#include <iostream>
#include <string>
#include <vector>

using namespace std;

//vector<string> parseInput();
//string add(string first, string second);
//void reduce(string& input);
//int getMagnitude(std::string input);


int nodeId = 0;

class node {
public:
	std::vector<node> nodes;
	int firstLit = -1;
	int secondLit = -1;
	int id;
};

vector<node> nodes;
void parseInput();
node add(node first, node second);
void reduce(node& input);
long long int getMagnitude(node& input);

int explosions = 0;
int splitL = 0;
int splitR = 0;
int lookingForLow = 0;
int foundLow = 0;
int changedFirst = 0;
int dismissed = 0;
int explosionHandledCount = 0;

int main()
{
	parseInput();

	long long int highestMag = -1;

	
	for (int i = 0; i < nodes.size(); i++)
	{
		node sumNode = nodes[i];
		for (int j = 0; j < nodes.size(); j++) {
			if (i == j)
				continue;
			node addNode = add(sumNode, nodes[j]);
			reduce(addNode);
			long long int addNodeMag = getMagnitude(addNode);
			if (highestMag < addNodeMag)
				highestMag = addNodeMag;
		}
	}

	for (int i = nodes.size() - 1; i > 0; i--)
	{
		node sumNode = nodes[i];
		for (int j = nodes.size() - 1; j > 0; j--) {
			if (i == j)
				continue;
			node addNode = add(sumNode, nodes[j]);
			reduce(addNode);
			long long int addNodeMag = getMagnitude(addNode);
			if (highestMag < addNodeMag)
				highestMag = addNodeMag;
		}
	}

	std::cout << "Final magnitude is: " << highestMag;
}

long long int getMagnitude(node& input)
{
	long long int returnVal = 0;
	if (input.firstLit == -1)
		returnVal += 3 * getMagnitude(input.nodes[0]);
	else
		returnVal += (3 * input.firstLit);

	int secondNodeLoc = input.nodes.size() > 1 ? 1 : 0;

	if (input.secondLit == -1)
		returnVal += 2 * getMagnitude(input.nodes[secondNodeLoc]);
	else
		returnVal += (2 * input.secondLit);

	return returnVal;
}

node split(int input) {
	node newNode;
	newNode.id = ++nodeId;
	int first = input / 2;
	newNode.firstLit = first;
	newNode.secondLit = input % (first)+first;
	return newNode;
}

int changeLower = -1;
int changeHigher = -1;
bool explosionHandled = true;
int lastNumberId = -1;
int changeId = -1;
bool changeFirst = true;

bool changed = true;
bool splitting = false;


void reduceNode(node& input, int level)
{
	//explode
	if (level > 4) {
		if (changeLower == -1 && changeHigher == -1 && !changed && level > 3) {
			if (input.firstLit == -1 || input.secondLit == -1) {
				cout << "heeeee";
				throw;
			}
			explosions++;
			changeLower = input.firstLit;
			if (lastNumberId != -1) {
				changeId = lastNumberId;
			}
			changeHigher = input.secondLit;
			explosionHandled = false;
			changed = true;
			return;
		}
	}

	if (changed && changeHigher == -1)
		return;


	if (input.firstLit != -1 && changeHigher != -1)
	{
		input.firstLit += changeHigher;
		changeHigher = -1;
	}

	std::vector<int> removeElements;
	bool explosionImmunity = false;
	int secondNodeLoc = input.nodes.size() > 1 ? 1 : 0;
	if (input.firstLit == -1) {
		reduceNode(input.nodes[0], level + 1);
		if (!explosionHandled)
		{
			removeElements.push_back(0);
			input.firstLit = 0;
			explosionHandled = true;
			if (input.secondLit != -1 && changeHigher != -1) {
				input.secondLit += changeHigher;
				changeHigher = -1;
			}
			if (changeId == -1) {
				dismissed++;
				changeLower = -1;
			}
			explosionHandledCount++;
		}
	}
	else //if (!explosionImmunity)
	{
		changeFirst = true;
		lastNumberId = input.id;
	}


	if (input.secondLit != -1 && changeHigher != -1)
	{
		input.secondLit += changeHigher;
		changeHigher = -1;
	}

	if (input.secondLit == -1) {
		reduceNode(input.nodes[secondNodeLoc], level + 1);
		if (!explosionHandled)
		{
			removeElements.push_back(secondNodeLoc);
			input.secondLit = 0;
			explosionHandled = true;
			explosionImmunity = true;
			if (input.firstLit != -1 && changeLower != -1) {
				input.firstLit += changeLower;
				changeId = -1;
				changeLower = -1;
				changedFirst++;
			}
			else if (changeId == -1) {
				dismissed++;
				changeLower = -1;
			}
			explosionHandledCount++;
		}
	}
	else //if (!explosionImmunity)
	{
		changeFirst = false;
		lastNumberId = input.id;
	}

	for (int i = removeElements.size() - 1; i >= 0; i--)
		input.nodes.erase(input.nodes.begin() + removeElements[i]);

}


void changeLowerOnId(node& input) {
	if (input.id == changeId)
	{
		if (input.secondLit != -1 && changeLower != -1)
		{
			input.secondLit += changeLower;
			changeLower = -1;
			foundLow++;
		}
		else if (input.firstLit != -1 && changeLower != -1)
		{
			input.firstLit += changeLower;
			changeLower = -1;
			foundLow++;
		}
	}
	else
		for (node& n : input.nodes)
			changeLowerOnId(n);
}

string buildDebugString(node input)
{
	string retVal = "[";
	retVal += input.firstLit > -1 ? to_string(input.firstLit) + "," : buildDebugString(input.nodes[0]) + ",";
	//int secondNodeLoc = input.firstLit > -1 ? 1 : 0;
	int secondNodeLoc = input.nodes.size() > 1 ? 1 : 0;
	retVal += input.secondLit > -1 ? to_string(input.secondLit) : buildDebugString(input.nodes[secondNodeLoc]);
	return retVal += "]";
}

void splitReduceNode(node& input)
{
	if (!changed) {
		if (input.firstLit > -1 && input.firstLit > 9)
		{
			splitL++;
			node newNode = split(input.firstLit);
			newNode.id = ++nodeId;
			vector<node> newNodes;
			newNodes.push_back(newNode);
			for (node n : input.nodes)
				newNodes.push_back(n);
			input.nodes = newNodes;
			input.firstLit = -1;
			changed = true;
		}
		else if(input.firstLit == -1)
			splitReduceNode(input.nodes[0]);

		int secondNodeLoc = input.nodes.size() > 1 ? 1 : 0;


		if (!changed) {
			if (input.secondLit > -1 && input.secondLit > 9)
			{
				splitR++;
				node newNode = split(input.secondLit);
				newNode.id = ++nodeId;
				input.nodes.push_back(newNode);
				input.secondLit = -1;
				changed = true;
			}
			else if (input.secondLit == -1)
				splitReduceNode(input.nodes[secondNodeLoc]);
		}
	}
}

void reduce(node& input)
{
	int level = 1;
	std::cout << endl << "Add: " << endl;
	string debugString = buildDebugString(input);
	std::cout << debugString << endl;
	std::cout << endl;
	std::cout << "Reduce:" << endl;

	foundLow = 0;
	 explosions = 0;
	 splitL = 0;
	 splitR = 0;
	 lookingForLow = 0;

	lastNumberId = -1;
	string previousDebugString = "";

	while (true) {
		changed = false;
		reduceNode(input, level);

		if (changeId != -1) {
			lookingForLow++;
			changeLowerOnId(input);
		}
		changeId = -1;

		if (!changed)
		{
			if (input.firstLit == -1)
				splitReduceNode(input.nodes[0]);
			if (input.secondLit == -1)
				input.nodes.size() > 1 ? splitReduceNode(input.nodes[1]) : splitReduceNode(input.nodes[0]);
		}

		string debugString = buildDebugString(input);
		std::cout << debugString << endl;

		if (debugString == previousDebugString)
			break;
		previousDebugString = debugString;
		changeLower = -1;
		changeHigher = -1;
		lastNumberId = -1;
		splitting = false;
	}
	std::cout << endl << endl;
}

node add(node first, node second)
{
	node newTop;
	newTop.id = ++nodeId;
	newTop.nodes.push_back(first);
	newTop.nodes.push_back(second);
	return newTop;
}


std::string currentInput;
node parseInputString(int& i)
{
	node newNode;
	newNode.id = ++nodeId;
	string currentInt = "";
	while (i < currentInput.size())
	{
		if (currentInput[i] == '[') {
			node subNode;
			newNode.nodes.push_back(parseInputString(++i));
		}
		else if (currentInput[i] == ',') {
			if (currentInt != "")
			{
				newNode.firstLit = stoi(currentInt);
				currentInt = "";
			}
		}

		else if (isdigit(currentInput[i]))
		{
			currentInt += currentInput.substr(i, 1);
		}

		else if (currentInput[i] == ']')
		{
			if (currentInt != "")
				newNode.secondLit = stoi(currentInt);
			return newNode;
		}
		i++;
	}
	throw;
}

void parseInput()
{
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		int i = 1;
		currentInput = input;
		nodes.push_back(parseInputString(i));
	}
}
