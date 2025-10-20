// 1-2-2 Graphics
#include <cstdio>

int n, m;
int u[200001];
int v[200001];
int tmp_arr[200001];

// 查询函数
int query(int x, int y)
{
    int lo = 0, hi = n - 1;
    int result = n; // 默认值，表示所有直线都满足条件

    // 二分查找：在排序后的直线数组中查找第一个不满足条件的直线
    while (lo <= hi)
    {
        // 查询区间为 [lo,hi]
        // int mi = (lo + hi) >> 1;
        int mi = lo + (hi - lo) / 2;

        // 计算判别式：p>0时无交点，需找到第一个无交点的位置
        long long p = -((long long)u[mi] * y + (long long)v[mi] * x - (long long)u[mi] * v[mi]);
        if (p > 0)
        {
            result = mi; // 记录当前位置，满足p>0
            hi = mi - 1; // 向左半部分继续查找
        }
        else
        {
            lo = mi + 1; // 向右半部分继续查找
        }
    }
    return result; // 返回，数值上等于交点个数
}

// 排序
void sort(int l, int r, int arr[])
{
    if (r - l <= 1)
        return;
    int m = l + (r - l) / 2;
    sort(l, m, arr);
    sort(m, r, arr);
    int i = l, j = m, k = l;
    while (i < m && j < r)
    {
        if (arr[i] <= arr[j])
            tmp_arr[k++] = arr[i++];
        else
            tmp_arr[k++] = arr[j++];
    }
    while (i < m)
        tmp_arr[k++] = arr[i++];
    while (j < r)
        tmp_arr[k++] = arr[j++];
    for (int t = l; t < r; ++t)
        arr[t] = tmp_arr[t];
}

int main()
{
    // 读取输入数据
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &u[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    // 对u和v数组进行排序
    sort(0, n, u);
    sort(0, n, v);

    // 处理查询请求
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        int ret = query(x, y);
        printf("%d\n", ret);
    }

    return 0;
}