#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> GetCoordsBetween(std::string firstCoord, std::string secondCoord);

int main()
{
	std::vector<std::string> allPoints;

	std::string firstCoord;
	while (std::cin >> firstCoord && firstCoord != "eof") {
		std::string dummy;
		std::cin >> dummy;
		std::string secondCoord;
		std::cin >> secondCoord;
		allPoints.push_back(firstCoord);
		if (firstCoord == secondCoord) {
			continue;
		}
		allPoints.push_back(secondCoord);
		std::vector<std::string> betweenCoords = GetCoordsBetween(firstCoord, secondCoord);
		for (std::string coord : betweenCoords)
			allPoints.push_back(coord);
	}

	std::sort(allPoints.begin(), allPoints.end());
	
	int doubleCount = 0;

	std::string previous;
	bool countedPrevious = false;

	for (int i = 0; i < allPoints.size(); i++)
	{
		if (allPoints[i] == previous && !countedPrevious)
		{
			doubleCount++;
			countedPrevious = true;
		}
		if (previous != allPoints[i])
		{
			previous = allPoints[i];
			countedPrevious = false;
		}
	}

	std::cout << "Number of doubles: " << doubleCount;

}


std::vector<std::string> GetCoordsBetween(std::string firstCoord, std::string secondCoord)
{
	std::vector<std::string> allPoints;
	int first_x = std::stoi(firstCoord.substr(0, firstCoord.find(',')));
	int first_y = std::stoi(firstCoord.substr(firstCoord.find(',') + 1));
	int second_x = std::stoi(secondCoord.substr(0, secondCoord.find(',')));
	int second_y = std::stoi(secondCoord.substr(secondCoord.find(',') + 1));
	if (first_x == second_x) {
		int lowest = first_y < second_y ? first_y : second_y;
		int highest = first_y > second_y ? first_y : second_y;
		while (true) {
			lowest++;
			std::string coord = std::to_string(first_x) + "," + std::to_string(lowest);
			if (lowest == highest)
				break;
			allPoints.push_back(coord);
		}
	}
	else if (first_y == second_y) {
		int lowest = first_x < second_x ? first_x : second_x;
		int highest = first_x > second_x ? first_x : second_x;
		while (true) {
			lowest++;
			std::string coord = std::to_string(lowest) + "," + std::to_string(first_y);
			if (lowest == highest)
				break;
			allPoints.push_back(coord);
		} 
	}
	else {
		int lowest = first_y < second_y ? first_y : second_y;
		int highest = first_y > second_y ? first_y : second_y;
		bool increaseX = true;
		int corresponding_x = first_y == lowest ? first_x : second_x;
		if (first_y == lowest && first_x > second_x)
			increaseX = false;
		if (second_y == lowest && second_x > first_x)
			increaseX = false;
		while (true) {
			lowest++;
			if (increaseX) corresponding_x++; else corresponding_x--;
			std::string coord = std::to_string(corresponding_x) + "," + std::to_string(lowest);
			if (lowest == highest)
				break;
			allPoints.push_back(coord);
		}
	}
	return allPoints;
}