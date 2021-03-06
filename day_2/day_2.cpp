// day_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	int depth = 0, horizontal = 0, aim = 0;
	std::string direction;

	while (std::cin >> direction && direction != "eof")
	{
		int amount;
		std::cin >> amount;
		if (direction == "forward") 
		{
			horizontal += amount;
			depth += aim * amount;
		}
		else if (direction == "up")
			aim -= amount;
		else if (direction == "down")
			aim += amount;
	}

	int output = depth * horizontal;
	std::cout << std::endl << output;
}