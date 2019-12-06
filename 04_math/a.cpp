#include <stdio.h>


constexpr int MAXN = 100000;
int memo[MAXN + 1];
int cum[MAXN + 1][129]; // ;)

int main()
{
    for (int i = 1; i <= MAXN; i++)
        for (int d = i; d <= MAXN; d += i)
            memo[d]++;

    for (int number = 1; number <= MAXN; number++)
    {
        int divider_count = memo[number];
        cum[number][divider_count]++;

        for (int d = 1; d < 129; d++)
            cum[number][d] += cum[number - 1][d];
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++)
    {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);

        if (k > 128)
        {
            printf("0\n");
            continue;
        }

        int count = cum[b][k] - cum[a - 1][k];

        //int count = 0;
        //for (int n = a; n <= b; n++)
        //    if (memo[n] == k)
        //        count++;

        printf("%d\n", count);
    }

    return 0;
}