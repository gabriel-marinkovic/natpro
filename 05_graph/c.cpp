#include <stdio.h>
#include <string.h>

constexpr int MAXD = 1000;

char m[MAXD][MAXD];

int main()
{
    int y, x;
    scanf("%d%d", &y, &x);

    for (int i = 0; i < y; i++)
        scanf("%s", m[i]);

    return 0;
}
