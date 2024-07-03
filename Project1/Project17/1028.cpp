#include <iostream>
#include <vector>
using namespace std;

class Map
{
public:
	int vertexNumber, edgeNumber, start, end;
};

class Edge
{
public:
	int start, end, length;
};

int minLength(Map mapData, vector<Edge> edgeData)
{
	vector<int> usedEdge(mapData.edgeNumber, 0);
	vector<int> tempMinLength(mapData.vertexNumber + 1, 2147483647);
	tempMinLength[mapData.start] = 0;
	int cnt = 0;
	/*for (int i = 0; i < mapData.edgeNumber; i++)
	{
		if (edgeData[i].start == mapData.start)
		{
			if (edgeData[i].length < tempMinLength[edgeData[i].end])
			{
				tempMinLength[edgeData[i].end] = edgeData[i].length;
			}
			usedEdge[i] = 1;
		}
		cnt += usedEdge[i];
	}
	if (cnt == 0)
		return -1;
	cnt = 0;*/
	for (int i = 0;; i++)
	{
		int temp = 0;
		for (int used : usedEdge)
		{
			temp += used;
		}
		if (temp == mapData.edgeNumber)
			return tempMinLength[mapData.end];
		if (i == mapData.edgeNumber && cnt == 0)
			return -1;
		if (i == mapData.edgeNumber && cnt != 0)
		{
			i = 0;
			cnt = 0;
		}
		if (usedEdge[i] == 1)
			continue;
		if (tempMinLength[edgeData[i].start] != 2147483647)
		{
			if (tempMinLength[edgeData[i].start] + edgeData[i].length < tempMinLength[edgeData[i].end])
			{
				tempMinLength[edgeData[i].end] = tempMinLength[edgeData[i].start] + edgeData[i].length;
			}
			usedEdge[i] = 1;
			cnt++;
		}
	}
}

int main()
{
	int group;
	cin >> group;
	vector<Map> mapData(group);
	vector<vector<Edge>> edgeData;
	int temp;
	for (int i = 0; i < group; i++)
	{
		cin >> mapData[i].vertexNumber >> mapData[i].edgeNumber >> mapData[i].start >> mapData[i].end;
		vector<Edge> tempEdge(mapData[i].edgeNumber);
		for (int j = 0; j < mapData[i].edgeNumber; j++)
		{
			cin >> tempEdge[j].start >> tempEdge[j].end >> tempEdge[j].length;
		}
		edgeData.push_back(tempEdge);
	}
	for (int i = 0; i < group; i++)
	{
		cout << minLength(mapData[i], edgeData[i]) << endl;
	}
}