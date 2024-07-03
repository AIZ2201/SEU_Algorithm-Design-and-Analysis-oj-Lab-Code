#include <iostream>
#include <vector>
using namespace std;

int maxGet(int length, int priceNumber, vector<int> sellLenth, vector<int> sellPrice);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> length;
	vector<int> priceNumber;
	vector<vector<int>> sellLenth;
	vector<vector<int>> sellPrice;
	int temp = 0;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		length.push_back(temp);
		cin >> temp;
		priceNumber.push_back(temp);
		vector<int> tempLenth;
		vector<int> tempPrice;
		for (int j = 0; j < priceNumber[i]; j++)
		{
			cin >> temp;
			tempLenth.push_back(temp);
			cin >> temp;
			tempPrice.push_back(temp);
		}
		sellLenth.push_back(tempLenth);
		sellPrice.push_back(tempPrice);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxGet(length[i], priceNumber[i], sellLenth[i], sellPrice[i]) << endl;
	}
}

int maxGet(int length, int priceNumber, vector<int> sellLenth, vector<int> sellPrice)
{
	vector<int> dp(length + 1, 0);
	for (int templenth = 1; templenth < length + 1; templenth++)
	{
		int max = dp[templenth - 1];
		for (int i = 0; i < priceNumber; i++)
		{
			if (templenth - sellLenth[i] < 0)
				break;
			int cnt = 0;
			cnt = sellPrice[i] + dp[templenth - sellLenth[i]];
			if (cnt > max)
				max = cnt;
		}
		dp[templenth] = max;
	}
	return dp[length];
}