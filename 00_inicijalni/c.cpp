#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

int main()
{
    int e_count, q_count;
    scanf("%d%d", &e_count, &q_count);

    std::vector<int> salary;
    salary.reserve(e_count);

    for (int i = 0; i < e_count; i++)
    {
        int s;
        scanf("%d", &s);
        salary.push_back(s);
    }

    for (int i = 0; i < q_count; i++)
    {
        char type[8];
        scanf("%s", type);

        if (strcmp(type, "sum") == 0)
        {
            int low, high;
            scanf("%d%d", &low, &high);

            int sum = 0;
            for (int i = low; i <= high; i++)
            {
                sum += salary[i-1];
            }

            printf("%d\n", sum);
            continue;
        }

        if (strcmp(type, "raise") == 0)
        {
            int low, high, raise;
            scanf("%d%d%d", &low, &high, &raise);
            for (int i = low; i <= high; i++)
                salary[i-1] += raise;

            continue;
        }
    }
}
