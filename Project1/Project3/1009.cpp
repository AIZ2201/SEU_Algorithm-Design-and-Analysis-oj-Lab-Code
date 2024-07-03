#include <iostream>
#include <vector>
using namespace std;

int numberofProtector(vector<int> number, int size);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> size;
	vector<vector<int>> number;
	for (int i = 0; i < group; i++)
	{
		int a = 0;
		cin >> a;
		size.push_back(a);
		vector<int> temp;
		for (int j = 0; j < size[i]; j++)
		{
			int b = 0;
			cin >> b;
			temp.push_back(b);
		}
		number.push_back(temp);
	}
	for (int i = 0; i < group; i++)
	{
		cout << numberofProtector(number[i], size[i]) << endl;
	}
}

int numberofProtector(vector<int> number, int size)
{
	vector<int>temp(size, 1);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (number[j] > number[i] && temp[j] + 1 > temp[i])
				temp[i] = temp[j] + 1;
		}
	}
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		if (temp[i] > result)
		{
			result = temp[i];
		}
	}
	return result;
}