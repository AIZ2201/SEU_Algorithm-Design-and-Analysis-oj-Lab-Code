#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double partNumber(int islandNumber, vector<int> destroyP);

int main()
{
	int group;
	cin >> group;
	vector<int> islandNumber(group);
	vector<vector<int>> destroyP;
	for (int i = 0; i < group; i++)
	{
		cin >> islandNumber[i];
		vector<int> tempP(islandNumber[i] - 1);
		for (int j = 0; j < islandNumber[i] - 1; j++)
		{
			cin >> tempP[j];
		}
		destroyP.push_back(tempP);
	}
	for (int i = 0; i < group; i++)
	{
		cout << fixed << setprecision(6) << partNumber(islandNumber[i], destroyP[i]) << endl;
	}
}

double partNumber(int islandNumber, vector<int> destroyP)
{
	if (islandNumber == 1)
		return 1;
	double pNum = 0;
	vector<double> douDestroyP;
	for (int temp : destroyP)
	{
		douDestroyP.push_back(temp / static_cast<double>(100));
	}
	int round = 1 << (islandNumber - 1);
	for (int i = 0; i < round; i++)
	{
		int temp = i;
		int cnt = 1;
		double tempP = 1;
		for (int j = 0; j < islandNumber - 1; j++)
		{
			if (i & (1 << j))
			{
				tempP *= douDestroyP[j];
				cnt++;
			}
			else 
			{
				tempP *= (1 - douDestroyP[j]);
			}
		}
		pNum += cnt * tempP;
	}
	return pNum;
}