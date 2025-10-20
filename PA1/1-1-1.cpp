// 1-1-1 filename
// double pointer x -->
// 1-dimensional dp + cut branch

// k-windows AC
#include <cstdio>

int n = 0, m = 0, k = 0;
char A[501001];
char B[501001];
char prev[501001];
char curr[501001];

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int check(int *prev, int *curr)
{
    // init the first row
    for (int i = 0; i <= min(n, k); i++)
        prev[i] = i;

    for (int j = 1; j <= m; j++)
    {
        // curr[0] = (j > k ? -1 : j);

        int imin = max(0, j - k);
        int imax = min(n, j + k);

        for (int i = imin; i <= imax; i++)
        {
            if (A[i] == B[j])
            {
                curr[i] = prev[i - 1];
            }
            else
            {
                if (i == imin) // 可优化
                    curr[i] = prev[i] + 1;
                else if (i == j + k)
                    curr[i] = curr[i - 1] + 1;
                else
                    curr[i] = min(curr[i - 1], prev[i]) + 1;
            }
        }
        int *temp = prev;
        prev = curr;
        curr = temp;
    }

    if (prev[n] > k)
        return -1;
    else
        return prev[n];
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    scanf("%s", A);
    scanf("%s", B);

    int *row1 = new int[n + 1];
    int *row2 = new int[n + 1];

    int ret = check(row1, row2);
    printf("%d", ret);

    delete[] row1;
    delete[] row2;

    return 0;
}
