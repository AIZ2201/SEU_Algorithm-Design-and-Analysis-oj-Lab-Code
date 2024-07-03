#include<iostream>
#include<limits.h>
#include<cmath>
using namespace std;
struct Matrix
{
	Matrix(long long r1 = 0, long long c1 = 0)
	{
		r = r1; c = c1;
	}
	long long r;
	long long c;
};
const long long Max = LLONG_MAX;
Matrix m_set[501];
long long dp[501][501];
int main()
{
	int T;
	cin >> T;

	while (T--)
	{
		int N; long long temp;
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			cin >> m_set[i].r;
			cin >> m_set[i].c;
			dp[i][i] = 0;
		}
		for (int i = 1; i <= N - 1; i++)
		{
			for (int j = 1; j <= N - i; j++)
			{
				int k = i + j;
				dp[j][k] = Max;
				for (int l = j; l <= k - 1; l++)
				{
					temp = dp[j][l] + dp[l + 1][k] + m_set[j].r * m_set[l].c * m_set[k].c;
					if (dp[j][k] > temp)dp[j][k] = temp;
				}

			}
		}
		cout << dp[1][N] << endl;
	}

	return 0;
}