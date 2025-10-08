#include <cstdio>

int matrix[2001][2001];
long long int rowsum[2001][2001];

int main()
{
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        rowsum[i][0] = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (i == 1)
                rowsum[0][j] = 0;
            rowsum[i][j] = rowsum[i][j - 1] + rowsum[i - 1][j] - rowsum[i - 1][j - 1] + matrix[i][j];
        }
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        // 单次查询为O(1)
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        long long int sum = rowsum[x + a - 1][y + b - 1] - rowsum[x + a - 1][y - 1] - rowsum[x - 1][y + b - 1] + rowsum[x - 1][y - 1];
        printf("%lld\n", sum);
    }
    return 0;
}