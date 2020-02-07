#include <stdio.h>
#include <vector>

typedef char s8;
enum Color : s8
{
    NOT_VISITED = 0,
    FIRST       = 1,
    SECOND      = -1,
};


constexpr int MAXN = 2000;
int N;

std::vector<int> convos[MAXN];
s8 color[MAXN];



bool check(int person, Color check_color)
{
    if (color[person] == check_color)  return true;
    if (color[person] == -check_color) return false;

    color[person] = check_color;

    for (int related : convos[person])
        if (!check(related, (Color)-check_color))
            return false;

    return true;
}


int main()
{
    int convo_count;
    scanf("%d%d", &N, &convo_count);

    for (int i = 0; i < convo_count; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        convos[a].push_back(b);
        convos[b].push_back(a);
    }

    for (int i = 0; i < N; i++)
    {
        if (color[i] == NOT_VISITED && !check(i, FIRST))
        {
            printf("NE");
            goto end;
        }
    }

    printf("DA");

end:
    return 0;
}
