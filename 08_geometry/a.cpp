#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

struct Vector2
{
    float x, y;
};

inline float orientation(Vector2 a, Vector2 b, Vector2 c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline float distance(Vector2 a, Vector2 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

constexpr int MAXN = 100000;
std::vector<Vector2> points;

std::vector<Vector2> hull(std::vector<Vector2> points)
{
    int n = points.size();

    if (n <= 3)
        return points;

    std::sort(points.begin(), points.end(), [](Vector2& lhs, Vector2& rhs)
    {
        if (lhs.x == rhs.x) return lhs.y < rhs.y;
        return lhs.x < rhs.x;
    });

    std::vector<Vector2> hull;

    int hull_count = 0;
    for (int i = 0; i < n; i++)
    {
        while (hull_count >= 2 && orientation(hull[hull_count - 2], hull[hull_count - 1], points[i]) <= 0)
        {
            hull_count--;
            hull.pop_back();
        }

        hull.push_back(points[i]);
        hull_count++;
    }

    int one_more_than_first_half = hull_count + 1;
    for (int i = (n - 1) - 1; i >= 0; i--)
    {
        while (hull_count >= one_more_than_first_half && orientation(hull[hull_count - 2], hull[hull_count - 1], points[i]) <= 0)
        {
            hull_count--;
            hull.pop_back();
        }

        hull.push_back(points[i]);
        hull_count++;
    }

    return hull;
}

double length(std::vector<Vector2> points)
{
    double result = 0.0;
    for (int i = 0; i < points.size(); i++)
        result += distance(points[i], points[(i + 1) % points.size()]);
    return result;
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        Vector2 v;
        scanf("%f%f", &v.x, &v.y);
        points.push_back(v);
    }

    double r = length(hull(points));
    printf("%llu", (long long)floor(r));

    return 0;
}
