#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
using namespace std;


typedef long long i64;


inline i64 round_up_to_pow2(i64 n)
{
    i64 x = 1;
    while (x < n)
        x *= 2;
    return x;
}

template<typename T> using Merge_Function  =    T (T  left, T right);
template<typename T> using Update_Function = void (T* node, T value);


template<typename T>
struct Tournament
{
    T*  tree;
    i64 offset;

    T* values; // tree + offset
    i64 count;
};

template<typename T>
Tournament<T> make_tournament(i64 count)
{
    Tournament<T> tournament;
    tournament.offset = round_up_to_pow2(count);
    tournament.tree   = (T*)calloc(tournament.offset * 2, sizeof(T));
    tournament.count  = count;
    tournament.values = tournament.tree + tournament.offset;
    return tournament;
}

template<typename T>
Tournament<T> make_tournament_from_values(T* values, i64 count)
{
    auto tournament = make_tournament<T>(count);
    memcpy(tournament.values, values, count * sizeof(T));

    return tournament;
}

template<typename T>
void free_tournament(Tournament<T>* tournament)
{
    free(tournament->tree);
}


template<typename T, Merge_Function<T>* merge>
void build_tournament_tree(Tournament<T>* tournament)
{
    for (i64 i = tournament->offset - 1; i > 0; i--)
        tournament->tree[i] = merge(tournament->tree[i * 2], tournament->tree[i * 2 + 1]);
}


template<typename T, Merge_Function<T>* merge>
T vertical_query_element(Tournament<T>* tournament, i64 index)
{
    index += tournament->offset;
    T result = tournament->tree[index];
    while (index /= 2)
        result = merge(result, tournament->tree[index]);
    return result;
}

template<typename T, Merge_Function<T>* merge>
T query_subrange(Tournament<T>* tournament, i64 low, i64 high, i64 node_over_subrange, i64 subrange_low, i64 subrange_high)
{
    //printf("subrange [%d, %d); node over %d; range [%d, %d).\n", subrange_low, subrange_high, node_over_subrange, low, high);

    if (subrange_low >= high || subrange_high <= low)
        return T{};

    if (subrange_low >= low && subrange_high <= high)
    {
        //printf("subrange [%d, %d); Returning tree[%d] = %d.\n", subrange_low, subrange_high, node_over_subrange, tournament->tree[node_over_subrange].low);
        return tournament->tree[node_over_subrange];
    }

    i64 next_subrange_low    = subrange_low;
    i64 next_subrange_high   = subrange_high;
    i64 next_subrange_middle = (subrange_low + subrange_high) / 2;

    i64 next_node1 = node_over_subrange * 2;
    i64 next_node2 = node_over_subrange * 2 + 1;

    T left_subrange  = query_subrange<T, merge>(tournament, low, high, next_node1, next_subrange_low,    next_subrange_middle);
    T right_subrange = query_subrange<T, merge>(tournament, low, high, next_node2, next_subrange_middle, next_subrange_high);

    return merge(left_subrange, right_subrange);
}

template<typename T, Merge_Function<T>* merge>
T horizontal_query_range(Tournament<T>* tournament, i64 low, i64 high)
{
    return query_subrange<T, merge>(tournament, low, high, 1, 0, tournament->offset);
}


template<typename T, Merge_Function<T>* merge>
void update_element(Tournament<T>* tournament, i64 index, T value)
{
    index += tournament->offset;
    tournament->tree[index] = value;
    while (index /= 2)
        tournament->tree[index] = merge(tournament->tree[index * 2], tournament->tree[index * 2 + 1]);
}

template<typename T, Update_Function<T>* update>
void update_subrange(Tournament<T>* tournament, i64 low, i64 high, i64 node_over_subrange, i64 subrange_low, i64 subrange_high, T value)
{
    //printf("subrange [%d, %d); node over %d; range [%d, %d).\n", subrange_low, subrange_high, node_over_subrange, low, high);

    if (subrange_low >= high || subrange_high <= low)
        return;

    if (subrange_low >= low && subrange_high <= high)
    {
        //printf("subrange [%d, %d); updating tree[%d] = %d with %d.\n", subrange_low, subrange_high, node_over_subrange, tournament->tree[node_over_subrange], value);
        update(&tournament->tree[node_over_subrange], value);
        return;
    }

    i64 next_subrange_low    = subrange_low;
    i64 next_subrange_high   = subrange_high;
    i64 next_subrange_middle = (subrange_low + subrange_high) / 2;

    i64 next_node1 = node_over_subrange * 2;
    i64 next_node2 = node_over_subrange * 2 + 1;

    update_subrange<T, update>(tournament, low, high, next_node1, next_subrange_low,    next_subrange_middle, value);
    update_subrange<T, update>(tournament, low, high, next_node2, next_subrange_middle, next_subrange_high,   value);
}

template<typename T, Update_Function<T>* update>
void update_range(Tournament<T>* tournament, i64 low, i64 high, T value)
{
    update_subrange<T, update>(tournament, low, high, 1, 0, tournament->offset, value);
}














int N;
constexpr int MAXN = 100000;
vector<int> conns[MAXN];

struct Node
{
    int index;
    int depth;
    bool valid;
};

Node merge(Node left, Node right)
{
    if (!right.valid) return left;
    if (!left.valid)  return right;
    return left.depth < right.depth ? left : right;
}
void update(Node* node, Node value)
{
    *node = value;
}

int first_location_in_array[MAXN];
vector<Node> nodes;
void fill(int node, int depth)
{
    nodes.push_back({ node, depth, true });
    first_location_in_array[node] = nodes.size() - 1;

    for (int child : conns[node])
    {
        fill(child, depth + 1);
        nodes.push_back({ node, depth, true });
    }
}

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
    int q;
    scanf("%d%d", &N, &q);

    for (int i = 0; i < N; i++)
    {
        int m;
        scanf("%d", &m);
        conns[i].reserve(m);

        for (int j = 0; j < m; j++)
        {
            int c;
            scanf("%d", &c);
            c--;
            conns[i].push_back(c);
        }
    }

    fill(0, 0);

    Tournament<Node> t = make_tournament_from_values(nodes.data(), nodes.size());
    build_tournament_tree<Node, &merge>(&t);

    for (int i = 0; i < q; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;

        int l = min(first_location_in_array[a], first_location_in_array[b]);
        int r = max(first_location_in_array[a], first_location_in_array[b]);

        Node lca = horizontal_query_range<Node, &merge>(&t, l, r);
        printf("%d\n", lca.index + 1);
    }

    return 0;
}
