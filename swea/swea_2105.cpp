#include <iostream>
#include <queue>
#include <map>

using namespace std;

vector<vector<int>> board;

int n;
int si, sj;
int answer;
int dat[101];

int di[] = {-1, -1, 1, 1};
int dj[] = {1, -1, -1, 1};


void backtrack(int i, int j, int dir_idx, int depth, int dir_cnt) {
	if (dir_cnt > 3) return;
	
	if (depth !=0 && i == si && j == sj) {
		answer = max(answer, depth);
		return;
	}

	if (dat[board[i][j]]) return;
	dat[board[i][j]] = 1;

	// 직진
	int ni = i + di[dir_idx];
	int nj = j + dj[dir_idx];
	if (ni >= 0 && ni < n && nj >= 0 && nj < n) backtrack(ni, nj, dir_idx, depth + 1, dir_cnt);

	// 회전
	int n_dir_idx = (dir_idx + 1) % 4;
	int ni2 = i + di[n_dir_idx];
	int nj2 = j + dj[n_dir_idx];
	if (ni2 >= 0 && ni2 < n && nj2 >= 0 && nj2 < n) backtrack(ni2, nj2, n_dir_idx, depth + 1, dir_cnt + 1);

	dat[board[i][j]] = 0;
}

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> n;

		board.assign(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> board[i][j];
		}
		
		answer = -1;
		for (int i = 0; i < 101; i++) dat[i] = 0;

		for (int i = 0; i < n - 1; i++) {
			for (int j = 1; j < n - 1; j++) {
				si = i;
				sj = j;
				for (int k = 0; k < 4; k++) {
					backtrack(i, j, k, 0, 0);
				}
			}
		}

		cout << '#' << t + 1 << ' ' << answer << "\n";
	}
}
