#include <iostream>
#include <string>

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

    int height = 0;
    int yMaxVelocity = lowestY * (-1) - 1;
    int xMaxVelocity = lowestX * (-1) - 1;
    for (int i = 0; i < yMaxVelocity; i++)
        height += yMaxVelocity - i;

    std::cout << "Max height is: " << height;
}
