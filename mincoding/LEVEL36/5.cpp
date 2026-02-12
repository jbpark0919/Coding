#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

vector<vector<int>> board;
vector<vector<int>> dist;

int n;

struct Edge {
    int i;
    int j;
    int cost;

    bool operator<(Edge right) const {
        if (cost < right.cost) return false;
        if (cost > right.cost) return true;

        if (i < right.i) return false;
        if (i > right.i) return true;

        if (j < right.j) return false;
        if (j > right.j) return true;

        return false;
    }
};

void dijkstra(int i, int j) {
    priority_queue<Edge> pq; // 현재 노드, 현재 위치까지의 거리
    pq.push({i, j, 0});

    dist.assign(n, vector<int>(n, INT_MAX));
    dist[i][j] = 0;

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int ci = cur.i;
        int cj = cur.j;
        int cur_dist = cur.cost;

        for (int k = 0; k < 4; k++) {
            int ni = ci + di[k];
            int nj = cj + dj[k];

            if ((ni >= 0 && ni < n && nj >= 0 && nj < n) && (board[ni][nj] != -1)) {
                if (cur_dist + board[ni][nj] < dist[ni][nj]) {
                    dist[ni][nj] = cur_dist + board[ni][nj];
                    pq.push({ni, nj, dist[ni][nj]});
                }
            }
            
        }
    }
}

int main() {
    int r, c;
    cin >> r >> c;

    cin >> n;

    board.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    dijkstra(r, c);

    int answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != INT_MAX)
                answer = max(answer, dist[i][j]);
        }
    }

    cout << answer + board[r][c];

    return 0;
}