#include <iostream>
#include<iomanip>
#include<vector>
using namespace std;

int main()
{
    int group;
    cin >> group;
    int keyNumber;
    vector<double> result(group);
    for (int i = 0; i < group; i++)
    {
        cin >> keyNumber;
        vector<int> key(keyNumber);
        vector<double> searchP(keyNumber + 1);
        vector<double> noonSearchP(keyNumber + 1);
        for (int j = 0; j < keyNumber; j++)
            cin >> key[j];
        for (int j = 1; j <= keyNumber; j++)
            cin >> searchP[j];
        for (int j = 0; j <= keyNumber; j++)
            cin >> noonSearchP[j];
        vector<vector<double>> cost(keyNumber + 1, vector<double>(keyNumber + 1, 0));
        vector<vector<double>> weight(keyNumber + 1, vector<double>(keyNumber + 1, 0));
        for (int j = 0; j <= keyNumber; j++)
        {
            weight[j][j] = noonSearchP[j];
        }
        for (int j = 1; j <= keyNumber; j++)
            for (int k = 0; k <= keyNumber - j; k++)
            {
                int temp = j + k;
                cost[k][temp] = 2147483647;
                weight[k][temp] = weight[k][temp - 1] + searchP[temp] + noonSearchP[temp];
                for (int m = k + 1; m <= temp; m++)
                    cost[k][temp] = min(weight[k][temp] + cost[k][m - 1] + cost[m][temp], cost[k][temp]);
            }
        result[i] = cost[0][keyNumber];
    }
    for (int i = 0; i < group; i++)
    {
        cout << fixed << setprecision(6) << result[i] << endl;
    }
}