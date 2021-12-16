#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int TranslateBinary(std::string val);
void parseInput();
std::chrono::time_point<std::chrono::steady_clock> start_time;
std::string HexaToBinary(char hexa);
int ReadOperator(int currentCounter);
std::string binaryInput = "";
int totalVersion = 0;

int main()
{
	parseInput();

	for (int i = 0; i < binaryInput.size(); i++)
	{
		int counter = 0;
		std::string versionStr, typeStr;
		versionStr += binaryInput.substr(0, 3);
		int version = TranslateBinary(versionStr);
		totalVersion += version;
		typeStr += binaryInput.substr(3,3);
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
			counter += ReadOperator(counter);
		}

		for (int j = 0; j < counter; j++)
			i++;

		int extraZeroes = 4 - (counter % 4);
		for (int z = 0; z < extraZeroes; z++)
			i++;
	}


	std::cout << "Total Version: " << totalVersion << std::endl;
}

int ReadOperator(int currentCounter)
{
	bool isFifteen = false; // else eleven
	if (binaryInput[currentCounter] == '0')
		isFifteen = true;
	currentCounter++;
	int Lcounter = isFifteen ? 15 : 11;
	std::string Lstr;
	for (int j = 0; j < Lcounter; j++)
	{
		Lstr += binaryInput.substr(currentCounter, 1);
		currentCounter++;
	}
	int L = TranslateBinary(Lstr);
	int subPackSize = L + currentCounter;
	bool morePackages = isFifteen || L > 0;
	while (morePackages)
	{
		for (int sub = 0; sub < L; sub++)
		{
			totalVersion += TranslateBinary(binaryInput.substr(currentCounter, 3));
			currentCounter += 3;
			int type = TranslateBinary(binaryInput.substr(currentCounter, 3));
			currentCounter += 3;
			if (type != 4)
				currentCounter = ReadOperator(currentCounter);
			else
			{
				bool lastGroup = false;
				while (!lastGroup)
				{
					std::string subGroup;
					subGroup += binaryInput.substr(currentCounter, 5);
					currentCounter += 5;
					if (subGroup[0] == '0')
						lastGroup = true;
				}
			}
			if (isFifteen) {
				morePackages = (currentCounter < subPackSize);
				break;
			}
		}
		if (!isFifteen)
			morePackages = false;
	}
	return currentCounter;
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

void parseInput()
{
	std::string input;
	std::cin >> input;

	for (char c : input)
	{
		binaryInput += HexaToBinary(c);
	}
}