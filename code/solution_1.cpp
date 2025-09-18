#include <cstdio>

int matrix[2000][2000];

int main()
{
    // freopen("../3.in", "r", stdin); // 从 input.txt 读入
    // freopen("../my.ans", "w", stdout);

    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        // 单次查询为O(n^2)
        int sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j)
        {
            for (int k = 0; k < b; ++k)
            {
                sum += matrix[x + j][y + k];
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}