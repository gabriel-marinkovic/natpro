#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline int max(int a, int b) { return a > b ? a : b; }

constexpr int MAXN = 500'000 + 1;

struct Node
{
    Node* children[27] = {};
    int longest = 0;

    inline Node* next(char c, int length)
    {
        int index = (c == ' ') ? 26 : (c - 'a');

        if (children[index] == NULL)
            children[index] = new Node;

        Node* node = children[index];
        node->longest = max(node->longest, length);
        return node;
    }
};

Node root;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char type[2];
        char str[MAXN];
        scanf("%s%*[ ]%[^\n]", type, str);

        // save to trie
        int length = strlen(str);

        Node* cursor = &root;
        for (char *c = str + 1; *c != '\0'; c++)
        {
            cursor = cursor->next(*c, length);
        }

        if (type[0] == 's')
        {
            printf("%d\n", cursor->longest);
        }
    }

    return 0;
}
