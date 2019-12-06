#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef size_t umm;

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }


struct Point
{
    int x, y, z;
};

inline Point max(Point a, Point b) { return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) }; }
inline Point min(Point a, Point b) { return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) }; }

template<typename T>
struct Array_3D
{
    umm columns, rows, layers;
    T* data;

    inline T& at(umm column, umm row, umm layer)
    {
        return *(this->data + column
                            + row   * this->columns
                            + layer * this->columns * this->rows);
    }

    inline T& at(Point p)
    {
        return *(this->data + p.x
                            + p.y * this->columns
                            + p.z * this->columns * this->rows);
    }
};

template<typename T>
Array_3D<T> allocate_array_3d(umm columns, umm rows, umm layers)
{
    Array_3D<T> result;
    result.columns = columns;
    result.rows    = rows;
    result.layers  = layers;
    result.data    = (T*)calloc(columns * rows * layers, sizeof(T));
    return result;
}

int main()
{
    int layers, rows, columns;
    scanf("%d%d%d", &layers, &rows, &columns);

    Array_3D<int> m = allocate_array_3d<int>(columns + 1, rows + 1, layers + 1);

    for (umm l = 1; l <= layers;  l++)
    for (umm r = 1; r <= rows;    r++)
    for (umm c = 1; c <= columns; c++)
    {
        auto& cell = m.at(c, r, l);
        scanf("%d", &cell);

        cell ^= m.at(c-1, r,   l);
        cell ^= m.at(c,   r-1, l);
        cell ^= m.at(c,   r,   l-1);
        cell ^= m.at(c-1, r-1, l);
        cell ^= m.at(c,   r-1, l-1);
        cell ^= m.at(c-1, r,   l-1);
        cell ^= m.at(c-1, r-1, l-1);
    }


    int n_q;
    scanf("%d", &n_q);

    for (umm q = 0; q < n_q; q++)
    {
        Point a, b;
        scanf("%d%d%d%d%d%d", &a.z, &a.y, &a.x, &b.z, &b.y, &b.x);
        a.x--;
        a.y--;
        a.z--;

        // p1 closest to the origin, p8 farthest.
        Point p5, p6, p7, p8, // "top" points of the cube
              p1, p2, p3, p4; // "bottom" points

        p1 = { a.x, a.y, a.z };
        p2 = { b.x, a.y, a.z };
        p3 = { a.x, b.y, a.z };
        p4 = { b.x, b.y, a.z };
        p5 = { a.x, a.y, b.z };
        p6 = { b.x, a.y, b.z };
        p7 = { a.x, b.y, b.z };
        p8 = { b.x, b.y, b.z };

        umm res =  m.at(p8)
                ^ (m.at(p4) ^ m.at(p6) ^ m.at(p7))
                ^ (m.at(p2) ^ m.at(p3) ^ m.at(p5))
                ^  m.at(p1);

        printf("%d\n", res);
    }

    return 0;
}
