// O algoritmo foi adaptado de:
// http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <cstdio>

using namespace std;

#define N 601
#define M 101

int n, m, num_pos, pos, sum_index;
int graph[N+M+2][N+M+2], rGraph[N+M+2][N+M+2];

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[sum_index];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=1; v<sum_index; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

// Returns tne maximum flow from s to t in the given graph
int ford_fulkerson(int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph with given capacities in the original graph as residual capacities in residual graph
    // Residual graph where rGraph[i][j] indicates residual capacity of edge from i to j (if there is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 1; u < sum_index; u++)
        for (v = 1; v < sum_index; v++)
            rGraph[u][v] = graph[u][v];

    int parent[sum_index];  // This array is filled by BFS and to store path

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while there is path from source to sink
    while (bfs(s, t, parent))
    {
        // Find minimum residual capacity of the edges along the path filled by BFS. Or we can say find the maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

// Driver program to test above functions
int main()
{
    while (scanf("%d %d", &n, &m) > 0) {

        sum_index = n+m+2+1;

        for (int i = 1; i < n+1; i++) {
            scanf("%d", &num_pos);
            for (int j = 0; j < num_pos; j++) {
                scanf("%d", &pos);
                graph[i][n+pos] = 1; // test input: positions 1 and 2 become 7 and 8, respectively (the same for the others)
            }
        }

        for (int k = 1; k < m+1; k++) {
            scanf("%d", &pos);
            graph[n + k][n + m + 1] = pos;
        }

        for (int l = 1; l < n+1; l++) {
            graph[n + m + 2][l] = 1;
        }

        for (int i1 = 1; i1 < n+m+2; i1++) {
            for (int i = 1; i < n+m+2; i++) {
                printf("%d ", graph[i1][i]);
            }
            printf("\n");
        }

        printf("%d\n", ford_fulkerson(sum_index-1, sum_index-2));

        for (int i = 0; i < sum_index; i++) {
            for (int j = 0; j < sum_index; j++) {
                graph[i][j] = 0;
                rGraph[i][j] = 0;
            }
        }
    }

    return 0;
}