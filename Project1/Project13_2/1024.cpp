#include <iostream>
#include<iomanip>
using namespace std;

double cost[501][501], weight[501][501];
int key[500];
double searchP[501];
double noonSearchP[501];

int main()
{
    int group;
    cin >> group;
    double* result = new double[group];
    int keyNumber;
    for (int m = 0; m < group; m++)
    {
        cin >> keyNumber;
        for (int j = 0; j < keyNumber; j++)
            cin >> key[j];
        for (int j = 1; j <= keyNumber; j++)
            cin >> searchP[j];
        for (int j = 0; j <= keyNumber; j++)
            cin >> noonSearchP[j];
        for (int j = 0; j <= keyNumber; j++)
        {
            cost[j][j] = 0;
            weight[j][j] = noonSearchP[j];
        }
        for (int j = 1; j <= keyNumber; j++)
            for (int k = 0; k <= keyNumber - j; k++)
            {
                int temp = k + j;
                cost[k][temp] = 2147483647;
                weight[k][temp] = weight[k][temp - 1] + searchP[temp] + noonSearchP[temp];
                for (int m = k + 1; m <= temp; m++)
                    cost[k][temp] = min(weight[k][temp] + cost[k][m - 1] + cost[m][temp], cost[k][temp]);
            }
        result[m] = cost[0][keyNumber];
    }
    for (int i = 0; i < group; i++)
    {
        cout << fixed << setprecision(6) << result[i] << endl;
    }
    delete[] result;
}

