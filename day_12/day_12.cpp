#include <iostream>
#include <string>
#include <vector>

class node
{
public:
    std::string name;
    std::vector<node*> neighbours;
    bool isLarge = false;
};

std::vector<node> parseNodes(std::vector<std::string> inputs);
int visitNeighbours(node &node, std::vector<std::string> visited);

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
    for (int i = 0; i < nodes.size(); i++)
        if (nodes[i].name == "start")
            startNode = i;
    node start = nodes[startNode];
    std::vector<std::string> visited;
    int paths = visitNeighbours(start, visited);

    std::cout << "Number of paths: " << paths;
}

int visitNeighbours(node &node, std::vector<std::string> visited)
{
    int paths = 0;
    if (node.name == "end")
        return 1;

    if (!node.isLarge)
        visited.push_back(node.name);

    for (int i = 0; i < node.neighbours.size(); i++)
    {
        bool visitNeighbour = true;
        for (std::string str : visited)
            if (node.neighbours[i]->name == str)
                visitNeighbour = false;
        if (visitNeighbour)
            paths += visitNeighbours(*node.neighbours[i], visited);
    }
    return paths;
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