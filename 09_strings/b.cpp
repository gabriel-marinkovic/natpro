#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline int max(int a, int b) { return a > b ? a : b; }

char pattern[400'000 + 1];

constexpr int MAXN = 40'000;


struct Hash
{
    int bpow[MAXN];
    int hash[MAXN];
    int length;

    static constexpr int BASE = 191;

    void make_hash(char* str)
    {
        hash[0] = 0;
        bpow[0] = 1;

        int cursor = 0;
        while (str[cursor] != '\0')
        {
            if (cursor > 0)
            {
                bpow[cursor] = bpow[cursor - 1] * BASE;
                hash[cursor] = hash[cursor - 1] * BASE;
            }
            hash[cursor] += str[cursor];

            cursor++;
        }
        bpow[cursor] = bpow[cursor - 1] * BASE;

        length = cursor;
    }

    int subhash(int start, int length)
    {
        int upper = hash[start + length - 1];

        int lower;
        if (start > 0) lower = hash[start - 1] * bpow[length];
        else           lower = 0;

        return upper - lower;
    }

    int full_hash()
    {
        return subhash(0, length);
    }
};

Hash hasher;
int main()
{
    scanf("%[^\n]", pattern);
    hasher.make_hash(pattern);

    int pattern_hash   = hasher.full_hash();
    int pattern_length = hasher.length;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char str[MAXN + 1] = {};
        scanf("%*[\n\r]%[^\n]", str);

        hasher.make_hash(str);

        for (int i = 0; pattern_length + i <= hasher.length; i++)
        {
            int subash = hasher.subhash(i, pattern_length);
            if (subash != pattern_hash)
                continue;

            if (memcmp(pattern, str + i, pattern_length))
                continue;

            printf("%d\n", i);
            goto next;
        }

        printf("-1\n");
        next:;
    }

    return 0;
}
