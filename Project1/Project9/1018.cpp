#include <iostream>
#include <vector>
using namespace std;

int ValueCanTake(vector<int> itemSize, vector<int> itemValue, int itemNumber, int bagCapacity);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> itemNumber;
	vector<int> bagCapacity;
	vector<vector<int>> itemSize;
	vector<vector<int>> itemValue;
	for (int i = 0; i < group; i++)
	{
		int temp = 0;
		cin >> temp;
		itemNumber.push_back(temp);
		cin >> temp;
		bagCapacity.push_back(temp);
		vector<int> tempItemSize;
		vector<int> tempItemValue;
		for (int j = 0; j < itemNumber[i]; j++)
		{
			cin >> temp;
			tempItemSize.push_back(temp);
			cin >> temp;
			tempItemValue.push_back(temp);
		}
		itemSize.push_back(tempItemSize);
		itemValue.push_back(tempItemValue);
	}
	for (int i = 0; i < group; i++)
	{
		cout << ValueCanTake(itemSize[i], itemValue[i], itemNumber[i], bagCapacity[i]) << endl;
	}
}

int ValueCanTake(vector<int> itemSize, vector<int> itemValue,int itemNumber,int bagCapacity)
{
	vector<vector<int>> tempC(itemNumber + 1, vector<int>(bagCapacity + 1, 0));
	for (int i = 1; i < itemNumber + 1; i++)
	{
		for (int j = 1; j < bagCapacity + 1; j++)
		{
			if (itemSize[i - 1] > j || (tempC[i - 1][j - itemSize[i - 1]] == 0 && j - itemSize[i - 1] != 0))
				tempC[i][j] = tempC[i - 1][j];
			else
			{
				tempC[i][j] = tempC[i - 1][j - itemSize[i - 1]] + itemValue[i - 1] > tempC[i - 1][j] ? tempC[i - 1][j - itemSize[i - 1]] + itemValue[i - 1] : tempC[i - 1][j];
			}
		}
	}
	return tempC[itemNumber][bagCapacity];
}