#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string input; 
    int count = 0;
    int order = 0;
    while (std::cin >> input && input != "eof")
    {
        if(order < 11)
        { }
        else if (input.size() == 2 || input.size() == 3 || input.size() == 7 || input.size() == 4)
            count++;
        order++;
        if (order == 15)
            order = 0;
    }

    std::cout << count;
}
