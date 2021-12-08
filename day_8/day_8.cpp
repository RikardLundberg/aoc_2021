#include <iostream>
#include <string>
#include <vector>

int calculateOutput(std::vector<std::string> inputVals, std::vector<std::string> outputVals);
int getMatches(std::string currentVal, std::string otherVal);

int main()
{
    std::string input; 
    int count = 0;
    int order = 0;
    std::vector<std::string> inputVals;
    std::vector<std::string> outputVals;
    while (std::cin >> input && input != "eof")
    {
        if (order < 11)
            inputVals.push_back(input);
        else
            outputVals.push_back(input);
        order++;
        if (order == 15) {
            count += calculateOutput(inputVals, outputVals);
            inputVals.clear();
            outputVals.clear();
            order = 0;
        }
    }
    std::cout << count;
}

int calculateOutput(std::vector<std::string> inputVals, std::vector<std::string> outputVals)
{
    std::string correctInputVals[10] = { "" };
    for (std::string input : inputVals) {
        if (input.size() == 2) correctInputVals[1] = input;
        else if (input.size() == 3) correctInputVals[7] = input;
        else if (input.size() == 4) correctInputVals[4] = input;
        else if (input.size() == 7) correctInputVals[8] = input;
    }

    //rest:
    // 5 = 2,3,5  - if ct 7 = 3, elif ct 3/4 of 4 = 5, else 2
    // 6 = 0,6,9  - ifn ct 7 = 6, elif ct 4 = 9, else 0

    for (std::string input : inputVals) {
        if (input.size() == 5) {
            if (getMatches(input, correctInputVals[7]) == 3) correctInputVals[3] = input;
            else if (getMatches(input, correctInputVals[4]) == 3) correctInputVals[5] = input;
            else (correctInputVals[2] = input);
        }
        if (input.size() == 6) {
            if (getMatches(input, correctInputVals[7]) != 3) correctInputVals[6] = input;
            else if (getMatches(input, correctInputVals[4]) == 4) correctInputVals[9] = input;
            else (correctInputVals[0] = input);
        }
    }

    int retVal = 0;
    int counter = 1000;
    for (std::string output : outputVals)
    {
        for (int i = 0; i < 10; i++)
        {
            if (output.size() == correctInputVals[i].size() && getMatches(output, correctInputVals[i]) == correctInputVals[i].size())
            {
                retVal += counter * i;
                counter = counter / 10;
            }
        }
    }
    return retVal;
}

int getMatches(std::string currentVal, std::string otherVal)
{
    int matches = 0;
    for (char ch : otherVal)
    {
        if (currentVal.find(ch) != std::string::npos)
            matches++;
    }
    return matches;
}