#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int minLength(int dotNumber, vector<int> dotArray);

int main()
{
	int group;
	cin >> group;
	vector<int> dotNumber(group);
	vector<vector<int>> dotArray;
	for (int i = 0; i < group; i++)
	{
		cin >> dotNumber[i];
		vector<int> tempDot(2 * dotNumber[i]);
		for (int j = 0; j < 2 * dotNumber[i]; j++)
		{
			cin >> tempDot[j];
		}
		dotArray.push_back(tempDot);
	}
	for (int i = 0; i < group; i++)
	{
		cout << minLength(dotNumber[i], dotArray[i]) << endl;
	}
}

int minLength(int dotNumber, vector<int> dotArray)
{
	queue<int> temp;
	int tag = -1;
	int length = 0;
	for (int i = 0; i < 2 * dotNumber; i++)
	{
		if (temp.empty())
		{
			temp.push(i);
			tag = dotArray[i];
		}
		else if (dotArray[i] == tag)
		{
			temp.push(i);
			tag = dotArray[i];
		}
		else
		{
			length += i - temp.front();
			temp.pop();
		}
	}
	return length;
}