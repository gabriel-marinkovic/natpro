#include <stdlib.h>
#include <stdio.h>


inline int min(int a, int b) { return a < b ? a : b; }

struct Ingredient
{
    int count;
    int price;
};

int main()
{
    Ingredient meat, soy;
    int bun_count;
    scanf("%d%d%d", &meat.count, &soy.count, &bun_count);
    scanf("%d%d", &meat.price, &soy.price);

    Ingredient better, worse;
    if (meat.price > soy.price)
    {
        better = meat;
        worse = soy;
    }
    else
    {
        better = soy;
        worse = meat;
    }

    int profit = 0;
    profit += better.price * min(better.count, bun_count);

    bun_count -= min(better.count, bun_count);
    if (bun_count > 0)
        profit += worse.price * min(worse.count, bun_count);

    printf("%d", profit);
    return 0;
}
