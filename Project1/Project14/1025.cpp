#include <iostream>
#include <vector>
using namespace std;

int maxLength(int length, vector<int> number);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> length;
	vector<vector<int>> number;
	int temp = 0;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		length.push_back(temp);
		vector<int> tempNumber;
		for (int j = 0; j < length[i]; j++)
		{
			cin >> temp;
			tempNumber.push_back(temp);
		}
		number.push_back(tempNumber);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxLength(length[i], number[i]) << endl;
	}
}

int maxLength(int length, vector<int> number)
{
	vector<int> temp(length, 0);
	int max = 1;
	temp[0] = number[0];
	for (int i = 1; i < length; i++)
	{
		if (number[i] < temp[0])
			temp[0] = number[i];
		else if (number[i] >= temp[max - 1])
		{
			temp[max++] = number[i];
		}
		else
		{
			int left = 0, right = max - 1;
			while (left < right)
			{
				int mid = left + (right - left) / 2;
				if (temp[mid] <= number[i])//注意取<= 这样才能把left设置到大于等于number[i]的最小下标（尤其是在number[i]与number[0]相同时）
				{
					left = mid + 1;
				}
				else 
				{
					right = mid;
				}
			}
			temp[left] = number[i];
		}
	}
	return max;
}