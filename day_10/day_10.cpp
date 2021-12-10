#include <iostream>
#include <string>
#include <vector>

bool isCloser(char potentialCloser);
bool matches(char opener, char closer);
int getPoints(char closer);

int main()
{
	int highScore = 0;
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		std::vector<char> openerStack;
		for (int i = 0; i < input.size(); i++) 
		{
			if (isCloser(input[i])) {

				if(matches(openerStack[openerStack.size() - 1], input[i]))
					openerStack.pop_back();
				else
				{
					highScore += getPoints(input[i]);
					break;
				}
			}
			else
				openerStack.push_back(input[i]);
		}
	}

	std::cout << "HighScore: " << highScore;
}

int getPoints(char closer)
{
	switch (closer)
	{
	case ')':
		return 3;
	case ']':
		return 57;
	case '}':
		return 1197;
	case '>':
		return 25137;
	}
	throw;
}

bool matches(char opener, char closer)
{
	if (opener == '(' && closer == ')') return true;
	if (opener == '[' && closer == ']') return true;
	if (opener == '{' && closer == '}') return true;
	if (opener == '<' && closer == '>') return true;
	return false;
}

bool isCloser(char potentialCloser)
{
	switch (potentialCloser)
	{
	case ')':
	case ']':
	case '}':
	case '>':
		return true;
	}
	return false;
}
