#include <iostream>
#include <vector>
#include <string>
using namespace std;

int maxLength(string strA, string strB);

int main()
{
	int group = 0;
	cin >> group;
	vector<string> strA;
	vector<string> strB;
	string temp;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		strA.push_back(temp);
		cin >> temp;
		strB.push_back(temp);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxLength(strA[i], strB[i]) << endl;
	}
}

int maxLength(string strA, string strB)
{
	vector<vector<int>> dp(strA.length() + 1, vector<int>(strB.length() + 1, 0));
	for (int i = 1; i <= strA.length(); i++)
	{
		for (int j = 1; j <= strB.length(); j++)
		{
			if (strA[i - 1] == strB[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else if (dp[i - 1][j] >= dp[i][j - 1])
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = dp[i][j - 1];
		}
	}
	return dp[strA.length()][strB.length()];
}