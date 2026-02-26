#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n;
char board[300][300];
int visited[300][300];
int boom_board[300][300];
int answer;

// 상하좌우 + 대각선
int di[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dj[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

struct Coord {
	int i;
	int j;
	int cnt; // 주위 8방향 폭탄 개수

	bool operator< (Coord right) const {
		if (cnt < right.cnt) return false;
		if (cnt > right.cnt) return true;
		return false;
	}
};

int check_boom(int ci, int cj) {
	int cnt = 0;
	for (int k = 0; k < 8; k++) {
		int ni = ci + di[k];
		int nj = cj + dj[k];

		if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
			if (board[ni][nj] == '*') cnt++;
		}
	}
	return cnt;
}

void simulation() {
	priority_queue<Coord> pq;
	memset(boom_board, -1, sizeof(boom_board));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == '.') {
				int cnt = check_boom(i, j);
				boom_board[i][j] = cnt;
				pq.push({ i, j, cnt });
			}
		}
	}

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << boom_board[i][j] << ' ';
		cout << endl;
	}*/

	// 방문 배열 초기화
	memset(visited, -1, sizeof(visited));

	answer = 0;

	while (!pq.empty()) {
		auto cur = pq.top(); pq.pop();
		int now_i = cur.i;
		int now_j = cur.j;

		if (visited[now_i][now_j] != -1) continue;

		answer++;

		// 클릭하면 주위 8개 계속 확인해서 boom_board[i][j]가 0이면 q에 넣고 아니면 숫자 표시만
		queue<pair<int, int>> q;
		q.push({ now_i, now_j });

		visited[now_i][now_j] = boom_board[now_i][now_j];

		if (visited[now_i][now_j] != 0) continue;

		//cout << now_i << ' ' << now_j << endl;

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			int ci = cur.first;
			int cj = cur.second;

			for (int k = 0; k < 8; k++) {
				int ni = ci + di[k];
				int nj = cj + dj[k];

				if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
					if (board[ni][nj] == '.' && visited[ni][nj] == -1) {
						//cout << ni << ' ' << nj << endl;
						visited[ni][nj] = boom_board[ni][nj];
						if (boom_board[ni][nj] == 0) q.push({ ni, nj });
					}
				}
			}
		}

		//cout << endl;

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << visited[i][j] << ' ';
			cout << endl;
		}*/
	}
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t < T + 1; t++) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;

			for (int j = 0; j < str.length(); j++) {
				board[i][j] = str[j];
			}
		}

		simulation();

		cout << '#' << t << ' ' << answer << '\n';
	}

	return 0;
}