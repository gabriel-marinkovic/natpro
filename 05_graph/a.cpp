#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

typedef unsigned char u8;

inline int max(int a, int b) { return a > b ? a : b; }

constexpr int MAXN = 300'000;

u8 is_root[MAXN];
int height[MAXN];
vector<int> children[MAXN];

int connections(int town)
{
    if (height[town])
        return height[town];

    int best = 0;
    for (int child : children[town])
        best = max(best, connections(child));

    height[town] = best + 1;
    return best + 1;
}

int main()
{
    memset(is_root, true, sizeof(is_root));

    int town_count, road_count;
    scanf("%d%d", &town_count, &road_count);

    for (int i = 0; i < road_count; i++)
    {
        int from, to;
        scanf("%d%d", &from, &to);
        from--; to--;

        children[from].push_back(to);
        is_root[to] = false;
    }

    int best = 0;
    for (int town = 0; town < MAXN; town++)
        if (is_root[town])
            best = max(best, connections(town));

    printf("%d", best);

    return 0;
}
