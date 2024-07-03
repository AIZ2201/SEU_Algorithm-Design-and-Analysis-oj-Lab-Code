#include <iostream>
#include <vector>
using namespace std;

int myfind(vector<int> number, int low, int high, int x, int father);
int myfind2(vector<int> number, int low, int high, int x, int father);

int main()
{
	int group = 0;
	cin >> group;
	vector<vector<int>> sizeAndx;
	vector<vector<int>> number;
	for (int i = 0; i < group; i++)
	{
		int size = 0;
		int x = 0;
		vector<int> temp1;
		vector<int> temp2;
		cin >> size >> x;
		temp2.push_back(size);
		temp2.push_back(x);
		for (int j = 0; j < size; j++)
		{
			int a = 0;
			cin >> a;
			temp1.push_back(a);
		}
		sizeAndx.push_back(temp2);
		number.push_back(temp1);
	}
	for (int i = 0; i < group; i++)
	{
		if (myfind2(number[i], 0, sizeAndx[i][0] - 1, sizeAndx[i][1], 0) == sizeAndx[i][1])
		{
			cout << "success, father is " << myfind(number[i], 0, sizeAndx[i][0] - 1, sizeAndx[i][1], 0) << endl;
		}
		else
		{
			cout<<"not found, father is "<< myfind(number[i], 0, sizeAndx[i][0] - 1, sizeAndx[i][1], 0) << endl;
		}
	}
}

int myfind(vector<int> number,int low,int high,int x,int father)
{
	int mid = (low + high) / 2;
	if (number[mid] == x)
		return number[father];
	else if (low >= high)
		return number[mid];
	else if (number[mid] < x)
	{
		return myfind(number, mid + 1, high, x, mid);
	}
	else if (number[mid] > x)
	{
		return myfind(number, low, mid - 1, x, mid);
	}
}

int myfind2(vector<int> number, int low, int high, int x, int father)
{
	int mid = (low + high) / 2;
	if (number[mid] == x)
		return x;
	else if (low >= high)
		return -1;
	else if (number[mid] < x)
	{
		return myfind2(number, mid + 1, high, x, mid);
	}
	else if (number[mid] > x)
	{
		return myfind2(number, low, mid - 1, x, mid);
	}
}