#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;

int n, m, p;

struct Edge{
    int now;
    int cost;
    
    bool operator<(Edge right) const {
        if (now < right.now) return false;
        if (now > right.now) return true;

        if (cost < right.cost) return false;
        if (cost > right.cost) return true;

        return false;
    }
};


void dijkstra(int start) {
    priority_queue<Edge> pq;
    pq.push({start, 0});
    
    dist.assign(n + 1, INT_MAX);
    dist[start] = 0;

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int now_node = cur.now;
        int now_dist = cur.cost;

        if (dist[now_node] < now_dist) continue;

        for (int i = 0; i < graph[now_node].size(); i++) {
            auto nxt = graph[now_node][i];
            int nxt_node = nxt.first;
            int nxt_cost = nxt.second;

            if (dist[now_node] + nxt_cost < dist[nxt_node]) {
                dist[nxt_node] = dist[now_node] + nxt_cost;
                pq.push({nxt_node, dist[nxt_node]});
            }
        }
    }
}

int main() {
    cin >> n >> m >> p;

    graph.assign(n + 1, {});

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        
        graph[u].push_back({v, c});
    }

    vector<int> answer;
    answer.assign(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        dijkstra(i);
            
        answer[i] += dist[p];
    }

    dijkstra(p);
    for (int i = 1; i < n + 1; i++) {
        answer[i] += dist[i];
    }

    int result = 0;
    for (int i = 1; i < n + 1; i++) result = max(result, answer[i]);

    cout << result;

    return 0;
}