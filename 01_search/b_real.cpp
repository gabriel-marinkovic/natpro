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
 
inline int min(int a, int b) { return a < b ? a : b; }
 
int main()
{
    int boxes, cows;
    scanf("%d%d", &boxes, &cows);
 
    std::vector<int> positions(boxes);
 
    for (int i = 0; i < boxes; i++)
        scanf("%d", &positions[i]);
 
    std::sort(positions.begin(), positions.end());
 
 
    int low  = 1;
    int high = 1000000000;
    int mid  = (low + high) / 2;
 
    while (low < high)
    {
        //printf("low: %d\nmid: %d\nhigh: %d\n-------\n", low, mid, high);
 
        int cows_left  = cows - 1;
        int accumulated = 0;
        for (int i = 0; i < boxes - 1; i++)
        {
            int b1 = positions[i];
            int b2 = positions[i + 1];
 
            accumulated += b2 - b1;
            if (accumulated >= mid)
            {
                cows_left--;
                accumulated = 0;
            }
        }
 
        if (cows_left > 0)
        {
            high = mid;
            mid = (low + high) / 2;
        }
        else
        {
            low = mid + 1;
            mid = (low + high) / 2;
        }
 
    }
 
    printf("%d", low - 1);
 
    return 0;
}
