#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int answer;
int N;
int MAP[11][11];

struct Coord {
    int row;
    int col;
};

int calcDist(Coord left, Coord right) {
    return abs(left.row - right.row) + abs(left.col - right.col);
}

struct Element {
    Coord person;
    Coord stair;

    bool operator<(Element right) const {
        int ldist = calcDist(person, stair);
        int rdist = calcDist(right.person, right.stair);

        if (ldist < rdist) return false;
        if (ldist > rdist) return true;

        return false;
    }
};

vector<Coord> persons;
vector<Coord> stairs;
vector<int> path; // idx: now 번째 사람이 value: 선택한 계단

void init() {
    persons.clear();
    stairs.clear();
    memset(MAP, 0, sizeof(MAP));
    answer = INT_MAX;
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1) persons.push_back({i, j});
            if (MAP[i][j] == 2) stairs.push_back({i, j});
        }
    }
}

int simulation() {
    priority_queue<Element> pq[2];

    for (int i = 0; i < path.size(); i++) {
        pq[path[i]].push({persons[i], stairs[path[i]]});
    }

    queue<int> useList;

    for (int stairNum = 0; stairNum < 2; stairNum++) {
        while (!pq[stairNum].empty()) {
            Element now = pq[stairNum].top(); pq[stairNum].pop();

            // 계단까지 도착시간
            int arriveTime = calcDist(now.person, now.stair) + 1;

            // 계단 내려가는 시간
            int stairTime = MAP[now.stair.row][now.stair.col];

            // 대기열 관리
            if (useList.size() < 3) {
                useList.push(arriveTime + stairTime);
            }
            else {
                int prevTime = useList.front(); useList.pop();
                if (arriveTime < prevTime) {
                    useList.push(prevTime + stairTime);
                }
                else {
                    useList.push(arriveTime + stairTime);
                }
            }
        }
    }
}

void dfs(int now) {
    if (now >= persons.size()) {
        answer = min(answer, simulation());
        return;
    }

    for (int i = 0; i < 2; i++) {
        path.push_back(i);
        dfs(now + 1);
        path.pop_back();
    }
}

void solution() {
    dfs(0);
}

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        init();
        input();
        solution();
        cout << "#" << t + 1 << ' ' << answer << "\n";
    }
}