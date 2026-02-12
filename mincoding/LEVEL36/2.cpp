#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;

int n, m, k;

struct Edge {
    int now_node;
    int cost;

    bool operator<(Edge right) const {
        if (cost < right.cost) return false;
        if (cost > right.cost) return true;
        
        if (now_node < right.now_node) return false;
        if (now_node > right.now_node) return true;

        return false;
    }
};

void dijkstra(int start) {
    priority_queue<Edge> pq;
    pq.push({start, 0});

    dist.assign(n, INT_MAX);
    dist[start] = 0;

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int now = cur.now_node;
        int cost = cur.cost;

        if (dist[now] < cost) continue;

        for (int i = 0; i < graph[now].size(); i++) {
            auto nxt = graph[now][i];
            int nxt_node = nxt.first;
            int nxt_cost = nxt.second;

            if (dist[now] + nxt_cost < dist[nxt_node]) {
                dist[nxt_node] = dist[now] + nxt_cost;
                pq.push({nxt_node, dist[nxt_node]});
            }
        }
    }
}

int main() {
    cin >> n >> m >> k;

    int start, end;
    cin >> start >> end;

    start--;
    end--;

    graph.assign(n, {});

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        u--;
        v--;    

        graph[u].push_back({v, c});
        graph[v].push_back({u, c});
    }

    vector<int> K;
    K.push_back(0);

    for (int i = 0; i < k; i++) {
        int p;
        cin >> p;
        K.push_back(p);
    }

    for (int k_idx = 0; k_idx < K.size(); k_idx++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                graph[i][j].second += K[k_idx];
            }
        }

        dijkstra(start);

        cout << dist[end] << "\n";
    }
}