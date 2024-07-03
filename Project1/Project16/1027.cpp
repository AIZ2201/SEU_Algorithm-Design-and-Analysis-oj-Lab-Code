#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class  Activity 
{
public:
    int start, end, value;
};

bool compare(Activity a, Activity b)
{
    return a.end < b.end;
}

int binarySearch(vector<Activity>& activities, int endIndex, int startTime) 
{
    int low = 0, high = endIndex - 1;
    while (low <= high) 
    {
        int mid = (low + high) / 2;
        if (activities[mid].end <= startTime) 
        {
            if (activities[mid + 1].end <= startTime) 
            {
                low = mid + 1;
            }
            else 
            {
                return mid;
            }
        }
        else 
        {
            high = mid - 1;
        }
    }
    return -1;
}

int maxSum(int activityNumber, vector<Activity>& activities) 
{
    sort(activities.begin(), activities.end(), compare);
    vector<int> dp(activityNumber);
    dp[0] = activities[0].value;
    for (int i = 1; i < activityNumber; i++) 
    {
        int includeWeight = activities[i].value;
        int l = binarySearch(activities, i, activities[i].start);
        if (l != -1)
        {
            includeWeight += dp[l];
        }
        dp[i] = max(dp[i - 1], includeWeight);
    }
    return dp[activityNumber - 1];
}

int main() 
{
    int group;
    cin >> group;
    vector<int> activityNumber;
    vector <vector<Activity>> activities;
    int temp;
    for (int i = 0; i < group; i++) 
    {
        cin >> temp;
        activityNumber.push_back(temp);
        vector<Activity> tempActivities(activityNumber[i]);
        for (int j = 0; j < activityNumber[i]; j++) 
        {
            cin >> tempActivities[j].start >> tempActivities[j].end >> tempActivities[j].value;
        }
        activities.push_back(tempActivities);
    }
    for (int i=0;i<group;i++)
    {
        cout << maxSum(activityNumber[i],activities[i]) << endl;
    }
}