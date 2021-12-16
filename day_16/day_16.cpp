#include <iostream>
#include <string>
#include <vector>
#include <chrono>

long long int TranslateBinary(std::string val);
void parseInput();
std::chrono::time_point<std::chrono::steady_clock> start_time;
std::string HexaToBinary(char hexa);
long long int ReadOperator(int type);
std::string binaryInput = "";
int totalVersion = 0;
int counter = 0;
std::string translation = "";

int main()
{
	parseInput();

	long long int result = 0;
	std::string versionStr, typeStr;
	versionStr += binaryInput.substr(0, 3);
	int version = TranslateBinary(versionStr);
	totalVersion += version;
	typeStr += binaryInput.substr(3, 3);
	int type = TranslateBinary(typeStr);
	counter = 6;
	if (type == 4)
	{
		bool lastGroup = false;
		while (!lastGroup)
		{
			std::string subGroup;
			subGroup += binaryInput.substr(counter, 5);
			counter += 5;
			if (subGroup[0] == '0')
				lastGroup = true;
		}
	}
	else
	{
		result += ReadOperator(type);
	}

	std::cout << "End result: " << result << std::endl;
	std::cout << "Total Version: " << totalVersion << std::endl;
	std::cout << std::endl << std::endl << translation;
}

void LogType(int type)
{
	switch (type)
	{
	case 0:
		translation += "\nSUM(";
		break;
	case 1:
		translation += "\nMUL(";
		break;
	case 2:
		translation += "\nMIN(";
		break;
	case 3:
		translation += "\nMAX(";
		break;
	case 5:
		translation += "\nGRT(";
		break;
	case 6:
		translation += "\nLES(";
		break;
	case 7:
		translation += "\nEQU(";
		break;
	}
}


bool CanFitMore(int counter, int subPackEnd) 
{
	return (counter < subPackEnd);
}


long long int ReadOperator(int type)
{
	bool isFifteen = false; // else eleven
	if (binaryInput[counter] == '0')
		isFifteen = true;
	counter++;
	int Lcounter = isFifteen ? 15 : 11;
	std::string Lstr;
	for (int j = 0; j < Lcounter; j++)
	{
		Lstr += binaryInput.substr(counter, 1);
		counter++;
	}
	int L = TranslateBinary(Lstr);
	int subPackSize = L + counter;
	bool morePackages = isFifteen || L > 0;
	std::vector<long long int> values;

	LogType(type);

	while (morePackages)
	{
		for (int sub = 0; sub < L; sub++)
		{
			totalVersion += TranslateBinary(binaryInput.substr(counter, 3));
			counter += 3;
			int type = TranslateBinary(binaryInput.substr(counter, 3));
			counter += 3;
			if (isFifteen && !CanFitMore(counter, subPackSize))
				break;
			if (type != 4)
			{
				values.push_back(ReadOperator(type));
			}
			else
			{
				bool lastGroup = false;
				std::string totalVal = "";
				if (isFifteen && !CanFitMore(counter, subPackSize))
					break;
				while (!lastGroup)
				{
					std::string subGroup;
					subGroup += binaryInput.substr(counter, 5);
					totalVal += binaryInput.substr(counter + 1, 4);
					counter += 5;
					if (subGroup[0] == '0')
						lastGroup = true;
				}
				long long int newValue = TranslateBinary(totalVal);
				translation += std::to_string(newValue) + ", ";
				values.push_back(newValue);
			}
			if (isFifteen && !CanFitMore(counter, subPackSize)) {
				morePackages = false;//(counter + 10 < subPackSize);
				break;
			}
		}
		if (!isFifteen)
			morePackages = false;
	}
	if (isFifteen)
		counter = subPackSize;

	if(translation.substr(translation.size() - 2, 2) == ", ")
		translation = translation.substr(0, translation.size() - 2);
	translation += ")";

	if (0 == type) {
		long long int start = 0;
		for (int i = 0; i < values.size(); i++)
			start += values[i];
		return start;
	}
	else if (1 == type) {
		long long int start = values[0];
		for (int i = 1; i < values.size(); i++)
			start *= values[i];
		return start;
	}
	else if (2 == type) {
		long long int min = INT_MAX;
		for (long long int val : values)
			if (val < min)
				min = val;
		return min;
	}
	else if (3 == type) {
		long long int max = INT_MIN;
		for (long long int val : values)
			if (val > max)
				max = val;
		return max;
	}
	else if (5 == type) 
		return (values[0] > values[1]);
	else if (6 == type)
		return (values[0] < values[1]);
	else if (7 == type)
		return (values[0] == values[1]);

	throw;
}

std::string HexaToBinary(char hexa)
{
	switch (hexa) {
	case '0':
		return "0000";
		break;
	case '1':
		return "0001";
		break;
	case '2':
		return "0010";
		break;
	case '3':
		return "0011";
		break;
	case '4':
		return "0100";
		break;
	case '5':
		return "0101";
		break;
	case '6':
		return "0110";
		break;
	case '7':
		return "0111";
		break;
	case '8':
		return "1000";
		break;
	case '9':
		return "1001";
		break;
	case 'A':
		return "1010";
		break;
	case 'B':
		return "1011";
		break;
	case 'C':
		return "1100";
		break;
	case 'D':
		return "1101";
		break;
	case 'E':
		return "1110";
		break;
	case 'F':
		return "1111";
		break;
	}
}

long long int TranslateBinary(std::string val)
{
	long long int retVal = 0;
	long long int positionWorth = 1;
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

void parseInput()
{
	std::string input;
	std::cin >> input;

	for (char c : input)
	{
		binaryInput += HexaToBinary(c);
	}
}