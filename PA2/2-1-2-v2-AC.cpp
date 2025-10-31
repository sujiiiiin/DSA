// 2-1-2 Risks
// 共计用时5h：write 1.5h + debug 3.5h

#include <cstdio>

int n, t;
int xlist[1000001];    // 每天确诊人数
int Maxqueue[1000001]; // 辅助队列；保证降序；修改为存储达到最大值的角标
int mf = 0, mb = 0;    // [maxfront, maxback)
int maxlist[1000001];  // 确诊人数最大值
int tmp[1000001];      // DEBUG: 数组开的不够大！造成小数据AC大数据WA的问题不只有没开longlong

//! 空队列检查

void calculate(int pos, long long int mi) // 传入当前位置
{
    if (mi > pos) // 避免查询天数超出第1天
        mi = pos;

    if (pos > mi)
    {
        while (Maxqueue[mf] < pos - mi)
        {
            mf++;
        }
    }

    // mi天中的最大值一定在Maxqueue队首
    if (mf < mb)
        maxlist[pos] = xlist[Maxqueue[mf]];
    else
        maxlist[pos] = 0; // 注意maxqueue为空的情况

    // printf("maxlist[%d] = %d \n", pos, maxlist[pos]);

    // 更新队列
    while (mf < mb && xlist[Maxqueue[mb - 1]] < xlist[pos])
    {
        mb--;
    }
    mb++;
    Maxqueue[mb - 1] = pos;

    return;
}
// 每个元素均出队入队一次，均摊复杂度为2n = O(n) = 10^6

// query的时间复杂度为T*n = 10^5*10^6 = 10^11 ，瓶颈！

void sort(int l, int h)
{
    if (h - l <= 1)
        return;

    int m = l + (h - l) / 2;

    sort(l, m);
    sort(m, h);
    int i = l, j = m, k = 0;
    while (i < m && j < h)
    {
        if (maxlist[i] < maxlist[j])
        {
            tmp[k++] = maxlist[i++];
        }
        else
        {
            tmp[k++] = maxlist[j++];
        }
    }
    while (i < m)
    {
        tmp[k++] = maxlist[i++];
    }
    while (j < h)
    {
        tmp[k++] = maxlist[j++];
    }

    for (int idx = 0; idx < k; idx++)
    {
        maxlist[l + idx] = tmp[idx];
    } // DEBUG:从哪儿copy到哪。k！
}

int search(int lo, int hi, long long int val)
{
    while (lo < hi)
    {
        int mi = lo + (hi - lo) / 2;
        if (val < maxlist[mi])
        {
            hi = mi;
        }
        else
        {
            lo = mi + 1;
        }
    }
    return lo - 1;
}

void query(long long int p, long long int q)
{
    int cntlow = 0, cntmid = 0;

    cntlow = search(0, n, p - 1) + 1;
    cntmid = search(0, n, q - 1) + 1 - cntlow;

    printf("%d %d\n", cntlow, cntmid);
}

void queryright(long long int p, long long q)
{
    int cntlow = 0, cntmid = 0;
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
    printf("true: %d %d\n", cntlow, cntmid);
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

    for (int i = 0; i < n; i++)
    {
        printf("%d ", maxlist[i]);
    }
    printf("\n");

    // 查询预处理
    sort(0, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", maxlist[i]);
    }
    printf("\n");

    // 执行查询
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        long long int p, q;
        scanf("%lld %lld", &p, &q);
        query(p, q);
        queryright(p, q);
    }

    return 0;
}