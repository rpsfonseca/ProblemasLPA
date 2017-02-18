#include <stdio.h>
#include <algorithm>

#define N 800

using namespace std;

int n, direct, connection_id, load, t, best;
int low[N], dfs[N], parent[N], visited[N];
int matrix_adj[N][N], traffic_load[N][N], adjs_num[N][N];

int adjs(int v) {
    int adj = 0;
    for (int i = 0; i < n; i++) {
        if (matrix_adj[v][i] == 1) {
            adjs_num[v][adj] = i;
            adj++;
        }
    }
    return adj;
}

void worker(int v) {
    int w, num_adjs, sum = 0, articulation_point = 0;
    t += 1;
    low[v] = dfs[v] = t;
    num_adjs = adjs(v);
    for (int i = 0; i < num_adjs; i++) {
        w = adjs_num[v][i];
        sum += traffic_load[v][w];
        if (dfs[w] == -1) {
            parent[w] = v;
            worker(w);
            low[v] = min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2) { articulation_point = 1; }
            if (dfs[v] != 1 && low[w] >= dfs[v]) { articulation_point = 1; }
        } else if (w != parent[v]) { low[v] = min(low[v], dfs[w]); }
    }
    if (articulation_point && (sum > best)) {
        best = sum;
    }
    visited[v] = 1;
}

int main() {
    while (scanf("%d", &n) > 0) {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                matrix_adj[k][i] = 0;
                traffic_load[k][i] = 0;
                adjs_num[k][i] = 0;
            }
            parent[k] = n;
            visited[k] = 0;
            low[k] = n;
            dfs[k] = -1;
        }

        best = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &direct);
            for (int j = 0; j < direct; j++) {
                scanf("%d %d", &connection_id, &load);
                matrix_adj[i][connection_id - 1] = 1;
                traffic_load[i][connection_id - 1] = load;
            }
        }

        for (int l = 0; l < n; l++) {
            if (visited[l] == 0) {
                t = 0;
                worker(l);
            }
        }

        if (best > 0) {
            printf("%d\n", best);
        } else {
            printf("Well designed city!\n");
        }
    }
    return 0;
}




