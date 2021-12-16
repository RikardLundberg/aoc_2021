#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int TranslateBinary(std::string val);
void parseInput();
std::chrono::time_point<std::chrono::steady_clock> start_time;
std::string HexaToBinary(char hexa);
void ReadOperator();
std::string binaryInput = "";
int totalVersion = 0;
int counter = 0;

int main()
{
	parseInput();

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
		ReadOperator();
	}

	std::cout << "Total Version: " << totalVersion << std::endl;
}

void ReadOperator()
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
	while (morePackages)
	{
		for (int sub = 0; sub < L; sub++)
		{
			totalVersion += TranslateBinary(binaryInput.substr(counter, 3));
			counter += 3;
			int type = TranslateBinary(binaryInput.substr(counter, 3));
			counter += 3;
			if (type != 4)
				ReadOperator();
			else
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
			if (isFifteen) {
				morePackages = (counter < subPackSize);
				break;
			}
		}
		if (!isFifteen)
			morePackages = false;
	}
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