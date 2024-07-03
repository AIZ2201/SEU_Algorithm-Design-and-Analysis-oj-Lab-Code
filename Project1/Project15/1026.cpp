#include <iostream>
#include <vector>
using namespace std;

long long maxSum(int start, int end, int signNumber, vector<int>& number);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> numberNumber;
	vector<int> signNumber;
	vector<vector<int>> number;
	int temp;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		numberNumber.push_back(temp);
		cin >> temp;
		signNumber.push_back(temp);
		vector<int> tempNumber;
		for (int j = 0; j < numberNumber[i]; j++)
		{
			cin >> temp;
			tempNumber.push_back(temp);
		}
		number.push_back(tempNumber);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxSum(0, numberNumber[i], signNumber[i], number[i]) << endl;
	}
}

long long maxSum(int start,int end, int signNumber, vector<int>& number)
{
	if (signNumber == 0)
	{
		long long cnt = 0;
		for (int i = start; i < end; i++)
		{
			cnt += number[i];
		}
		return cnt;
	}
	if (start == end - 1)
	{
		if (signNumber > 0)
			return 0;
		else
			return number[start];
	}
	long long max = 0;
	for (int i = start + 1; i < end; i++)
	{
		long long cnt = 0;
		for (int j = start; j < i; j++)
		{
			cnt += number[j];
		}
		cnt *= maxSum(i, end, signNumber - 1, number);
		if (cnt > max)
			max = cnt;
	}
	return max;
}