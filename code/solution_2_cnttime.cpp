#include <cstdio>
#include <chrono>

int matrix[2000][2000];
int rowsum[2000][2000];

int main()
{
    // auto begin = std::chrono::high_resolution_clock::now();

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

    auto begin = std::chrono::high_resolution_clock::now();

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        // 单次查询为O(n)
        int sum = 0;
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j)
        {
            sum += rowsum[x + j][y + b - 1] - rowsum[x + j][y - 1];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("solution_2: %d s\n ", elapsed);

    return 0;
}