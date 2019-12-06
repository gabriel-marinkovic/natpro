#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <unordered_map>

typedef unsigned long long u64;

void print_vector(std::vector<u64> v)
{
    printf("[");
    for (auto& e : v)
        printf("%llu,", e);
    printf("]\n");
}

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }


int main()
{
    int n, q;
    scanf("%d%d", &n, &q);

    std::vector<int> nums(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int max_num = 0;
    for (auto &num : nums)
        max_num = max(max_num, num);

    std::unordered_map<int, int> num_to_index = {};
    for (int i = 0; i < n; i++)
        if (!num_to_index[nums[i]])
            num_to_index[nums[i]] = i + 1;

    for (int i = 0; i < q; i++)
    {
        int index, number;
        scanf("%d%d", &index, &number);

        int found = num_to_index[number];
        if (found <= index && found != 0)
            printf("DA\n");
        else
            printf("NE\n");
    }

    return 0;
}
