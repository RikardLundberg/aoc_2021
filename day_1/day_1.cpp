#include <iostream>
#include <vector>

int main()
{

	int n;
	int box[3]{0,0,0};
	int counter = 0;
	int prevSum = -1;

	int count = 0;
	while (std::cin >> n)
	{
		box[counter] = n;
		counter++;
		if (counter == 3)
			counter = 0;

		if (box[2] != 0) {
			int boxSum = box[0] + box[1] + box[2];
			if (prevSum != -1)
			{
				if (boxSum > prevSum)
					count++;
			}
			prevSum = boxSum;
		}
	}

	std::cout << std::endl << count;
}


/*
#include <iostream>
#include <vector>
#include <algorithm>

void compareInputs(std::vector<int> inputs, int& a, int& b, int &c);

int main()
{
	int n;
	std::vector<int> inputs;

	while (std::cin >> n)
		inputs.push_back(n);

	std::sort(inputs.begin(), inputs.end());

	int a, b, c;
	compareInputs(inputs, a, b, c);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;

	std::cout << a * b * c << std::endl;
}

void compareInputs(std::vector<int> inputs, int& a, int& b, int &c)
{
	for (int input : inputs)
	{
		for (int i = 0; i < inputs.size(); i++) {
			auto preSum = input + inputs[i];
			if (preSum > 2020)
				break;
			for (int j = 0; j < inputs.size(); j++) {
				auto sum = preSum + inputs[j];
				if (sum == 2020) {
					a = input;
					b = inputs[j];
					c = inputs[i];
					return;
				}
				else if (sum > 2020)
					break;
			}
		}
	}
}
*/