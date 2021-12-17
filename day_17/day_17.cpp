#include <iostream>
#include <string>
#include <vector>
#include <math.h>

int main()
{

	int lowestY, highestY, lowestX, highestX;
	std::string input;
	while (std::cin >> input && input != "eof")
	{
		if (input[0] == 'x')
		{
			std::string xVal = input.substr(input.find('=') + 1);
			lowestX = std::stoi(xVal.substr(0, xVal.find('.')));
			highestX = std::stoi(xVal.substr(xVal.find('.') + 2));
		}

		else if (input[0] == 'y')
		{
			std::string yVal = input.substr(input.find('=') + 1);
			lowestY = std::stoi(yVal.substr(0, yVal.find('.')));
			highestY = std::stoi(yVal.substr(yVal.find('.') + 2));
		}
	}

	/*int height = 0;
	int yMaxVelocity = lowestY * (-1) - 1;
	int xMaxVelocity = lowestX * (-1) - 1;
	for (int i = 0; i < yMaxVelocity; i++)
		height += yMaxVelocity - i;
	*/

	// is x possible
	std::vector<std::pair<int, int>> possibleXAndSteps;
	int highestStepCount = 0;
	for (int i = 0; i <= 2000; i++)
	{
		int path = i;
		int steps = 1;
		int increment = i;
		while (true)
		{
			if (path <= highestX && path >= lowestX)
			{
				if (increment == 0)
					possibleXAndSteps.emplace_back(i, -steps);
				else
					possibleXAndSteps.emplace_back(i, steps);
				//if (steps > highestStepCount)
				 //   highestStepCount = steps;
				//break;
			}
			if (increment > 0)
				increment--;
			else
				break;
			path += increment;
			if (path > highestX)
				break;
			//if (steps > 2000)
			//    break;
			steps++;
		}
	}

	int distinctCount = 0;

	/*int oneStepYs = std::abs(lowestY) - std::abs(highestY) + 1;
	for (int i = 0; i < possibleXAndSteps.size(); i++)
	{
		if (possibleXAndSteps[i].second == 1)
			distinctCount += oneStepYs;
	}*/

	int lessThanNoGo = std::abs(lowestY) / 2 - 1;


	//negative speed
	/*for(int i = 0; i <= lessThanNoGo; i++)
	{
		int path = i;
		int steps = 1;
		int increment = i;
		while (true)
		{
			if (path >= std::abs(highestY) && path <= std::abs(lowestY))
			{
				for (auto posX : possibleXAndSteps)
				{
					if (posX.second == steps)
						distinctCount++;
				}
			}
			increment++;
			path += increment;
			if (path > std::abs(lowestY))
				break;
			steps++;
		}
	}*/

	//positive speed
	std::vector<std::pair<int, int>> outpair;
	int yCount = 0;
	//for (int i = lowestY; i <= std::abs(lowestY); i++)
	for (int i = lowestY; i <= std::abs(lowestY); i++)
	{
		int path = i;
		int steps = 1;
		int increment = i;

		std::vector<int> usedPos;
		while (path >= lowestY) {
			if (path >= lowestY && path <= highestY)
			{
				yCount++;

				for (auto posX : possibleXAndSteps)
				{
					if ((posX.second < 0 && std::abs(posX.second) <= steps) || posX.second == steps) {
						//distinctCount++;
						std::string hej;
						if (i == 1)
						{
							hej = "3";
						}

						/*bool outpairContains = false;
						for (int i = 0; i < outpair.size(); i++)
							if (outpair[i].first == posX.first && outpair[i].second == i)
								outpairContains = true;

						if(!outpairContains)*/


						bool outpairContains = false;
						for (int i = 0; i < usedPos.size(); i++)
						{
							if (usedPos[i] == posX.first) {
								outpairContains = true;
							}
						}
						if (!outpairContains) {
							outpair.emplace_back(posX.first, i);
							usedPos.push_back(posX.first);
						}
					}
				}
			}
			increment--;
			path += increment;
			//if (path < highestY)
			//    break;
			steps++;
			//if (steps > highestStepCount)
			//    break;
		}
	}


	/*for (int i = 0; i <= lessThanNoGo; i++)
	{
		int path = i;
		int steps = 1;
		int increment = i;
		while (true)
		{
			if (path >= std::abs(highestY) && path <= std::abs(lowestY))
			{
				for (auto posX : possibleXAndSteps)
				{
					if (posX.second == steps)
						distinctCount++;
				}
				//break;
			}
			increment++;
			path += increment;
			if (path > std::abs(lowestY))
				break;
			steps++;
		}
	}*/


	std::cout << "Distinct Count: " << distinctCount;
}
