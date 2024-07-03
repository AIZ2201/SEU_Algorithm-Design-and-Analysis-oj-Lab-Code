#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Work
{
public:
	int workDDL;
	int workValue;
};

int maxValue(int workNumber, vector<Work>& workArray);

int main()
{
	int group;
	cin >> group;
	vector<int> workNumber(group);
	vector<vector<Work>> workArray;
	for (int i = 0; i < group; i++)
	{
		cin >> workNumber[i];
		vector<Work> tempWork(workNumber[i]);
		for (int j = 0; j < workNumber[i]; j++)
		{
			cin >> tempWork[j].workDDL >> tempWork[j].workValue;
		}
		workArray.push_back(tempWork);
	}
	for (int i = 0; i < group; i++)
	{
		cout << maxValue(workNumber[i], workArray[i]) << endl;
	}
}

bool compare(const Work& A, const Work& B)
{
	return A.workValue > B.workValue;
}

int maxValue(int workNumber, vector<Work>& workArray)
{
	vector<int> value(workArray[workArray.size() - 1].workDDL + 1, 0);
	sort(workArray.begin(), workArray.end(), compare);
	for (Work temp : workArray)
	{
		for (int i = temp.workDDL; i >= 1; i--)
		{
			if (value[i] == 0)
			{
				value[i] = temp.workValue;
				break;
			}
		}
	}
	int result = 0;
	for (int temp : value)
	{
		result += temp;
	}
	return result;
}