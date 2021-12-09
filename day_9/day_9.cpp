#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::vector<int>> matrix;
    std::string input;
    while (std::cin >> input && input != "eof")
    {
        std::vector<int> newRow;
        for (int i = 0; i < input.size(); i++)
            newRow.push_back(input[i] - 48);
        matrix.push_back(newRow);
    }

    int riskLevel = 0;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (j != 0) if (matrix[i][j - 1] <= matrix[i][j]) continue;
            if (i != 0) if (matrix[i - 1][j] <= matrix[i][j]) continue;
            if (j != matrix[i].size()-1) if (matrix[i][j + 1] <= matrix[i][j]) continue;
            if (i != matrix.size()-1) if (matrix[i + 1][j] <= matrix[i][j]) continue;
            riskLevel += matrix[i][j] + 1;
        }
    }

    std::cout << riskLevel;
}
