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
	//vector<string> inputs = parseInput();

	//string inp = "[[[[0,7],4],[15,[0,13]]],[1,1]]"; //split
	//string inp = "[[[[[9,8],1],2],3],4]"; //explode
	//while (reduce(inp));

	//string inp = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"; //magnitude
	//string inp = "[1,9]"; //magnitude
	//int mag = getMagnitude(inp);

	/*string sumStr = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
	{
		string addStr = add(sumStr, inputs[i]);
		reduce(addStr);
		sumStr = addStr;
	}

	int mag = getMagnitude(sumStr);
	*/

	/*parseInput();
	reduce(nodes[0]);



	return 0;
	*/
	parseInput();
	node sumNode = nodes[0];
	for (int i = 1; i < nodes.size(); i++)
	{
		node addNode = add(sumNode, nodes[i]);
		reduce(addNode);
		sumNode = addNode;

		cout << endl << "Data: " << endl;
		cout << "Explosions: " << explosions << endl;
		cout << "Split left: " << splitL << endl;
		cout << "Split right: " << splitR << endl;
		cout << "Look low: " << lookingForLow << endl;
		cout << "Found low: " << foundLow << endl;
		cout << "Changed first: " << changedFirst << endl;
		cout << "Dismissed lows: " << dismissed << endl;
		cout << "Explosions handled: " << explosionHandledCount << endl;

		cout << endl << endl << "Next iteration: " << endl;

	}


	long long int mag = getMagnitude(sumNode);


	std::cout << "Final magnitude is: " << mag;
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

//bool explodeChanged = false;
//bool splitChanged = false;

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
		//else
		//return;
	}

	//split
	/*if (!changed) {
		if (input.firstLit > -1 && input.firstLit > 9)
		{
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
		else if (input.secondLit > -1 && input.secondLit > 9)
		{
			node newNode = split(input.secondLit);
			newNode.id = ++nodeId;
			input.nodes.push_back(newNode);
			input.secondLit = -1;
			changed = true;
		}
	}

	if (splitting)
		return;*/
	if (changed && changeHigher == -1)
		return;


	if (input.firstLit != -1 && changeHigher != -1)
	{
		input.firstLit += changeHigher;
		changeHigher = -1;
	}
	/*else if (input.secondLit != -1 && changeHigher != -1)
	{
		input.secondLit += changeHigher;
		changeHigher = -1;
	}*/

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
			//explosionImmunity = true;
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
	/*if (!explosionImmunity && input.secondLit != -1 && changeHigher != -1)
	{
		input.secondLit += changeHigher;
		changeHigher = -1;
	}*/

	for (int i = removeElements.size() - 1; i >= 0; i--)
		input.nodes.erase(input.nodes.begin() + removeElements[i]);


	//if (!explosionImmunity && (input.secondLit != -1 || input.firstLit != -1))
	//	lastNumberId = input.id;


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
		/*if (input.firstLit == -1)
			reduceNode(input.nodes[0], level + 1);
		if (input.secondLit == -1)
			input.nodes.size() > 1 ? reduceNode(input.nodes[1], level + 1) : reduceNode(input.nodes[0], level + 1);
			*/
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
		//changed = explodeChanged || splitChanged;
		//explodeChanged = false;
		//splitChanged = false;
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

/*string add(string first, string second)
{
	return ("[" + first + "," + second + "]");
}

void reduce(string& input)
{
	bool changed = true;
	while (changed)
	{
		changed = false;
		int openParams = 0;
		int posLastOpen = -1;
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '[') {
				openParams++;
				posLastOpen = i;
			}
			if (input[i] == ']') {
				if (openParams >= 5)
				{
					string preCalcStr = input.substr(0, posLastOpen);
					string calcStr = input.substr(posLastOpen, i - posLastOpen + 1);
					string postCalcStr = input.size() > i + 1 ? input.substr(i + 1) : "";
					int first = stoi(calcStr.substr(1, calcStr.find(',')));
					int second = stoi(calcStr.substr(calcStr.find(',') + 1));

					int locationLastDigit = -1;
					for (int j = 0; j < preCalcStr.size(); j++)
					{
						if (isdigit(preCalcStr[j]))
							locationLastDigit = j;
					}

					string preStr, postStr;
					if (locationLastDigit != -1)
					{
						string prePreStr = preCalcStr.substr(0, locationLastDigit);
						int add = stoi(preCalcStr.substr(locationLastDigit, 1)) + first;
						string postPreStr = preCalcStr.substr(locationLastDigit + 1);
						preStr = prePreStr + to_string(add) + postPreStr;
					}
					else
						preStr = preCalcStr;

					int locationNextDigit = -1;
					for (int j = 0; j < postCalcStr.size(); j++)
					{
						if (isdigit(postCalcStr[j])) {
							locationNextDigit = j;
							break;
						}
					}

					if (locationNextDigit != -1)
					{
						string prePostStr = postCalcStr.substr(0, locationNextDigit);
						int add = stoi(postCalcStr.substr(locationNextDigit, 1)) + second;
						string postPostStr = postCalcStr.substr(locationNextDigit + 1);
						postStr = prePostStr + to_string(add) + postPostStr;
					}
					else
						postStr = postCalcStr;

					input = preStr + "0" + postStr;

					changed = true;
					break;
				}
				else
					openParams--;
			}
			if (isdigit(input[i]))
			{
				int j = i;
				string num = input.substr(i, 1);
				while (isdigit(input[++j]))
					num += input.substr(j, 1);
				if (num.size() > 1) {
					//split
					int numInt = stoi(num);
					int first = numInt / 2;
					int second = numInt % (first)+first;
					string preStr = input.substr(0, i);
					string postStr = input.substr(i + num.size());
					input = preStr + "[" + to_string(first) + "," + to_string(second) + "]" + postStr;
					changed = true;
					break;
				}
			}
		}
	}
}

int getMagnitude(std::string input)
{
	bool changed = true;
	string modInput = input;
	while (changed)
	{
		changed = false;
		int posLastOpen = -1;

		for (int i = 0; i < modInput.size(); i++)
		{
			if (modInput[i] == '[')
				posLastOpen = i;
			if (modInput[i] == ']')
			{
				string preStr = modInput.substr(0, posLastOpen);
				string calcStr = modInput.substr(posLastOpen, i - posLastOpen);
				string postStr = modInput.size() > i + 1 ? modInput.substr(i + 1) : "";
				int first = stoi(calcStr.substr(1, calcStr.find(','))) * 3;
				int second = stoi(calcStr.substr(calcStr.find(',') + 1)) * 2;

				modInput = preStr + to_string(first + second) + postStr;
				changed = true;
				break;
			}
		}
	}

	return stoi(modInput);
}

vector<string> parseInput()
{
	vector<string> inputs;
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		inputs.push_back(input);
	}

	return inputs;
}
*/