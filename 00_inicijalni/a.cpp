#include <stdlib.h>
#include <stdio.h>

int main()
{
    int input;
    scanf("%d", &input);

    int sum = 0;
    for (int i = 1; i <= input; i++)
    {
        if (i % 13 == 0) sum += 2 * i;
        else             sum += i;
    }

    printf("%d", sum);
    return 0;
}
