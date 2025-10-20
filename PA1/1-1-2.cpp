// 1-1-2 Interview
// structure: doubly linked list
#include <cstdio>

struct people
{
    int num;
    people *next; // counter-clockwise neighbor
    people *pred; // clockwise neighbor
};

people que[1000000]; // input list
people *head, *p;

void create()
{
    head = &que[0];
    head->next = head; // make the ring
    head->pred = head;
}

people *sitin(int n, int m)
{
    p = head; // p points to the last seated one
    for (int i = 1; i < n; i++)
    {
        // DEBUG: (m-1) instead of m
        int k = (m - 1) % i; // use mode

        // PERF: choose the direction of addressing
        if (k > i / 2)
        {
            k = i - k;
            for (int j = 0; j < k; j++)
            {
                p = p->pred;
            }
        }
        else
        {
            for (int j = 0; j < k; j++)
            {
                p = p->next;
            }
        }

        // insert
        que[i].next = p->next;
        p->next->pred = &que[i];

        p->next = &que[i];
        que[i].pred = p;

        p = p->next;
    }
    return p;
}

int main()
{
    int n, m;
    if (scanf("%d %d", &n, &m) != 2)
    {
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &que[i].num);
    }

    create();
    people *pp = sitin(n, m);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pp->num);
        pp = pp->pred;
    }

    return 0;
}