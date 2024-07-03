#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double minPay(int end, int start, vector<int>& critical, vector<double>& searchP, vector<double>& noonSearchP, int depth);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> criticalNumber;
	vector<vector<int>> critical;
	vector<vector<double>> searchP;
	vector<vector<double>> noonSearchP;
	double temp = 0;
	for (int i = 0; i < group; i++)
	{
		cin >> temp;
		criticalNumber.push_back(temp);
		vector<int> tempCritical;
		vector<double> tempSearchP;
		vector<double> tempNoonSearchP;
		for (int j = 0; j < criticalNumber[i]; j++)
		{
			cin >> temp;
			tempCritical.push_back(temp);
		}
		for (int j = 0; j < criticalNumber[i]; j++)
		{
			cin >> temp;
			tempSearchP.push_back(temp);
		}
		for (int j = 0; j < criticalNumber[i] + 1; j++)
		{
			cin >> temp;
			tempNoonSearchP.push_back(temp);
		}
		critical.push_back(tempCritical);
		searchP.push_back(tempSearchP);
		noonSearchP.push_back(tempNoonSearchP);
	}
	for (int i = 0; i < group; i++)
	{
		cout << fixed << setprecision(6) << minPay(criticalNumber[i], 0, critical[i], searchP[i], noonSearchP[i], 1) << endl;
	}
}

double minPay(int end, int start, vector<int>& critical, vector<double>& searchP, vector<double>& noonSearchP,int depth)
{
	if (end == start)
		return noonSearchP[start] * (depth - 1);
	double min = 2147483647;
	for (int i = start; i < end; i++)
	{
		double cnt = 0;
		cnt = minPay(i, start, critical, searchP, noonSearchP, depth + 1)
			+ searchP[i] * depth
			+ minPay(end, 1 + i, critical, searchP, noonSearchP, depth + 1);
		if (cnt < min)
			min = cnt;
	}
	return min;
}