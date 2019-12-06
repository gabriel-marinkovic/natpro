#include <stdio.h>

inline int min(int a, int b) { return a < b ? a : b; }

struct Coin
{
    int  value;
    char color;
};

Coin coins[50];
int coin_count;

struct State
{
    int  remaining;
    char last_color;
};

int memo[1001][30] = {}; // [remaining][color] -> best

int search(State state)
{
    if (!state.remaining)
        return 0;

    int result = memo[state.remaining][state.last_color];
    if (result)
        return result;

    int best = 1 << 30;

    for (int i = 0; i < coin_count; i++)
    {
        Coin c = coins[i];

        if (c.color != state.last_color && c.value <= state.remaining)
        {
            State new_state;
            new_state.remaining  = state.remaining - c.value;
            new_state.last_color = c.color;

            best = min(best, 1 + search(new_state));
        }
    }

    memo[state.remaining][state.last_color] = best;
    return best;
}

int main()
{
    int price;
    scanf("%d%d", &coin_count, &price);

    for (int i = 0; i < coin_count; i++)
    {
        int value;
        char color;
        scanf("%d%*c%c", &value, &color);

        coins[i].value = value;
        coins[i].color = color - 'A';
    }

    printf("%d", search({ price, 0 }));

    return 0;
}
