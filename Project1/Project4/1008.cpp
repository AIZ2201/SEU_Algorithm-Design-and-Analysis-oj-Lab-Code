#include <iostream>
#include <vector>
using namespace std;

int numberofProtector(vector<int> number, int size);
int numberofProtector2(vector<int> number, int size, int times);

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
	vector<int> result1;
	vector<int> result2;
	for (int i = 0; i < group; i++)
	{
		result1.push_back(numberofProtector(number[i],size[i]));
	} 
	for (int i = 0; i < group; i++)
	{
		result2.push_back(numberofProtector2(number[i], size[i],0));
	}
	for (int i = 0; i < group; i++)
	{
		cout << result1[i] << " " << result2[i] << endl;
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

int numberofProtector2(vector<int> number, int size,int times)
{
	if (number.size() == 0)
		return times;
	vector<int>temp(size, 1);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (number[j] > number[i] && temp[j] + 1 > temp[i])
				temp[i] = temp[j] + 1;
		}
	}
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (temp[i] > max)
		{ 
			max = temp[i];
		}
	}
	for (int i = size - 1; i >= 0; i--)
	{
		if (temp[i] == max)
		{
			max--;
			size--;
			number.erase(number.begin() + i);
		}
	}
	return numberofProtector2(number, size, ++times);
}