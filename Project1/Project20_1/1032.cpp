#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double partNumber(const vector<double>& destroyP, int islandNumber);

int main()
{
    int group;
    cin >> group;
    vector<double> answer(group);

    for (int i = 0; i < group; i++)
    {
        int islandNumber;
        cin >> islandNumber;
        vector<double> destroyP(islandNumber - 1);

        for (int j = 0; j < islandNumber - 1; j++)
        {
            cin >> destroyP[j];
            destroyP[j] /= 100.0;
        }

        answer[i] = partNumber(destroyP, islandNumber);
    }

    for (double res : answer)
    {
        cout << fixed << setprecision(6) << res << endl;
    }
}

double partNumber(const vector<double>& destroyP, int islandNumber)
{
    double* even = new double[islandNumber + 1];
    double* odd = new double[islandNumber + 1];
    for (int i = 0; i < islandNumber + 1; i++)
    {
        odd[i] = 0;
        even[i] = 0;
    }
    even[1] = 1;
    for (int i = 1; i < islandNumber; i++)
    {
        if (i % 2 == 1)
        {
            for (int j = 1; j <= i + 1; j++)
            {
                odd[j] = even[j - 1] * destroyP[i - 1] + even[j] * (1 - destroyP[i - 1]);
            }
        }
        else
        {
            for (int j = 1; j <= i + 1; j++)
            {
                even[j] = odd[j - 1] * destroyP[i - 1] + odd[j] * (1 - destroyP[i - 1]);
            }
        }
    }
    double result = 0;
    if (islandNumber % 2 == 1)
    {
        for (int i = 1; i <= islandNumber; i++)
        {
            result += i * even[i];
        }
    }
    else
    {
        for (int i = 1; i <= islandNumber; i++)
        {
            result += i * odd[i];
        }
    }
    return result;
}
