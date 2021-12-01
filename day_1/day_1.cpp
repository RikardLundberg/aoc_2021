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