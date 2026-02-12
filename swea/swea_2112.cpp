#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> board;

int r, c, K;
int answer;

bool check() {
    for (int j = 0; j < c; j++) {
        int cnt = 1;
        int max_cnt = 1;
        for (int i = 1; i < r; i++) {
            if (board[i - 1][j] == board[i][j]) {
                cnt++;
                max_cnt = max(max_cnt, cnt);
            }
            else cnt = 1;

            if (max_cnt >= K) break;
        }        
        if (max_cnt < K) return false;
    }
    return true;
}

void fill(int row, int color) {
    for (int j = 0; j < c; j++) board[row][j] = color;
}

void backtrack(int row, int cnt) {
    if (cnt >= answer || cnt >= c || row > r) {
        return;
    }
    
    if (check()) {
        answer = cnt;
        return;
    }
    
    // A 채우기
    vector<int> backup = board[row];
    fill(row, 0);
    backtrack(row + 1, cnt + 1);
    board[row] = backup;

    // B 채우기
    fill(row, 1);
    backtrack(row + 1, cnt + 1);
    board[row] = backup;

    // 안 채우기
    backtrack(row + 1, cnt);
}

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        cin >> r >> c >> K;

        answer = c;
        
        board.assign(r, vector<int>(c));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> board[i][j];
            }
        }

        if (K == 1) answer = 0;
        else backtrack(0, 0);

        cout << '#' << t + 1 << ' ' << answer << "\n";
    }

    return 0;
}