#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TreeData
{
public:
	int vertexNumber, edgeNumber;
};

class Edge
{
public:
	int start, end, Weight;
};

bool compare(Edge& A, Edge& B)
{
	return A.Weight < B.Weight;
}

class UnionFind
{
public:
    vector<int> parent, rank;

    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x) 
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) 
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) 
        {
            if (rank[rootX] < rank[rootY]) 
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else 
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y) 
    {
        return find(x) == find(y);
    }
};

int minWeight(TreeData treeData, vector<Edge> edgeData)
{
	sort(edgeData.begin(), edgeData.end(), compare);
    UnionFind vertex(treeData.vertexNumber);//注意UF中下标0对应edge中1
    int Weight = 0;
    for (auto& tempEdge : edgeData)
    {
        if (vertex.connected(tempEdge.start - 1, tempEdge.end - 1))
        {
            continue;
        }
        else
        {
            vertex.unite(tempEdge.start - 1, tempEdge.end - 1);
            Weight += tempEdge.Weight;
        }
    }
    int standard = vertex.parent[0];
    for (int i = 0; i < treeData.vertexNumber; i++)
    {
        if (vertex.parent[i] != standard)
            return -1;
    }
    return Weight;
}

int main()
{
	int group;
	cin >> group;
	vector<TreeData> treeData(group);
	vector<vector<Edge>> edgeData;
	for (int i = 0; i < group; i++)
	{
		cin >> treeData[i].vertexNumber >> treeData[i].edgeNumber;
		vector<Edge> tempEdge(treeData[i].edgeNumber);
		for (int j = 0; j < treeData[i].edgeNumber; j++)
		{
			cin >> tempEdge[j].start >> tempEdge[j].end >> tempEdge[j].Weight;
		}
		edgeData.push_back(tempEdge);
	}
    for (int i = 0; i < group; i++)
    {
        cout << minWeight(treeData[i], edgeData[i]) << endl;
    }
}