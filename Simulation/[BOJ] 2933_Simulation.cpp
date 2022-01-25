// reference : https://rile1036.tistory.com/133

#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>

using namespace std;

#define MAX 101

int R, C, N;
vector <int> stick;
vector <pair <int, int>> cluster;
char arr[MAX][MAX];
bool visit[MAX][MAX];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void clust_Down() {
	bool cluster_visit[MAX][MAX];
	memset(cluster_visit, false, sizeof(cluster_visit));

	for (int i = 0; i < cluster.size(); i++) {
		int x = cluster[i].first;
		int y = cluster[i].second;
		if (x == R - 1) 
			return;
		else {
			arr[x][y] = '.';
			visit[x][y] = false;
		}
	}

	for (int i = 0; i < cluster.size(); i++) {
		int x = cluster[i].first;
		int y = cluster[i].second;

		arr[x + 1][y] = 'x';
		visit[x + 1][y] = true;
		cluster_visit[x + 1][y] = true;
		cluster[i].first += 1;
	}

	for (int i = 0; i < cluster.size(); i++) {
		int x = cluster[i].first;
		int y = cluster[i].second;

		if (x == R - 1)
			return;
		if (arr[x + 1][y] == 'x' && !cluster_visit[x + 1][y])
			return;
	}
	clust_Down();
	return;
}

void DFS(int x, int y) {
	cluster.push_back(make_pair(x, y));
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
		if (arr[nx][ny] == 'x' && !visit[nx][ny]) {
			visit[nx][ny] = true;
			DFS(nx, ny);
		}
	}
}

void clust() {
	for (int i = R - 1; i >= 0; i--) {
		for (int j = 0; j < C; j++) {
			if (arr[i][j] == 'x' && !visit[i][j]) {
				cluster.clear();
				visit[i][j] = true;
				DFS(i, j);
				clust_Down();
			}
		}
	}
}

void Throw(int height, bool flag) {
	height = R - height;

	if (flag) { // 왼
		for (int i = 0; i < C; i++) {
			if (arr[height][i] == 'x') {
				arr[height][i] = '.';
				break;
			}
		}
	}
	if (!flag) { // 오
		for (int i = C - 1; i >= 0; i--) {
			if (arr[height][i] == 'x') {
				arr[height][i] = '.';
				break;
			}
		}
	}
	return;
}

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
}

int main() {
	init();
	cin >> R >> C;
	
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			cin >> arr[i][j];

	cin >> N;
	for (int i = 0; i < N; i++) {
		int stick_num; cin >> stick_num;
		stick.push_back(stick_num);
	}
	for (int i = 0; i < stick.size(); i++) {
		memset(visit, false, sizeof(visit));
		if (i % 2 == 0)
			Throw(stick[i], true);
		else
			Throw(stick[i], false);
		clust();
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	return 0;
}
