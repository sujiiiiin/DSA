// 1-1-2 Interview
#include <cstdio>

struct people
{
    int num;
    people *next;
    people *pred;
};

people que[1000000]; // input list
people *head, *tail;
people *p;

void create()
{
    head = &que[0];
    tail = &que[0];
    tail->next = head; // 成环
    head->pred = tail;
}

people *sitin(int n, int m)
{
    p = head;                   // p指向上一个入座人
    for (int i = 1; i < n; i++) // i表示第i个人入座
    {
        int k = (m - 1) % i; // 则有i个人已入座,k为真实步数; DEBUG:是m-1不是m

        if (k > i / 2)
        {
            k = i - k;
            for (int j = 0; j < k; j++) // TODO: 耗时！
            {
                p = p->pred;
            }
        }
        else
        {
            for (int j = 0; j < k; j++) // TODO: 耗时！
            {
                p = p->next;
            }
        }

        que[i].next = p->next;
        p->next->pred = &que[i];

        p->next = &que[i]; // insert
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