#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;

int C, P, K, A, B;

struct Edge {
    int node;
    int cost;

    bool operator<(Edge right) const {
        if (cost < right.cost) return false;
        if (cost > right.cost) return true;

        if (node < right.node) return false;
        if (node > right.node) return true;

        return false;
    }
};

void dijkstra(int start) {
    priority_queue<Edge> pq;
    pq.push({start, 0});

    dist.assign(P + 1, INT_MAX);
    dist[start] = 0;

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int cur_node = cur.node;
        int cur_dist = cur.cost;

        if (dist[cur_node] < cur_dist) continue;

        for (int i = 0; i < graph[cur_node].size(); i++) {
            auto nxt = graph[cur_node][i];
            int nxt_node = nxt.first;
            int nxt_cost = nxt.second;

            if (dist[cur_node] + nxt_cost < dist[nxt_node]) {
                dist[nxt_node] = dist[cur_node] + nxt_cost;
                pq.push({nxt_node, dist[nxt_node]});
            }
        }
    }
}

int main() {
    cin >> C >> P >> K >> A >> B;
    
    graph.assign(P + 1, {});

    for (int i = 0; i < C; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        graph[u].push_back({v, c});
        graph[v].push_back({u, c});
    }

    int tmp1 = 0;
    int tmp2 = 0;
    dijkstra(K);
    tmp1 += dist[A];
    tmp2 += dist[B];

    dijkstra(A);
    tmp1 += dist[B];
    dijkstra(B);
    tmp2 += dist[A];

    int answer = min(tmp1, tmp2);

    cout << answer;

    return 0;
}