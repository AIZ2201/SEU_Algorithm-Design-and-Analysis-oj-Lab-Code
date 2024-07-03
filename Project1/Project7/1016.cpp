#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& nums, int low, int high);
void quickSort(vector<int>& nums, int low, int high);
void sortDescending(vector<int>& nums);
bool ifSun(vector<int>number, int size, int find);

int main()
{
	int group = 0;
	cin >> group;
	vector<int>size;
	vector<int>findNumber;
	vector<vector<int>>number;
	for (int i = 0; i < group; i++)
	{
		int tempsize = 0;
		int tempfindnumber = 0;
		cin >> tempsize;
		cin >> tempfindnumber;
		size.push_back(tempsize);
		findNumber.push_back(tempfindnumber);
		vector<int>t_number;
		for (int j = 0; j < tempsize; j++)
		{
			int tempnumber = 0;
			cin >> tempnumber;
			t_number.push_back(tempnumber);
		}
		number.push_back(t_number);
	}
	for (int i = 0; i < group; i++)
	{
		if (ifSun(number[i], size[i], findNumber[i]))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
}

int partition(vector<int>& nums, int low, int high) 
{
	int pivot = nums[high]; 
	int i = low - 1; 

	for (int j = low; j < high; j++) {
		if (nums[j] >= pivot) {
			i++;
			swap(nums[i], nums[j]);
		}
	}

	swap(nums[i + 1], nums[high]);
	return i + 1; 
}

void quickSort(vector<int>& nums, int low, int high)
{
	if (low < high) {
		int pi = partition(nums, low, high); 
		quickSort(nums, low, pi - 1); 
		quickSort(nums, pi + 1, high); 
	}
}

void sortDescending(vector<int>& nums)
{
	int n = nums.size();
	quickSort(nums, 0, n - 1);
}

bool ifSun(vector<int>number, int size, int find)
{
	sortDescending(number);
	vector<int> temp;
	for (int i = 0; i < size; i++)
	{
		temp.push_back(find - number[i]);
	}
	int left = 0;
	int right = size - 1;
	for (;;)
	{
		if (left >= size || right < 0)
			return 0;
		if (temp[left] == number[right])
			return 1;
		if (temp[left] < number[right])
		{
			left++;
			continue;
		}
		else
		{
			right--;
			continue;
		}
	}
}