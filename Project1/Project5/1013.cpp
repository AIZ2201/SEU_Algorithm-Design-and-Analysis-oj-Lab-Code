#include <iostream>
#include <vector>
using namespace std;

int pairNumber(vector<int>& number, int start, int end);

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
		cout << pairNumber(number[i], 0, size[i] - 1) << endl;
	}
}

int pairNumber(vector<int>& number, int start, int end)
{
	int cnt = 0;
	if (end - start == 0)
	{
		return cnt;
	}
	if (end - start == 1)
	{
		if (number[end] > number[start])
		{
			int temp = number[start];
			number[start] = number[end];
			number[end] = temp;
			return cnt;
		}
		else
		{
			return ++cnt;
		}
	}
	int mid = (end + start) / 2;
	cnt += pairNumber(number, start, mid) + pairNumber(number, mid + 1, end);
	int j = mid + 1;
	int i = start;
	vector<int>temp;
	for (; ;)
	{
		if (number[i] > number[j])
		{
			temp.push_back(number[i]);
			cnt += end - j + 1;
			i++;
		}
		else
		{
			temp.push_back(number[j]);
			j++;
		}
		if (j > end && i <= mid)
		{
			for (;;)
			{
				if (i > mid)
					break;
				temp.push_back(number[i++]);
			}
		}
		if (i > mid && j <= end)
		{
			for (;;)
			{
				if (j > end)
					break;
				temp.push_back(number[j++]);
			}
		}
		if (i > mid && j > end)
			break;
	}
	for (int i = start; i <= end; i++)
	{
		number[i] = temp[i - start];
	}
	return cnt;
}