#include <stdio.h>
#include <string.h>
#include <vector>

inline int min(int a, int b) { return a < b ? a : b; }

constexpr int MAXN = 100000;
int N_nodes, N_conns;

std::vector<int> conns[MAXN];

int articulated = 0;
int depth[MAXN];
int min_reachable[MAXN];
int previous[MAXN];

inline void articulate(int node)
{
    articulated++;
    //printf("baddie: %d\n", node);
}

void dfs(int current, int current_depth)
{
    depth[current] = current_depth;
    min_reachable[current] = depth[current];

    bool art = false;
    int unvisited_neighbors = 0;
    for (int neighbor : conns[current])
    {
        if (depth[neighbor] == -1)
        {
            unvisited_neighbors++;

            previous[neighbor] = current;
            dfs(neighbor, current_depth + 1);

            min_reachable[current] = min(min_reachable[current], min_reachable[neighbor]);

            if (previous[current] != -1 && min_reachable[neighbor] >= depth[current])
                art = true;
        }
        else if (neighbor != previous[current])
        {
            min_reachable[current] = min(min_reachable[current], depth[neighbor]);
        }
    }

    if (art) articulate(current);

    if (previous[current] == -1 && unvisited_neighbors > 1)
        articulate(current);
}

int main()
{
    memset(previous, 0xFF, sizeof(previous));
    memset(depth, 0xFF, sizeof(depth));
    memset(min_reachable, 0xFF, sizeof(min_reachable));

    scanf("%d%d", &N_nodes, &N_conns);

    for (int i = 0; i < N_conns; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        conns[a].push_back(b);
        conns[b].push_back(a);
    }

    for (int i = 0; i < N_nodes; i++)
        if (depth[i] == -1)
            dfs(i, 0);

    printf("%d", articulated);

    return 0;
}
