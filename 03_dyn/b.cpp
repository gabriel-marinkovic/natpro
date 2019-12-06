#include <stdio.h>
#include <string.h>

inline int max(int a, int b) { return a > b ? a : b; }

char m[2][500];
int  p[2][500];

int nx;
int group_count;
int group_size;

int memo[500][50][2][2]; // [x][remaining][allow_top][allow_bot] -> result

bool can_place_up(int x)    { return p[0][x] >= group_size; }
bool can_place_down(int x)  { return p[1][x] >= group_size; }
bool can_place_block(int x) { return p[0][x] >= group_size / 2 && p[1][x] >= group_size / 2; }

int search(int x, int remaining, bool allow_top, bool allow_bot)
{
    if (!remaining) return 1;
    if (x >= nx)    return 0;

    int result = memo[x][remaining][allow_top][allow_bot];
    if (result != -1)
        return result;

    long long best = 0;
    if (allow_top &&              can_place_up(x))    best += search(x + group_size, remaining - 1, false, true);
    if (allow_bot &&              can_place_down(x))  best += search(x + group_size, remaining - 1, true, false);
    if (allow_top && allow_bot && can_place_block(x)) best += search(x + group_size / 2, remaining - 1, false, false);
    best += search(x + 1, remaining, true, true);

    best %= 1000000007;

    memo[x][remaining][allow_top][allow_bot] = best;
    return best;
}

int main()
{
    memset(memo, 0xFF, sizeof(memo));

    scanf("%d%d%d", &nx, &group_count, &group_size);

    scanf("%s", m[0]);
    scanf("%s", m[1]);

    for (int y = 0; y < 2; y++)
    {
        int spots = 0;
        for (int x = nx - 1; x >= 0; x--)
        {
            spots = m[y][x] == 'X' ? 0 : spots + 1;
            p[y][x] = spots;
        }
    }

#if 0
    for (int y = 0; y < 2; y++)
    {
        for (int x = 0; x < nx; x++)
            printf("%d", p[y][x]);
        printf("\n");
    }
#endif

    printf("%d", search(0, group_count, true, true));
}
