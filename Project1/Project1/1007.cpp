#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long returnMax(int size, int quantity, long long number);

int main()
{
	int group = 0;
	cin >> group;
	vector<int> size;
	vector<int> quantity;
	vector<long long> number;
	for (int i = 0; i < group; i++)
	{
		int tempsize = 0;
		int tempquantity = 0;
		long long tempnumber = 0;
		cin >> tempsize >> tempquantity >> tempnumber;
		size.push_back(tempsize);
		quantity.push_back(tempquantity);
		number.push_back(tempnumber);
	}
	for (int i = 0; i < group; i++)
	{
		cout << returnMax(size[i], quantity[i], number[i]) << endl;
	}
}

long long returnMax(int size,int quantity, long long number)
{
	long long result = 0;
	if (quantity == 0)
		return number;
	if (quantity >= size)
		return 0;
	int screw = 10;
	for (int i = 1; i < size; i++)
	{
		long long temp = (number / screw) * returnMax(i, quantity - 1, number % screw);
		if (temp > result)
		{
			result = temp;
		}
		screw *= 10;
	}
	return result;
}