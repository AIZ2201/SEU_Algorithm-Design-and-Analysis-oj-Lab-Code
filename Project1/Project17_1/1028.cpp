#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

class Map 
{
public:
    int vertexNumber, edgeNumber, start, end;
};

int minLength(Map mapData, vector<vector<pair<int, int>>>& adjList)
{
    vector<int> distance(mapData.vertexNumber + 1, INT_MAX);
    distance[mapData.start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, mapData.start });
    while (!pq.empty()) 
    {
        int dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();
        if (dist > distance[current]) 
            continue;
        for (const auto& neighbor : adjList[current]) 
        {
            int next = neighbor.first;
            int length = neighbor.second;
            if (distance[current] + length < distance[next]) 
            {
                distance[next] = distance[current] + length;
                pq.push({ distance[next], next });
            }
        }
    }
    return (distance[mapData.end] == INT_MAX) ? -1 : distance[mapData.end];
}

int main() {
    int group;
    cin >> group;
    vector<Map> mapData(group);
    vector<vector<vector<pair<int, int>>>> edgeData(group);
    for (int i = 0; i < group; i++) 
    {
        cin >> mapData[i].vertexNumber >> mapData[i].edgeNumber >> mapData[i].start >> mapData[i].end;
        edgeData[i].resize(mapData[i].vertexNumber + 1);
        for (int j = 0; j < mapData[i].edgeNumber; j++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edgeData[i][u].emplace_back(v, w);
            edgeData[i][v].emplace_back(u, w);
        }
    }
    for (int i = 0; i < group; i++)
    {
        cout << minLength(mapData[i], edgeData[i]) << endl;
    }
}