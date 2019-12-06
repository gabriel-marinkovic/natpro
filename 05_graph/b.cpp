#include <stdio.h>
#include <string.h>
#include <algorithm>

typedef unsigned char u8;

inline int max(int a, int b) { return a > b ? a : b; }

constexpr int MAXN = 100'000;
constexpr int ROADN = 300'000;

int parent[MAXN];

int find(int a)
{
    if (parent[a] == a)
        return a;

    parent[a] = find(parent[a]);
    return parent[a];
}

void unionize(int a, int b)
{
    int pa = find(a);
    int pb = find(b);
    parent[pa] = pb;
}


struct Road
{
    int a, b;
    int thicc;
};

struct Query : Road
{
    int index;
};

Road  roads[ROADN];
Query queries[MAXN];
u8    anwsers[MAXN];

int main()
{
    int town_count, road_count;
    scanf("%d%d", &town_count, &road_count);

    for (int i = 0; i < town_count; i++)
        parent[i] = i;

    for (int i = 0; i < road_count; i++)
    {
        scanf("%d%d%d", &roads[i].a, &roads[i].b, &roads[i].thicc);
        roads[i].a--; roads[i].b--;
    }

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        scanf("%d%d%d", &queries[i].a, &queries[i].b, &queries[i].thicc);
        queries[i].a--; queries[i].b--;
        queries[i].index = i;
    }

    std::sort(roads,   roads   + road_count, [](const auto& lhs, const auto& rhs) { return lhs.thicc > rhs.thicc; }); // reverse order
    std::sort(queries, queries + town_count, [](const auto& lhs, const auto& rhs) { return lhs.thicc > rhs.thicc; }); // reverse order

    Road* merge_cursor = &roads[0];
    for (int i = 0; i < q; i++)
    {
        while (queries[i].thicc <= merge_cursor->thicc && merge_cursor < roads + road_count)
        {
            unionize(merge_cursor->a, merge_cursor->b);
            merge_cursor++;
        }

        anwsers[queries[i].index] = find(queries[i].a) == find(queries[i].b);
    }

    for (int i = 0; i < q; i++)
        printf("%s\n", anwsers[i] ? "DA" : "NE");

    return 0;
}
