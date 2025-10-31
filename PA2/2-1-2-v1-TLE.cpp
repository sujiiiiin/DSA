#include <cstdio>

int n, t;
int xlist[1000001];    // 每天确诊人数
int xf = 0, xb = 0;    // [xfront, xback)
int Maxqueue[1000001]; // 辅助队列；保证降序
int mf = 0, mb = 0;    // [maxfront, maxback)
int maxlist[1000001];  // 确诊人数最大值

//! 空队列检查

void calculate(int pos, long long int mi) // 传入当前位置
{
    int x = xlist[pos];
    int ret = 0; // 默认值为0，提供了maxqueue为空时的情形

    if (mi > pos) // 避免查询天数超出第1天
        mi = pos;

    if (pos > mi)
    {
        // pop xqueue，同时对每个pop的x值判定，以更新maxqueue；
        // 直到xqueue开头来到 pos - mi（未细致想）的位置
        while (xf < pos - mi)
        {
            int a = xlist[xf];
            xf++;
            if (a == Maxqueue[mf])
                mf++;
        } // ！这层循环需要优化掉
    }

    // 之后剩余mi天中的最大值一定在Maxqueue队首
    if (mf < mb)
        ret = Maxqueue[mf];

    maxlist[pos] = ret;
    // printf("maxlist[%d] = %d \n", pos, ret);

    // 更新队列
    xb++;
    while (mb > mf && Maxqueue[mb - 1] < x)
    {
        mb--;
    }
    mb++;
    Maxqueue[mb - 1] = x;

    return;
}

void query(long long int p, long long int q)
{
    int cntlow = 0;
    int cntmid = 0;
    for (int i = 0; i < n; i++)
    {
        if (maxlist[i] < p)
        {
            cntlow++;
        }
        else if (maxlist[i] < q)
        {
            cntmid++;
        }
    }
    printf("%d %d\n", cntlow, cntmid);
}

int main()
{
    // 读入x数组
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &xlist[i]);
    }

    // 根据mi更新最大值数组
    for (int i = 0; i < n; i++)
    {
        long long int mi;
        scanf("%lld", &mi);
        calculate(i, mi);
    }

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", maxlist[i]);
    // }

    // 执行查询
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        long long int p, q;
        scanf("%lld %lld", &p, &q);
        query(p, q);
    }
}