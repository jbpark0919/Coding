#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int n, h, w;
int board[15][12];
int tmp_board[15][12];
int answer;
int path[4];

int di[] = { -1, 1, 0, 0 };
int dj[] = { 0, 0, -1, 1 };

int visited[15][12];

struct Coord {
	int i;
	int j;
};

void check_board() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) cout << tmp_board[i][j] << ' ';
		cout << endl;
	}
}

int count_board() {
	int cnt = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (tmp_board[i][j]) cnt++;
		}
	}

	return cnt;
}

void gravity(int j) {
	int ci = 0;
	int cj = j;
	
	vector<int> balls;
	
	while (ci < h) {
		if (tmp_board[ci][cj]) balls.push_back(tmp_board[ci][cj]);
		tmp_board[ci][cj] = 0;
		ci++;
	}

	int fill_i = h - 1;
	int v_size = balls.size();
	
	for (int idx = v_size - 1; idx >= 0; idx--) {
		tmp_board[fill_i--][cj] = balls[idx];
	}
}

void boom_simulation(int si, int sj) {
	queue<Coord> q;
	q.push({ si, sj });

	memset(visited, 0, sizeof(visited));
	visited[si][sj] = 1;

	/*cout << "before_boom" << endl;
	check_board();*/
	
	// 범위 만큼 다 방문
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		int ci = cur.i;
		int cj = cur.j;
		int R = tmp_board[ci][cj];

		for (int k = 0; k < 4; k++) {
			for (int r = 1; r < R; r++) {
				int ni = ci + di[k] * r;
				int nj = cj + dj[k] * r;

				if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
					if (tmp_board[ni][nj] != 0 && visited[ni][nj] == 0) {
						visited[ni][nj] = 1;
						q.push({ ni, nj });
					}
				}
			}
		}
	}

	// 방문한 곳 다 터뜨리기
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (visited[i][j]) tmp_board[i][j] = 0;
		}
	}

	/*cout << "after_boom" << endl;
	check_board();*/
	
	// 아래로 내리기
	for (int j = 0; j < w; j++) {
		gravity(j);
	}

	/*cout << "after_gravity" << endl;
	check_board();*/
}

void copy_board() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) tmp_board[i][j] = board[i][j];
	}
}

void check() {
	if (answer == 0) return;

	int boom_i;
	int boom_j;

	for (int p = 0; p < n; p++) {
		boom_i = 0;
		boom_j = path[p];

		while (boom_i < h) {
			if (tmp_board[boom_i][boom_j]) break;
			boom_i++;
		}

		/*cout << boom_i << ' ' << boom_j << endl;
		cout << tmp_board[boom_i][boom_j] << endl;*/

		if (boom_i != h) {
			boom_simulation(boom_i, boom_j);
		}
	}

	int remain = count_board();
	//answer = min(answer, remain);
	if (remain < answer) {
		answer = remain;

		/*cout << answer << endl;
		for (int p = 0; p < n; p++) cout << path[p] << ' ';
		cout << endl;
		check_board();
		cout << endl;*/
	}
}

void backtrack(int depth) {
	if (depth == n) {

		copy_board();
		check();
		
		return;
	}

	for (int j = 0; j < w; j++) {
		path[depth] = j;
		backtrack(depth + 1);
	}
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t < T + 1; t++) {
		cin >> n >> w >> h;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) cin >> board[i][j];
		}

		answer = INT_MAX;

		//check_board();

		/*copy_board();
		check();*/

		backtrack(0);

		cout << '#' << t << ' ' << answer << '\n';
	} 

	return 0;
}