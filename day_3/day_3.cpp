#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int TranslateBinary(std::string val);
int CalculateLifeSupport(std::vector<std::string> binaryNumbers, bool calcOxygen);

int main()
{
	std::string binaryNumber;
	const int binarySize = 12;

	int mostCommon[binarySize];
	for (int i = 0; i < binarySize; i++)
		mostCommon[i] = 0;

	int count = 0;

	std::vector<std::string> binaryNumbers;

	while (std::cin >> binaryNumber && binaryNumber != "eof")
	{
		binaryNumbers.push_back(binaryNumber);
		for (int i = 0; i < binaryNumber.length(); i++)
		{
			mostCommon[i] += binaryNumber[i] - '0';
		}
		count++;
	}

	std::sort(binaryNumbers.begin(), binaryNumbers.end());

	std::string gamma = "";
	std::string epsilon = "";
	for (int i = 0; i < binarySize; i++)
	{
		if (mostCommon[i] > count / 2)
		{
			gamma += "1";
			epsilon += "0";
		}
		else
		{
			gamma += "0";
			epsilon += "1";
		}
	}

	int gammaInt = TranslateBinary(gamma);
	int epsilonInt = TranslateBinary(epsilon);
	int result = gammaInt * epsilonInt;
	std::cout << std::endl << "Power consumption is: " << result;

	int co2Int = CalculateLifeSupport(binaryNumbers, false);
	int oxyInt = CalculateLifeSupport(binaryNumbers, true);
	int LSresult = co2Int * oxyInt;
	std::cout << std::endl << "Life support is: " << LSresult;
}


int TranslateBinary(std::string val)
{
	int retVal = 0;
	int positionWorth = 1;
	while (val.length() > 0)
	{
		auto transChar = val.substr(val.length() - 1);
		val = val.substr(0, val.length() - 1);
		if (transChar == "1")
			retVal += positionWorth;
		positionWorth *= 2;
	}
	return retVal;
}

int CalculateLifeSupport(std::vector<std::string> binaryNumbers, bool calcOxygen)
{
	std::vector<std::string> binaryNumbersTmp;
	for (std::string binary : binaryNumbers)
		binaryNumbersTmp.push_back(binary);

	int currentPlace = 0;
	while (binaryNumbersTmp.size() > 1) {
		int matchCount = 0;
		for (int i = 0; i < binaryNumbersTmp.size(); i++)
			matchCount += binaryNumbersTmp[i][currentPlace] - '0';
		bool removeOnes = calcOxygen ? matchCount < ((double)binaryNumbersTmp.size() / 2) : matchCount >= ((double)binaryNumbersTmp.size() / 2);
		std::vector<int> markForDeletion;
		for (int i = 0; i < binaryNumbersTmp.size(); i++)
		{
			if (binaryNumbersTmp[i][currentPlace] == '1' && removeOnes)
				markForDeletion.push_back(i);
			else if (binaryNumbersTmp[i][currentPlace] == '0' && !removeOnes)
				markForDeletion.push_back(i);
		}

		for (int i = markForDeletion.size() - 1; i >= 0; i--)
			binaryNumbersTmp.erase(binaryNumbersTmp.begin() + markForDeletion[i]);
		currentPlace++;
	}
	return TranslateBinary(binaryNumbersTmp[0]);
}