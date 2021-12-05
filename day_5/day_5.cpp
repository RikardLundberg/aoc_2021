#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<std::string> allPoints;

	std::string firstCoord;
	while (std::cin >> firstCoord && firstCoord != "eof") {
		std::string dummy;
		std::cin >> dummy;
		std::string secondCoord;
		std::cin >> secondCoord;
		if (firstCoord == secondCoord) {
			allPoints.push_back(firstCoord);
			continue;
		}

		int first_x = std::stoi(firstCoord.substr(0, firstCoord.find(',')));
		int first_y = std::stoi(firstCoord.substr(firstCoord.find(',') + 1));
		int second_x = std::stoi(secondCoord.substr(0, secondCoord.find(',')));
		int second_y = std::stoi(secondCoord.substr(secondCoord.find(',') + 1));
		if (first_x == second_x) {
			int lowest = first_y < second_y ? first_y : second_y;
			int highest = first_y > second_y ? first_y : second_y;
			if (first_y == lowest) allPoints.push_back(firstCoord); else allPoints.push_back(secondCoord);
			do {
				lowest++;
				std::string coord = std::to_string(first_x) + "," + std::to_string(lowest);
				allPoints.push_back(coord);
			} while (lowest != highest);
		}
		else if (first_y == second_y) {
			int lowest = first_x < second_x ? first_x : second_x;
			int highest = first_x > second_x ? first_x : second_x;
			if (first_x == lowest) allPoints.push_back(firstCoord); else allPoints.push_back(secondCoord);
			do {
				lowest++;
				std::string coord = std::to_string(lowest) + "," + std::to_string(first_y);
				allPoints.push_back(coord);
			} while (lowest != highest);
		}
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