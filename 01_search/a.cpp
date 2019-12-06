#include <stdio.h>

#include <vector>
#include <algorithm>

typedef unsigned long long u64;

void print_vector(std::vector<u64> v)
{
    printf("[");
    for (auto& e : v)
        printf("%llu,", e);
    printf("]\n");
}

int main()
{
    u64 n;
    scanf("%llu", &n);

    std::vector<u64> strengths(n);

    for (u64 i = 0; i < n; i++)
        scanf("%llu", &strengths[i]);

    std::sort(strengths.begin(), strengths.end(), [](auto a, auto b) { return a > b; });


    u64 shoots = 0;
    for (u64 i = 0; i < n; i++)
        shoots += (strengths[i] * i) + 1;

    printf("%llu", shoots);

    return 0;
}
