#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isCloser(char potentialCloser);
bool matches(char opener, char closer);
long long int getPoints(std::vector<char> openerStack);

int main()
{
	std::vector<long long int> highScores;
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		std::vector<char> openerStack;
		bool failed = false;
		for (int i = 0; i < input.size(); i++) 
		{
			if (isCloser(input[i])) {

				if(matches(openerStack[openerStack.size() - 1], input[i]))
					openerStack.pop_back();
				else
				{
					failed = true;
					break;
				}
			}
			else
				openerStack.push_back(input[i]);
		}

		if (!failed)
			highScores.push_back(getPoints(openerStack));
	}

	std::sort(highScores.begin(), highScores.end());
	std::cout << "HighScore: " << highScores[highScores.size()/2];
}

long long int getPoints(std::vector<char> openerStack)
{
	long long int points = 0;
	for (int i = openerStack.size() - 1; i >= 0; i--) {
		points *= 5;
		switch (openerStack[i])
		{
		case '(':
			points += 1;
			break;
		case '[':
			points += 2;
			break;
		case '{':
			points += 3;
			break;
		case '<':
			points += 4;
			break;
		default:
			throw;
		}
	}
	return points;
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
