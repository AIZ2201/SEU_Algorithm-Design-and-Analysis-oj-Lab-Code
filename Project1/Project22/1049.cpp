#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

class Sensor
{
public:
    double left;
    double right;
    double time;
};

bool compare(Sensor& A, Sensor& B)
{
    return A.right < B.right;
}

double objective_function(double v, double x) 
{
    return (0.07 * v * v + 0.0391 * v - 13.196 + 390.95 / v) * x;
}

double find_minimum(double x) 
{
    double low = std::numeric_limits<double>::epsilon();
    double high = 1000;
    double mid;
    double precision = 1e-7;

    while ((high - low) > precision)
    {
        mid = (low + high) / 2;
        double f_mid = objective_function(mid, x);
        double f_mid_plus = objective_function(mid + precision, x);

        if (f_mid_plus < f_mid)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    return (low + high) / 2;
}

int main()
{
    int group;
    cin >> group;
    for (int turn = 0; turn < group; turn++)
    {
        int sensorNumber;
        double end;
        cin >> sensorNumber >> end;
        vector<Sensor> sensorArray(sensorNumber);
        for (int i = 0; i < sensorNumber; i++)
        {
            cin >> sensorArray[i].left >> sensorArray[i].right >> sensorArray[i].time;
        }
        sort(sensorArray.begin(), sensorArray.end(), compare);

        vector<double> VChangeLocationArray;
        vector<double> VArray;
        double currentLocation = 0;
        for (int i = 0; i < sensorNumber; i++)
        {
            double left = sensorArray[i].left;
            double right = sensorArray[i].right;
            double time = sensorArray[i].time;
            if (currentLocation < left)
            {
                VChangeLocationArray.push_back(left);
                VArray.push_back(find_minimum(left - currentLocation));
                currentLocation = left;
            }
            double totalTime = time;
            for (int j = i + 1; j < sensorNumber; j++)
            {
                if (sensorArray[j].right != right)
                {
                    i = j - 1;
                    break;
                }
                totalTime += sensorArray[j].time;
            }
            double tempV = (right - currentLocation) / totalTime;
            VChangeLocationArray.push_back(right);
            VArray.push_back(tempV);
            currentLocation = right;
        }
        if (currentLocation < end)
        {
            VChangeLocationArray.push_back(end);
            VArray.push_back(find_minimum(end - currentLocation));
        }

        cout << VChangeLocationArray.size() << endl;
        for (double tempX : VChangeLocationArray)
        {
            cout << fixed << setprecision(6) << tempX << ' ';
        }
        cout << endl;
        for (double tempV : VArray)
        {
            cout << fixed << setprecision(6) << tempV << ' ';
        }
        cout << endl;
    }
}