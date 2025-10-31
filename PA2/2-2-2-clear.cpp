// 2-2-2 Polynomial
// 多项式计算器
// 用stack实现运算式求值

#include <cstdio>
#include <ctype.h>
#include <math.h>
#include <cstdlib>

char S[5000000];  // 表达式字符串
int n = 0;        // 最终字符串长度
int mapping[256]; // 操作符与优先级表序号的对应关系
long long int M = 1000000007;

struct Polynomial
{
    int k;                     // 实际次数
    long long int x[65] = {0}; // x[i]表示x^i的系数
};

Polynomial opnd[300000]; // 操作数栈
int h_nd = 0;
char optr[2001000]; // 操作符栈
int h_tr = 0;

// 多项式运算方法
Polynomial add(Polynomial &a, Polynomial &b)
{
    Polynomial result;
    int k = (a.k > b.k) ? a.k : b.k;

    for (int i = 0; i <= k; i++)
    {
        result.x[i] = (a.x[i] + b.x[i]) % M;
    }

    while (k >= 0 && result.x[k] == 0)
    {
        k--;
    }
    result.k = k;

    return result;
}

Polynomial minus(Polynomial &a, Polynomial &b)
{
    Polynomial result;
    int k = (a.k > b.k) ? a.k : b.k;

    for (int i = 0; i <= k; i++)
    {
        result.x[i] = a.x[i] - b.x[i];
        if (result.x[i] < 0)
            result.x[i] += M;
    }

    while (k > 0 && result.x[k] == 0)
    {
        k--;
    }
    result.k = k;

    return result;
}

Polynomial multiply(const Polynomial &a, const Polynomial &b)
{
    Polynomial result;

    int k = a.k + b.k;

    for (int i = 0; i <= a.k; i++)
    {
        if (a.x[i] == 0)
        {
            continue;
        }
        for (int j = 0; j <= b.k; j++)
        {
            if (b.x[j] == 0)
            {
                continue;
            }

            result.x[i + j] += (long long int)a.x[i] * b.x[j];
            result.x[i + j] %= M;
        }
    }

    result.k = k;

    return result;
}

Polynomial power(Polynomial &a, int p)
{
    Polynomial result = a;

    for (int i = 0; i < p - 1; i++)
    {
        result = multiply(result, a);
    }

    result.k = a.k * p;

    return result;
}

const char pri[7][7] = { // 优先级快查表[栈顶][当前]
                         /*         |------------ 当 前 运 算 符 ------------|  */
                         /*          +    -    *    ^    (    )   \0 */
    /*--  + */ '>', '>', '<', '<', '<', '>', '>',
    /* |  - */ '>', '>', '<', '<', '<', '>', '>',
    /* 栈 * */ '>', '>', '>', '<', '<', '>', '>',
    /* 运 ^ */ '>', '>', '>', '>', '<', '>', '>',
    /* 符 ( */ '<', '<', '<', '<', '<', '~', ' ',
    /* |  ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /*-- \0 */ '<', '<', '<', '<', '<', ' ', '~'};

void init()
{
    mapping['+'] = 0;
    mapping['-'] = 1;
    mapping['*'] = 2;
    mapping['^'] = 3;
    mapping['('] = 4;
    mapping[')'] = 5;
    mapping['\0'] = 6;
}

// 读入多项式字符串，补全可能省略的情况
void read()
{
    char p = NULL, x = NULL;

    int i = 0;
    while ((x = getchar()) != '\n')
    {
        if ((isdigit(p) || p == ')' || p == 'x') && x == '(')
        {
            S[i] = '*';
            i++;
        }
        if ((isdigit(p) || p == ')') && x == 'x')
        {
            S[i] = '*';
            i++;
        }

        S[i] = x;
        i++;
        p = x;
    }
    S[i] = '\0';
    n = i;
}

Polynomial calculate(Polynomial opnd1, char op, Polynomial opnd2)
{
    if (op == '+')
    {
        return add(opnd1, opnd2);
    }
    else if (op == '-')
    {
        return minus(opnd1, opnd2);
    }
    else if (op == '*')
    {
        return multiply(opnd1, opnd2);
    }
    else if (op == '^')
    {
        return power(opnd1, opnd2.x[0]); // 按约定，opnd2为1~4内正整数
    }
}

// 处理读入的字符串
Polynomial evaluate()
{
    optr[h_tr] = '\0';
    h_tr++;

    int s = 0; // 当前字符下标

    while (h_tr != 0)
    {
        if (isdigit(S[s]))
        {
            long long int val = 0;
            while (isdigit(S[s]))
            {
                val = val * 10 + (int)(S[s] - '0');
                s++;
            } // 退出循环时隐含了s++

            Polynomial c;
            c.k = 0;
            c.x[0] = val;

            opnd[h_nd] = c;
            h_nd++;
        }
        else if (S[s] == 'x')
        {
            Polynomial c;
            c.k = 1;
            c.x[1] = 1;

            opnd[h_nd] = c;
            h_nd++;

            s++;
        }
        else
        {
            // 相比栈顶字符，下一字符优先级高
            char c1 = optr[h_tr - 1], c2 = S[s];
            if (pri[mapping[c1]][mapping[c2]] == '<')
            {
                optr[h_tr] = S[s]; // 存值，直接用指针位
                h_tr++;

                s++;
            }
            // 相比栈顶字符，下一字符优先级低
            else if (pri[mapping[c1]][mapping[c2]] == '>')
            {
                // // DEBUG
                // if (h_tr < 1 || h_nd < 2)
                // {
                //     exit(mapping[40]);
                //     break;
                // }

                char op = optr[h_tr - 1]; // 取值，用指针前一位
                h_tr--;

                Polynomial &opnd2 = opnd[h_nd - 1];
                h_nd--;
                Polynomial &opnd1 = opnd[h_nd - 1];
                h_nd--;

                Polynomial ret = calculate(opnd1, op, opnd2);

                opnd[h_nd] = ret;
                h_nd++;
            }
            // 左右括号或'\0'匹配
            else if (pri[mapping[c1]][mapping[c2]] == '~')
            {
                h_tr--;

                s++;
            }
        }
    }
    return opnd[h_nd - 1];
}

int main()
{
    read();

    init();

    Polynomial outcome = evaluate();

    if (outcome.k == 0 && outcome.x[0] == 0)
    {
        printf("%d", 0); // 考虑结果为0的特殊情况
    }
    else
    {
        for (int i = outcome.k; i >= 0; i--)
        {
            long long int ret = outcome.x[i];

            if (ret < 0)
            {
                ret = (ret % M + M) % M;
            }
            else
            {
                ret %= M;
            }
            printf("%lld ", ret);
        }
    }

    return 0;
}