#include <iostream>
#include <algorithm>
using namespace std;

class Work 
{
public:
    int workDDL;
    int workValue;
};

long long maxValue(int workNumber, Work* workArray);

bool compare(const Work& A, const Work& B)
{
    return A.workValue > B.workValue;
}

int main() {
    int group;
    cin >> group;
    int* workNumber = new int[group];
    Work** workArray = new Work * [group];
    for (int i = 0; i < group; i++) 
    {
        cin >> workNumber[i];
        workArray[i] = new Work[workNumber[i]];
        for (int j = 0; j < workNumber[i]; j++)
        {
            cin >> workArray[i][j].workDDL >> workArray[i][j].workValue;
        }
    }
    for (int i = 0; i < group; i++) 
    {
        cout << maxValue(workNumber[i], workArray[i]) << endl;
    }
    for (int i = 0; i < group; i++) 
    {
        delete[] workArray[i];
    }
    delete[] workArray;
    delete[] workNumber;
}

long long maxValue(int workNumber, Work* workArray)
{
    int maxDDL = 0;
    for (int i = 0; i < workNumber; i++)
    {
        if (workArray[i].workDDL > maxDDL) 
        {
            maxDDL = workArray[i].workDDL;
        }
    }
    int* value = new int[maxDDL + 1]();
    sort(workArray, workArray + workNumber, compare);
    for (int i = 0; i < workNumber; i++)
    {
        for (int j = workArray[i].workDDL; j >= 1; j--) 
        {
            if (value[j] == 0) 
            {
                value[j] = workArray[i].workValue;
                break;
            }
        }
    }
    long long result = 0;
    for (int i = 1; i <= maxDDL; i++) 
    {
        result += value[i];
    }
    delete[] value;
    return result;
}
