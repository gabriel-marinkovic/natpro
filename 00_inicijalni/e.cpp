#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

typedef long long i64;

inline i64 max(i64 a, i64 b) { return a > b ? a : b; }

struct Task
{
    i64 time;
    i64 points;
};
std::vector<Task> tasks;

i64 time_to_points[10'000]; // memo

i64 best_score(i64 current_time)
{
    i64 memo = time_to_points[current_time];
    if (memo != -1)
        return memo;

    i64 best = 0;
    for (auto& task : tasks)
    {
        i64 time_after_task = current_time - task.time;
        if (time_after_task >= 0)
        {
            i64 score_after_task = task.points + best_score(time_after_task);
            best = max(best, score_after_task);
        }
    }

    time_to_points[current_time] = best; // memo
    return best;
}

int main()
{
    i64 task_count, total_time;
    scanf("%I64d%I64d", &task_count, &total_time);

    tasks.reserve(task_count);

    for (i64 i = 0; i < task_count; i++)
    {
        i64 time, points;
        scanf("%I64d%I64d", &time, &points);
        tasks.push_back({time, points});
    }

    // nested sort; time then points
    //std::sort(tasks.begin(), tasks.end(), [](const auto& lhs, const auto& rhs)
    //{
    //    if (lhs.time == rhs.time)
    //        return lhs.points < rhs.points;
    //    return lhs.time < rhs.time;
    //});

    // initial memoisation
    memset(time_to_points, -1, 10'000 * sizeof(i64));
    //for (auto& task : tasks)
    //    time_to_points[task.time] = task.points;

    printf("%I64d\n", best_score(total_time));
    return 0;
}
