#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;


typedef long long i64;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int grams_total;
int N;
constexpr int MAXN = 100000;
vector<int> conns[MAXN];
int grams[MAXN];

i64 greedy_dfs(int node, int parent, i64* total_cuts)
{
    i64 sum = grams[node];

    vector<i64> grams_of_children;
    for (int child : conns[node])
    {
        if (child == parent) continue;
        grams_of_children.push_back(greedy_dfs(child, node, total_cuts));
    }

    sort(grams_of_children.begin(), grams_of_children.end());

    for (int i = 0; i < grams_of_children.size(); i++)
    {
        if (sum + grams_of_children[i] > grams_total)
        {
            *total_cuts += grams_of_children.size() - i;
            break;
        }
        sum += grams_of_children[i];
    }

    return sum;
}

int main()
{
    scanf("%d%d", &N, &grams_total);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &grams[i]);
    }
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        conns[a].push_back(b);
        conns[b].push_back(a);
    }

    i64 result = 0;
    greedy_dfs(0, -1, &result);

    printf("%lld", result);

    return 0;
}
