#include <stdio.h>
#include <string.h>

typedef unsigned char u8;

u8 map[1001][1001];

int memo[1001][1001];

int m, n;

int dinamika(int x, int y)
{
    if (x > m || y > n)   return 0;
    if (map[y][x] == 1)   return 0;


    int result = memo[y][x];
    if (result != -1)
        return result;

    if (x == m && y == n) 
        result = 1;
    else
        result = (dinamika(x + 1, y) + dinamika(x, y + 1)) % (1'000'000'000 + 7);

    memo[y][x] = result;
    return result;
}

int main()
{
    memset(memo, 0xFF, sizeof(memo));

    int p;
    scanf("%d%d%d", &m, &n, &p);

    for (int i = 0; i < p; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        map[y][x] = 1;
    }

    printf("%d", dinamika(0, 0));

    return 0;
}