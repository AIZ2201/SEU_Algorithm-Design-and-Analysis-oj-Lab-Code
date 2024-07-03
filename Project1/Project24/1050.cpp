#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <climits>
using namespace std;

//��ͨ��

//��������
struct R
{
	int orderid;
	int get;
	int put;
	int earliest;
	int latest;
	int cost;//����������Ŀ���
	vector<int>path;//��������������·��
	vector<int>bypath;//�������������·��
	bool patched = 0;
};

struct ans
{
	int v;
	int time;
};

int shortest(vector<vector<int>>& E, int n, int a, int b, vector<int>& path) {
	vector<int> visited(n + 1, 0);
	vector<int> d(n + 1, INT_MAX);
	vector<int> tempd(n + 1, INT_MAX);
	vector<int> p(n + 1, -1);

	// ��ʼ��
	visited[a] = 1;
	d[a] = 0;
	tempd = E[a];
	for (int i = 1; i < n; i++)
	{
		if (E[a][i] != INT_MAX)
			p[i] = a;
	}

	for (int times = 1; times <= n; times++) {
		if (visited[b] == 1)
			break;

		int mind = INT_MAX;
		int next = -1;
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 1)
				continue;
			if (tempd[i] < mind) {
				mind = tempd[i];
				next = i;
			}
		}

		if (next == -1) { // ���û���ҵ��ɷ��ʵĽڵ㣬˵��û��·��
			return -1;
		}

		visited[next] = 1;
		d[next] = mind;


		// ���� tempd
		for (int j = 1; j <= n; j++) {
			if (visited[j] == 1)
				continue;
			if (E[next][j] != INT_MAX && d[next] + E[next][j] < tempd[j])
			{
				tempd[j] = d[next] + E[next][j];
				p[j] = next;
			}
		}
	}

	if (visited[b]) {
		vector<int> temppath;
		for (int v = b; v != -1; v = p[v]) {
			temppath.push_back(v);
		}
		reverse(temppath.begin(), temppath.end());
		path = temppath;

		return d[b]; // �������·������
	}
	else {
		return -1; // ���������·��
	}
}

bool compare(const R& a, const R& b) {
	if (a.latest != b.latest) {
		return a.latest < b.latest;
	}
	return a.cost < b.cost;
}

void patch(vector<vector<int>>& E, vector<vector<R>>& workpath, int n, vector<R>order, int x)
{
	//���������ʱ������
	sort(order.begin(), order.end(), compare);

	int m = order.size();
	//һ��һ��
	for (int j = 1; j <= x; j++)
	{
		int curtime = 0;
		int curtV;
		for (int i = 0; i < m; i++)
		{
			if (order[i].patched || order[i].latest > 144)
				continue;

			if (workpath[j].empty())
			{
				workpath[j].push_back(order[i]);
				curtime = max(order[i].cost, order[i].earliest);
				curtV = order[i].put;
				order[i].patched = 1;
			}
			else
			{
				//vector<int> tempa;
				int pathtime = shortest(E, n, curtV, order[i].get, order[i].bypath);
				int nexttime = curtime + pathtime + order[i].cost;

				if (nexttime <= order[i].latest && nexttime < 144)
				{
					workpath[j].push_back(order[i]);
					curtime = max(nexttime, order[i].earliest);
					curtV = order[i].put;
					order[i].patched = 1;
				}
				else
					continue;
			}


		}

	}


}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int time;
	cin >> time;

	vector<vector<vector<R>>>ans(time);
	for (int i = 0; i < time; i++) {

		int n, e, r, x;
		cin >> n >> e >> r >> x;
		vector<int> V(n + 1);
		vector<vector<int>> E(n + 1, vector<int>(n + 1, INT_MAX));
		vector<R>order(r);
		vector<vector<R>> workpath(x + 1);

		for (int j = 0; j < e; j++) {
			int s, en, w;
			cin >> s >> en >> w;
			E[s][en] = E[en][s] = w;
		}

		for (int i = 0; i < r; i++)
		{
			order[i].orderid = i + 1;
			cin >> order[i].get >> order[i].put >> order[i].earliest >> order[i].latest;
			order[i].cost = shortest(E, n, order[i].get, order[i].put, order[i].path);
		}

		patch(E, workpath, n, order, x);
		ans[i] = workpath;
	}

	for (int i = 0; i < time; i++)
	{
		for (int j = 1; j < ans[i].size(); j++)
		{
			if (!ans[i][j].empty())
			{
				cout << "solution " << j << endl;
				cout << "pick " << ans[i][j][0].orderid << endl;
				cout << "goto " << ans[i][j][0].path.size() << " ";
				for (int m = 0; m < ans[i][j][0].path.size(); m++)
					cout << ans[i][j][0].path[m] << " ";
				cout << endl;
				cout << "serve " << ans[i][j][0].orderid << " ";
				cout << endl;

				for (int k = 1; k < ans[i][j].size(); k++)
				{
					//���������·��
					cout << "goto " << ans[i][j][k].bypath.size() << " ";
					for (int m = 0; m < ans[i][j][k].bypath.size(); m++)
						cout << ans[i][j][k].bypath[m] << " ";
					cout << endl;

					cout << "pick " << ans[i][j][k].orderid << endl;
					cout << "goto " << ans[i][j][k].path.size() << " ";
					for (int m = 0; m < ans[i][j][k].path.size(); m++)
						cout << ans[i][j][k].path[m] << " ";
					cout << endl;
					cout << "serve " << ans[i][j][k].orderid << " ";
					cout << endl;
				}

			}

		}
		cout << endl;
	}


	return 0;
}
