#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class node
{
public:
    std::string name;
    std::vector<node*> neighbours;
    bool isLarge = false;
};

std::vector<node> parseNodes(std::vector<std::string> inputs);
void visitNeighbours(node &node, std::vector<std::string> visited, std::string path, bool hasVisitedTwice);
std::vector<std::string> foundPaths;
std::vector<std::string> smallCaveNames;

int main()
{
    std::string input;
    std::vector<std::string> inputs;
    while (std::cin >> input && input != "eof")
    {
        inputs.push_back(input);
    }

    std::vector<node> nodes = parseNodes(inputs);

    int startNode = -1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == "start")
            startNode = i;
        else if (nodes[i].name != "end" && !nodes[i].isLarge)
            smallCaveNames.push_back(nodes[i].name);
    }

    node start = nodes[startNode];
    std::vector<std::string> visited;
    visitNeighbours(start, visited, "", false);


    std::cout << "Number of paths: " << foundPaths.size();
}


void visitNeighbours(node &node, std::vector<std::string> visited, std::string path, bool hasVisitedTwice)
{
    path += node.name + ",";
    if (node.name == "end")
    {
        foundPaths.push_back(path);
        return;
    }

    if (!node.isLarge)
        visited.push_back(node.name);

    for (int i = 0; i < node.neighbours.size(); i++)
    {
        if (node.neighbours[i]->name == "start")
            continue;
        bool visitNeighbour = true;

        if (!node.neighbours[i]->isLarge) {
            for (std::string str : visited) {
                if (node.neighbours[i]->name == str)
                    visitNeighbour = false;
            }
            //if (path.find(node.neighbours[i]->name) != std::string::npos)
            //    visitNeighbour = false;
        }
        bool visitedTwiceOnThis = false;
        if (!visitNeighbour && !hasVisitedTwice && !node.neighbours[i]->isLarge) {
            visitNeighbour = true;
            hasVisitedTwice = true;
            visitedTwiceOnThis = true;
        }

        if (visitNeighbour) {
            visitNeighbours(*node.neighbours[i], visited, path, hasVisitedTwice);
            if(visitedTwiceOnThis)
                hasVisitedTwice = false;
        }
    }
}

std::vector<node> parseNodes(std::vector<std::string> inputs)
{
    std::vector<node> nodes;
    for (std::string input : inputs) {
        node newNode;
        auto name = input.substr(0, input.find('-'));
        auto secondName = input.substr(input.find('-') + 1);
        bool nameAdded = false, secondNameAdded = false;
        for (node node : nodes)
        {
            if (name == node.name)
                nameAdded = true;
            if (secondName == node.name)
                secondNameAdded = true;
        }
        if (!nameAdded) {
            node newNode;
            newNode.name = name;
            if (isupper(name[0]))
                newNode.isLarge = true;
            nodes.push_back(newNode);
        }

        if (!secondNameAdded) {
            node newNode;
            newNode.name = secondName;
            if (isupper(secondName[0]))
                newNode.isLarge = true;
            nodes.push_back(newNode);
        }
    }

    for (std::string input : inputs) {
        node newNode;
        auto first = input.substr(0, input.find('-'));
        auto second = input.substr(input.find('-') + 1);
        int firstNode, secondNode;
        for (int i = 0; i < nodes.size(); i++)
        {
            if (first == nodes[i].name)
                firstNode = i;
            if (second == nodes[i].name)
                secondNode = i;
        }
        nodes[firstNode].neighbours.push_back(&nodes[secondNode]);
        nodes[secondNode].neighbours.push_back(&nodes[firstNode]);
    }
    return nodes;
}