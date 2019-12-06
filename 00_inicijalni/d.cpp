#include <stdlib.h>
#include <stdio.h>
#include <vector>


int main()
{
    int field_x, field_y;
    scanf("%d%d", &field_y, &field_x);

    int pattern_x, pattern_y;
    scanf("%d%d", &pattern_y, &pattern_x);

    char* field = (char*)malloc(field_x * field_y * sizeof(char));
    for (int y = 0; y < field_y; y++)
        scanf("%s", field + (y * field_x));

    char* pattern = (char*)malloc(pattern_x * pattern_y * sizeof(char));
    for (int y = 0; y < pattern_y; y++)
        scanf("%s", pattern + (y * pattern_x));

    for (int y = 0; y <= field_y - pattern_y; y++)
    for (int x = 0; x <= field_x - pattern_x; x++)
    {
        for (int py = 0; py < pattern_y; py++)
        for (int px = 0; px < pattern_x; px++)
        {
            char cf = *(field   + (y + py) * field_x   + (x + px));
            char cp = *(pattern + (py)     * pattern_x + (px));
            if (cf != cp) goto next;
        }

        printf("DA\n");
        return 0;

        next:;
    }

    printf("NE\n");
    return 0;
}
