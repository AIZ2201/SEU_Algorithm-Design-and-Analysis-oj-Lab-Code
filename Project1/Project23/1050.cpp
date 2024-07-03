#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Edge
{
public:
	int start;
	int end;
	int passTime;
};

class Request
{
public:
	int number;
	int pick;
	int serve;
	int earlyTime;
	int lateTime;
};

bool compareEdge(Edge& a, Edge& b)
{
	return a.start < b.start;
}

bool compareRequest(Request& a, Request& b)
{
	return a.earlyTime < b.earlyTime;
}

void floydWarshall(int V, vector<vector<int>>& graph, vector<vector<int>>& dist, vector<vector<vector<int>>>& paths) {
	// Initialize distance and path matrices
	dist = vector<vector<int>>(V, vector<int>(V, 2147483647));
	paths = vector<vector<vector<int>>>(V, vector<vector<int>>(V));

	// Initialize distances with given graph and set paths for direct edges
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i == j) {
				dist[i][j] = 0;
				paths[i][j] = { i };
			}
			else if (graph[i][j] != -1) {
				dist[i][j] = graph[i][j];
				paths[i][j] = { i, j };
			}
		}
	}

	// Floyd-Warshall algorithm
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				if (dist[i][k] != 2147483647 && dist[k][j] != 2147483647 && dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					paths[i][j] = paths[i][k];
					paths[i][j].pop_back(); // Remove intermediate end before concatenation
					paths[i][j].insert(paths[i][j].end(), paths[k][j].begin(), paths[k][j].end());
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int group;
	cin >> group;
	vector<string> str;
	for (int turn = 0; turn < group; turn++)
	{
		int vertexNum;
		int edgeNum;
		int requestNum;
		int personNum;
		cin >> vertexNum >> edgeNum >> requestNum >> personNum;
		vector<Edge> edgeArray(edgeNum * 2);
		vector<Request> requestArray(requestNum);
		for (int i = 0; i < edgeNum; i++)
		{
			Edge temp;
			cin >> temp.start >> temp.end >> temp.passTime;
			edgeArray[i] = temp;
			int tempInt = temp.start;
			temp.start = temp.end;
			temp.end = tempInt;
			edgeArray[edgeNum + i] = temp;
		}
		vector<vector<int>> graph(vertexNum, vector<int>(vertexNum, -1));
		for (auto &tempE : edgeArray)
		{
			graph[tempE.start - 1][tempE.end - 1] = tempE.passTime;
		}
		vector<vector<vector<int>>> paths;
		vector<vector<int>> distances;
		floydWarshall(vertexNum, graph, distances, paths);
		for (int i = 0; i < requestNum; i++)
		{
			cin >> requestArray[i].pick >> requestArray[i].serve >> requestArray[i].earlyTime >> requestArray[i].lateTime;
			requestArray[i].number = i + 1;
		}
		sort(requestArray.begin(), requestArray.end(), compareRequest);

		string tempStr;

		for (int i = 1; i <= personNum; i++)
		{
			int time = 0;
			int tempLocation = 0;
			for (int j = 0; j < requestNum; j++)
			{
				if (requestArray[j].number == 0)
					continue;
				if (time + distances[requestArray[j].pick - 1][requestArray[j].serve - 1] <= requestArray[j].lateTime)
				{
					time = time + distances[requestArray[j].pick - 1][requestArray[j].serve - 1] > requestArray[j].earlyTime ? time + distances[requestArray[j].pick - 1][requestArray[j].serve - 1] : requestArray[j].earlyTime;
					/*cout << "solution " << i << '\n';*/
					tempStr += "solution ";
					tempStr += to_string(i);
					tempStr += '\n';
					/*cout << "pick " << requestArray[j].number << '\n';*/
					tempStr += "pick ";
					tempStr += to_string(requestArray[j].number);
					tempStr += '\n';
					/*cout << "goto " << requestArray[j].vertexNum << ' ';*/
					tempStr += "goto ";
					tempStr += to_string(paths[requestArray[j].pick - 1][requestArray[j].serve - 1].size());
					tempStr += ' ';
					for (int path : paths[requestArray[j].pick - 1][requestArray[j].serve - 1])
					{
						/*cout << path << ' ';*/
						tempStr += to_string(path + 1);
						tempStr += ' ';
					}
					/*cout << '\n' << "serve " << requestArray[j].number << '\n';*/
					tempStr += '\n';
					tempStr += "serve ";
					tempStr += to_string(requestArray[j].number);
					tempStr += '\n';
					requestArray[j].number = 0;
					tempLocation = requestArray[j].serve - 1;
					break;
				}
			}
			for (int m = 0; m < requestNum; m++)
			{
				int min = 2147483647;
				int minJ = -1;
				for (int j = 0; j < requestNum; j++)
				{
					if (requestArray[j].number == 0)
						continue;
					if (time + distances[tempLocation][requestArray[j].pick - 1] + distances[requestArray[j].pick - 1][requestArray[j].serve - 1] <= requestArray[j].lateTime)
					{
						int tempMin = requestArray[j].earlyTime > time + distances[tempLocation][requestArray[j].pick - 1] + distances[requestArray[j].pick - 1][requestArray[j].serve - 1] ?
							requestArray[j].earlyTime : time + distances[tempLocation][requestArray[j].pick - 1] + distances[requestArray[j].pick - 1][requestArray[j].serve - 1];
						if (tempMin < min)
						{
							min = tempMin;
							minJ = j;
						}
					}
				}
				if (minJ != -1)
				{
					time = min;
					/*cout << "goto " << requestArray[j].vertexNum << ' ';*/
					tempStr += "goto ";
					tempStr += to_string(paths[tempLocation][requestArray[minJ].pick - 1].size());
					tempStr += ' ';
					for (int path : paths[tempLocation][requestArray[minJ].pick - 1])
					{
						/*cout << path << ' ';*/
						tempStr += to_string(path + 1);
						tempStr += ' ';
					}
					tempStr += '\n';
					/*cout << "pick " << requestArray[j].number << '\n';*/
					tempStr += "pick ";
					tempStr += to_string(requestArray[minJ].number);
					tempStr += '\n';
					/*cout << "goto " << requestArray[j].vertexNum << ' ';*/
					tempStr += "goto ";
					tempStr += to_string(paths[requestArray[minJ].pick - 1][requestArray[minJ].serve - 1].size());
					tempStr += ' ';
					for (int path : paths[requestArray[minJ].pick - 1][requestArray[minJ].serve - 1])
					{
						/*cout << path << ' ';*/
						tempStr += to_string(path + 1);
						tempStr += ' ';
					}
					/*cout << '\n' << "serve " << requestArray[j].number << '\n';*/
					tempStr += '\n';
					tempStr += "serve ";
					tempStr += to_string(requestArray[minJ].number);
					tempStr += '\n';
					requestArray[minJ].number = 0;
					tempLocation = requestArray[minJ].serve - 1;
				}
				else
					break;
			}
		}
		str.push_back(tempStr);
	}
	for (int i = 0; i < group; i++)
	{
		cout << str[i] << '\n';
	}
}