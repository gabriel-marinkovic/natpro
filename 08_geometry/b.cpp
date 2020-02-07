#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

struct Event
{
    long long index;
    bool start;
};

Event evs[100000 * 2];

int main()
{
    long long n;
    scanf("%lld", &n);

    long long ev_count = 0;
    for (long long i = 0; i < n; i++)
    {
        long long start, length;
        scanf("%lld%lld", &start, &length);
        start--;

        evs[ev_count++] = { start, true };
        evs[ev_count++] = { start + length, false };
    }

    std::sort(evs, evs + ev_count, [](auto& l, auto& r)
    {
        if (l.index == r.index)
            return l.start < r.start;
        return l.index < r.index;
    });

    long long open_count = 0;
    long long best_count = 0;
    long long best_index = 0;

    for (long long i = 0; i < ev_count; i++)
    {
        open_count += evs[i].start ? 1 : -1;

        if (open_count > best_count)
        {
            best_count = open_count;
            best_index = evs[i].index;
        }
    }

    printf("%lld", best_index + 1);

    return 0;
}
