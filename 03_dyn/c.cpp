#include <stdio.h>
#include <string.h>

inline int max(int a, int b) { return a > b ? a : b; }

char m[200][200];

int memo[200][200][4] = {}; // [y][x][last_move] -> best

constexpr int DOWN  = 1;
constexpr int RIGHT = 2;
constexpr int DOWNRIGHT = 3;

int nx, ny;

inline int flower(int x, int y)
{
    return m[y][x] == 'X' ? 1 : 0;
}

int search(int x, int y, int move)
{
    if (x >= nx || y >= ny)
        return 0;

    int result = memo[y][x][move];
    if (result != -1)
        return result;

    int flowers = 0;

    if (move != DOWN)       flowers = max(flowers, search(x,     y + 1, DOWN));
    if (move != RIGHT)      flowers = max(flowers, search(x + 1, y,     RIGHT));
    if (move != DOWNRIGHT)  flowers = max(flowers, search(x + 1, y + 1, DOWNRIGHT));

    flowers += flower(x, y);

    memo[y][x][move] = flowers;
    return flowers;
}

int main()
{
    memset(memo, 0xFF, sizeof(memo));

    scanf("%d%d", &ny, &nx);

    for (int y = 0; y < ny; y++)
        scanf("%s", &m[y]);

    printf("%d", search(0, 0, 0));
}
