#include <iostream>
#include <stdio.h>

#define N 5000

using namespace std;

int lines, num_assets, own_fire_power, adj_asset, any_enemy, best_local_power, best_index, visited, passed_target = 0;
int own_fire_power_arr[N], local_power[N], dist[N], queue[N], marked[N];
int mat_adj[N][N];

int smallest_dist() {
    int index = -1, aux = N;
    for (int i = 0; i < lines; i++) {
        if (queue[i] == 0 && dist[i] < aux) {
            index = i;
            aux = dist[i];
        }
    }
    return index;
}

int main() {
    while(scanf("%d", &lines) > 0 && !feof(stdin)) {
        any_enemy = 0;
        best_local_power = 0;
        for (int i = 0; i < lines; i++) {
            scanf("%d %d", &own_fire_power, &num_assets);
            if (any_enemy == 0 && own_fire_power < 0) {
                any_enemy = 1;
            }
            own_fire_power_arr[i] = own_fire_power;
            for (int j = 0; j < num_assets; j++) {
                scanf("%d", &adj_asset);
                mat_adj[i][adj_asset - 1] = 1;
            }
        }

        if (any_enemy == 1) {
            for (int i = 0; i < lines; i++) {
                if (own_fire_power_arr[i] < 0) {
                    local_power[i] += (own_fire_power_arr[i]);
                    for (int j = 0; j < lines; j++) {
                        if (j != i && mat_adj[i][j] == 1) {
                            local_power[i] += (own_fire_power_arr[j]);
                        }
                    }
                }
            }
            while (passed_target == 0) {
                best_local_power = 0;
                best_index = 0;
                visited = 0;
                dist[0] = 0;
                queue[0] = 0;
                for (int i = 1; i < lines; i++) {
                    dist[i] = N;
                    queue[i] = 0;
                    if (marked[i] == 0 && local_power[i] < best_local_power) {
                        best_local_power = local_power[i];
                        best_index = i;
                    }
                }
                marked[best_index] = 1;
                int u = 0;
                while(visited < lines && u != -1) {
                    u = smallest_dist();
                    if (u != -1) {
                        queue[u] = 1;
                        visited++;
                        if (u == best_index) {
                            passed_target = 1;
                            break;
                        }
                        for (int i = 0; i < lines; i++) {
                            if (i != u && queue[i] == 0) {
                                if (mat_adj[u][i] == 1) {
                                    if (dist[i] > dist[u] + 1) {
                                        dist[i] = dist[u] + 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (dist[best_index] == 0) {
                printf("No threats!\n");
            } else {
                printf("%d\n", dist[best_index]);
            }

        } else {
            printf("No threats!\n");
        }

        for (int k = 0; k < N; k++) {
            queue[k] = 0;
            marked[k] = 0;
            local_power[k] = 0;
            dist[k] = 0;
            own_fire_power_arr[k] = 0;
            for (int i = 0; i < N; i++) {
                mat_adj[k][i] = 0;
            }
        }
    }

    return 0;
}