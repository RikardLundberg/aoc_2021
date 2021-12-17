#include <iostream>
#include <string>

int main()
{

    int lowestY;
    std::string input;
    while (std::cin >> input && input != "eof")
    {
        if (input[0] == 'y')
        {
            std::string yVal = input.substr(input.find('=') + 1);
            lowestY = std::stoi(yVal.substr(0, yVal.find('.')));
        }
    }

    int height = 0;
    int yMaxVelocity = lowestY * (-1) - 1;
    for (int i = 0; i < yMaxVelocity; i++)
        height += yMaxVelocity - i;

    std::cout << "Max height is: " << height;
}
