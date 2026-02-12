#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;

struct Edge{
    int v;
    int dist;

    bool operator<(Edge right) const {
        // dist 작은 순
        if (dist < right.dist) return false;
        if (dist > right.dist) return true;
        
        // 노드 번호 작은 순
        if (v < right.v) return false;
        if (v > right.v) return true;

        return false;
    }
};

void dijkstra(int start) {
    priority_queue<Edge> pq; // 노드 번호, 노드까지의 dist

    dist[start] = 0;
    pq.push({start, 0});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int cur_node = cur.v;
        int cur_dist = cur.dist;

        if (dist[cur_node] < cur_dist) continue;

        for (int i = 0; i < graph[cur_node].size(); i++) {
            auto nxt = graph[cur_node][i];
            int nxt_node = nxt.first;
            int cost = nxt.second;

            if (dist[cur_node] + cost < dist[nxt_node]) {
                dist[nxt_node] = dist[cur_node] + cost;
                pq.push({nxt_node, dist[nxt_node]});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.assign(n, {});
    dist.assign(n, INT_MAX);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        graph[u].push_back({v, c});
    }

    dijkstra(0);

    if (dist[n - 1] != INT_MAX) cout << dist[n - 1];
    else cout << "impossible";
}