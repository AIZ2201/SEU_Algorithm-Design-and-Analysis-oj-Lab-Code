#include <iostream>
#include <vector>
using namespace std;

int minPay(int matrixNumber, vector<int>& sizeNumber, int start, int end);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> matrixNumber;
	vector<vector<int>> sizeNumber;
	int temp = 0;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		matrixNumber.push_back(temp);
		vector<int> tempNumber;
		for (int j = 0; j < 2 * matrixNumber[i]; j++)
		{
			cin >> temp;
			tempNumber.push_back(temp);
		}
		sizeNumber.push_back(tempNumber);
	}
	for (int i = 0; i < group; i++)
	{
		cout << minPay(matrixNumber[i], sizeNumber[i], 0, 2 * matrixNumber[i] - 1) << endl;
	}
}

int minPay(int matrixNumber, vector<int>& sizeNumber,int start,int end)
{
	if (matrixNumber == 1)
	{
		return 0;
	}
	int min = 2147483647;
	for (int i = 1; i < matrixNumber; i++)
	{
		int cnt = 0;
		cnt += sizeNumber[start] * sizeNumber[start + 2 * i - 1] * sizeNumber[end];
		cnt += minPay(i, sizeNumber, 0, 2 * i - 1) + minPay(matrixNumber - i, sizeNumber, 2 * i, end);
		if (cnt < min)
			min = cnt;
	}
	return min;
}