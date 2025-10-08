#include <cstdio>

int matrix[2000][2000];
int rowsum[2000][2000];

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
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
        }
    }
    scanf("%d", &q);
    int sum = 0;
    for (int i = 1; i <= q; ++i)
    {
        // 单次查询为O(n)
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j)
        {
            sum += rowsum[x + j][y + b] - rowsum[x + j][y];
        }
        printf("%d\n", sum);
    }
    return 0;
}