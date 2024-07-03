#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int>number, int size);

int main()
{
	int group = 0;
	cin >> group;
	vector<int>size;
	vector<vector<int>>number;
	for (int i = 0; i < group; i++)
	{
		int tempsize = 0;
		cin >> tempsize;
		size.push_back(tempsize);
		vector<int>t_number;
		for (int j = 0; j < tempsize; j++)
		{
			int tempnumber = 0;
			cin >> tempnumber;
			t_number.push_back(tempnumber);
		}
		number.push_back(t_number);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxSum(number[i], size[i]) << endl;
	}
}

int maxSum(vector<int>number, int size)
{
	int max = number[0];
	int temp = number[0];
	for (int i = 1; i < size; i++)
	{
		temp + number[i] > number[i] ? temp += number[i] : temp = number[i];
		max > temp ? max = max : max = temp;
	}
	return max;
}