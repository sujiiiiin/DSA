// 2-2-2 Polynomial
// 21:59  1.5h 本地Write+Debug完成整型计算器

#include <cstdio>
#include <ctype.h>
#include <math.h>

char S[1001000];
int n = 0;        // 最终字符串长度
int mapping[256]; // 操作符与优先级表序号的对应关系

struct Polynomial
{
    int k;     // 实际次数
    int x[65]; // x[i]表示x^i的系数
};

// Polynomial opnd[1001000]; // 操作数栈
int opnd[1001000];
int h_nd = 0;
char optr[1001000]; // 操作符栈
int h_tr = 0;

// 多项式运算方法
Polynomial add(Polynomial a, Polynomial b)
{
    int k = (a.k > b.k) ? a.k : b.k;
    for (int i = 0; i <= k; i++)
    {
        a.x[i] += b.x[i];
        if (a.x[i] != 0)
            a.k = i;
    }
    return a;
}
// minus(a,b)=add(a,-b)

Polynomial multiply(Polynomial a, Polynomial b)
{
    Polynomial tmp;
    for (int i = 0; i <= a.k; i++)
    {
        for (int j = 0; j <= b.k; j++)
        {
            tmp.x[i + j] += a.x[i] * b.x[j];
        }
    }
    for (int k = 0; k <= 64; k++)
    {
        a.x[k] = tmp.x[k];
        if (a.x[k] != 0)
            a.k = k;
    }
    return a;
}

Polynomial power(Polynomial a, int p)
{
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
        p = x;

        if (isdigit(p) && x == '(')
        {
            S[i] = '*';
            i++;
        }
        if (p != 'x' && x == 'x')
        {
            S[i] = '*';
            i++;
        }

        S[i] = x;
        i++;
    }
    S[i] = '\0';
    n = i;
}

int calculate(int opnd1, char op, int opnd2)
{
    if (op == '+')
    {
        return opnd1 + opnd2;
    }
    else if (op == '-')
    {
        return opnd1 - opnd2;
    }
    else if (op == '*')
    {
        return opnd1 * opnd2;
    }
    else if (op == '^')
    {
        return pow(opnd1, opnd2);
    }
}

// 处理读入的字符串（先实现非多项式版）
int evaluate()
{
    optr[h_tr] = '\0';
    h_tr++;

    int s = 0; // 当前字符下标
    while (h_tr != 0)
    {
        if (isdigit(S[s]))
        {
            int val = 0;
            while (isdigit(S[s]))
            {
                val = val * 10 + (int)(S[s] - '0');
                s++;
            } // 退出循环时隐含了s++
            opnd[h_nd] = val;
            h_nd++;
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
                char op = optr[h_tr - 1]; // 取值，用指针前一位
                h_tr--;

                int opnd2 = opnd[h_nd - 1];
                h_nd--;
                int opnd1 = opnd[h_nd - 1];
                h_nd--;
                // DEBUG:先取出右操作数，再取出左边

                int ret = calculate(opnd1, op, opnd2);

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
    char c;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        S[i] = c;
        i++;
    }
    n = i;

    init();

    int outcome = evaluate();

    printf("outcome:%d", outcome);

    return 0;
}