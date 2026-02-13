#include <iostream>
#include <queue>

using namespace std;

int map[5][5];
int visited[5][5];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

void bfs(int r, int c) {
    queue<pair<int, int>> q;
    q.push({r, c});

    visited[r][c] = 1;

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int ci = cur.first;
        int cj = cur.second;

        for (int k = 0; k < 4; k++) {
            int ni = ci + di[k];
            int nj = cj + dj[k];

            if (ni >= 0 && ni < 5 && nj >= 0 && nj < 5) {
                if (visited[ni][nj] == 0) {
                    visited[ni][nj] = visited[ci][cj] + 1;
                    q.push({ni, nj});
                }
            } 
        }
    }
}

int main() {
    int r, c;

    bfs(r, c);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << visited[i][j] << ' ';
        cout << "\n";
    }
}