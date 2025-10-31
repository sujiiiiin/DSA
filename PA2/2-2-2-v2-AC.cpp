// 2-2-2 Polynomial
// 21:59  1.5h 本地Write+Debug完成整型计算器
// 22:30  0.5h 本地Write完多项式计算器
// 00：30 15min 本地Debug完多项式计算器
// 00:32 MLE
// 9：30-10:40 依次解决MLE、WA、RE
// 10：40 定位了RE的问题
// 11:20 只剩下一个点TLE和一个点WA(RE)
// 19：00-21：30 在志愿者的帮助下解决了两个问题，主要是RE
// 总共用时 2h + 4.5h = 6.5h

#include <cstdio>
#include <ctype.h>
#include <math.h>
#include <cstdlib>

char S[5000000];
int n = 0;        // 最终字符串长度
int mapping[256]; // 操作符与优先级表序号的对应关系
long long int M = 1000000007;

struct Polynomial
{
    int k;                     // 实际次数
    long long int x[65] = {0}; // x[i]表示x^i的系数
    // DEBUG:开longlong，由于乘法时系数M*M达到10^18会越界
};

Polynomial opnd[300000]; // 操作数栈
// int opnd[1001000];
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

// minus(a,b)=add(a,-b)
// 直接复制的，注意debug时一起d
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

// if (can oprate) ==> pri[stack.top()][S]=='>'

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

// 处理读入的字符串（先实现非多项式版）（再实现多项式版本）
Polynomial evaluate()
{
    optr[h_tr] = '\0';
    h_tr++;

    int s = 0; // 当前字符下标
    // bool expect_operand = true; // DEBUG: 布尔值标注语法状态

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

            // expect_operand = false;
        }
        else if (S[s] == 'x')
        {
            Polynomial c;
            c.k = 1;
            c.x[1] = 1;

            opnd[h_nd] = c;
            h_nd++;

            s++; // DEBUG:死循环，s没有自加加
            // expect_operand = false;
        }
        // // 处理一元负号
        // else if (S[s] == '-' && expect_operand)
        // {
        //     Polynomial zero;
        //     zero.k = 0;
        //     zero.x[0] = 0;
        //     opnd[h_nd++] = zero;
        //     optr[h_tr++] = '-';
        //     s++;
        //     // expect_operand保持为true，因为减号后面还需要操作数
        // }
        else
        {
            // 相比栈顶字符，下一字符优先级高
            char c1 = optr[h_tr - 1], c2 = S[s];
            if (pri[mapping[c1]][mapping[c2]] == '<')
            {
                optr[h_tr] = S[s]; // 存值，直接用指针位
                h_tr++;

                s++;
                // expect_operand = true;
            }
            // 相比栈顶字符，下一字符优先级低
            else if (pri[mapping[c1]][mapping[c2]] == '>')
            {
                // DEBUG
                if (h_tr < 1 || h_nd < 2)
                {
                    exit(mapping[40]); // DEBUG
                    break;
                }

                char op = optr[h_tr - 1]; // 取值，用指针前一位
                h_tr--;

                Polynomial &opnd2 = opnd[h_nd - 1];
                h_nd--;
                Polynomial &opnd1 = opnd[h_nd - 1];
                h_nd--;
                // DEBUG:先取出右操作数，再取出左边

                Polynomial ret = calculate(opnd1, op, opnd2);

                opnd[h_nd] = ret;
                h_nd++;
            }
            // 左右括号或'\0'匹配
            else if (pri[mapping[c1]][mapping[c2]] == '~')
            {
                h_tr--;

                s++;
                // expect_operand = false;
            }
        }
    }
    return opnd[h_nd - 1];
}

int main()
{
    read();

    init();

    // for (int i = 0; S[i] != '\0'; i++)
    // {
    //     printf("%c", S[i]);
    // }
    // printf("\n");

    Polynomial outcome = evaluate();

    if (outcome.k == 0 && outcome.x[0] == 0)
    {
        printf("%d", 0); // DEBUG:一个点WA，未考虑结果为0的特殊情况；
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