#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class board
{
public:
	std::vector<std::vector<int>> matrix;
	int winSum;
	std::vector<std::vector<bool>> marked;
	bool drawNumber(int number) {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if (matrix[i][j] == number)
				{
					winSum -= number;
					marked[i][j] = true;
					bool winning = true;
					for (int col = 0; col < marked[i].size(); col++)
						if (!marked[i][col])
							winning = false;
					if (winning) return true;
					winning = true;
					for (int row = 0; row < marked.size(); row++)
						if (!marked[row][j])
							winning = false;
					return winning;
				}
			}
		}
		return false;
	}
	void addMatrix(std::vector<std::vector<int>> newMatrix) {
		
		for (int i = 0; i < newMatrix.size(); i++) {
			std::vector<int> newMatrixRow;
			std::vector<bool> newMarkedRow;
			for (int j = 0; j < newMatrix[i].size(); j++) {
				newMatrixRow.push_back(newMatrix[i][j]);
				newMarkedRow.push_back(false);
			}
			matrix.push_back(newMatrixRow);
			marked.push_back(newMarkedRow);
		}
	}
};

void ReadInput(std::vector<int>& drawnNumbers, std::vector<board>& boards);
int PlayBingo(std::vector<int> &drawnNumbers, std::vector<board> &boards);

int main()
{
	std::vector<int> drawnNumbers;
	std::vector<board> boards;
	ReadInput(drawnNumbers, boards);

	int result = PlayBingo(drawnNumbers, boards);
	std::cout << std::endl << "Final score: " << result;
}

int PlayBingo(std::vector<int> &drawnNumbers, std::vector<board> &boards) {
	for (int drawnNumber : drawnNumbers)
	{
		for (int i = 0; i < boards.size(); i++)
		{
			if (boards[i].drawNumber(drawnNumber))
			{
				return boards[i].winSum * drawnNumber;
			}
		}
	}
	return -1;
}

void ReadInput(std::vector<int>& drawnNumbers, std::vector<board>& boards) {
	std::string numberString;
	std::cin >> numberString;

	while (numberString.find(',') != std::string::npos) {
		drawnNumbers.push_back(std::stoi(numberString.substr(0, numberString.find(','))));
		numberString = numberString.substr(numberString.find(',') + 1);
	}
	drawnNumbers.push_back(std::stoi(numberString));

	int input;
	std::vector<std::vector<int>> matrix;
	int winSum = 0;
	std::vector<int> currentRow;
	while (std::cin >> input)
	{
		currentRow.push_back(input);
		winSum += input;
		if (currentRow.size() == 5)
		{
			matrix.push_back(currentRow);
			currentRow = {};
			if (matrix.size() == 5) {
				board newBoard; 
				newBoard.winSum = winSum;
				winSum = 0;
				newBoard.addMatrix(matrix);
				boards.push_back(newBoard);
				matrix = {};
			}
		}
	}
}