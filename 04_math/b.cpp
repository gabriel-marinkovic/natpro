// a.zarada(dan)   = p * a.money(dan - 1)
// a.giveaway(dan) = a.zarada(dan)
// a.charity(dan)  = giver1.zarada(dan - 1) + giver2.zarada(dan - 1) + ... + giverN.zarada(dan - 1)
// a.money(dan)    = a.zarada(dan) - a.giveaway() + a.charity(dan) = a.charity(dan)

// a.money(dan) = a.charity(dan)

// a.zarada(dan) = p * a.money(dan - 1) 
//               = p * a.charity(dan - 1) 
//               = giver1.zarada(dan - 1) + giver2.zarada(dan - 1) + ... + giverN.zarada(dan - 1)

// a.zarada(dan + 1) = p * charity(dan + 1)
//                   = sigma_i<N(giver_i.zarada(dan))


/*

0 1 1 0     1 -> person 1 depends on 2 and 3
0 0 0 0     2
0 0 0 0     3
0 0 0 0     4

*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long s64;

constexpr s64 MOD  = 1'000'000'000 + 7;
constexpr int MAXN = 100;

int N = 0;
struct Matrix
{
    s64 data[MAXN][MAXN];
};

Matrix mul( Matrix* left, Matrix* right)
{
    Matrix out = {};

    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        s64 dot = 0;
        for (int k = 0; k < N; k++)
            dot = ((left->data[i][k] * right->data[k][j]) % MOD + dot) % MOD;

        out.data[i][j] = dot;
    }

    return out;
}

constexpr int POW2MAX = 63;

Matrix money         = {}; // use only first column
Matrix memo[POW2MAX] = {};

int main()
{
    int pairings;
    scanf("%d%d", &N, &pairings);

    for (int i = 0; i < pairings; i++)
    {
        int daddy, baby;
        scanf("%d%d", &daddy, &baby);
        daddy--; baby--;

        memo[0].data[baby][daddy] = 1;
    }

    for (int i = 0; i < N; i++)
        scanf("%lld", &money.data[i][0]);

    s64 day;
    scanf("%lld", &day);


    // everyone keeps their money
    for (int i = 0; i < N; i++)
        memo[0].data[i][i] = 1;

    for (int i = 1; i < POW2MAX; i++)
        memo[i] = mul(&memo[i - 1], &memo[i - 1]);

    int pow_of_digit = 0;
    while (day)
    {
        if (day & 1)
            money = mul(&memo[pow_of_digit], &money);

        day = day >> 1;
        pow_of_digit++;
    }

    for (int i = 0; i < N; i++)
        printf("%lld ", money.data[i][0]);

    return 0;
}