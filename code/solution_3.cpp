#include <cstdio>

int matrix[2001][2001];
int rowsum[2001][2001];
int rowcolsum[2001][2001];

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
            // printf("%d ", rowsum[i][j]);
        }
        // printf("\n");
    }

    for (int j = 1; j <= m; ++j)
    {
        rowcolsum[0][j] = 0;
        for (int i = 1; i <= n; ++i)
        {
            rowcolsum[i][j] = rowcolsum[i - 1][j] + rowsum[i][j];
            // printf("%d ", rowcolsum[i][j]);
        }
        // printf("\n");
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        // 单次查询为O(1)
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        int sum = rowcolsum[x + a - 1][y + b - 1] - rowcolsum[x + a - 1][y - 1] - rowcolsum[x - 1][y + b - 1] + rowcolsum[x - 1][y - 1];
        printf("%d\n", sum);
    }
    return 0;
}