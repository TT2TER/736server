#include <cstdio>
#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;
struct Ret
{
    int num;
    bool m; // n/y
};
stack<int> num;
stack<char> sig;
//一起用来定位优先顺序
char operation[9] =
    {'+', '-', '*', '/', '(', ')', '#', '^', '%'};
char checklist[9][9] = {
    {'>', '>', '<', '<', '<', '>', '>', '<', '<'},
    {'>', '>', '<', '<', '<', '>', '>', '<', '<'},
    {'>', '>', '>', '>', '<', '>', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '<', '>'},
    {'<', '<', '<', '<', '<', '=', ' ', '<', '<'},
    {'>', '>', '>', '>', ' ', '>', '>', '>', '>'},
    {'<', '<', '<', '<', '<', ' ', '=', '<', '<'},
    {'>', '>', '>', '>', '<', '>', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '<', '>'}};

int char2num(char *q)
{
    return (int)(*q - '0');
}

char compare(char x, char y)
{
    int a, b; //用来定位下标输出优先顺序
    for (int i = 0; i < 9; i++)
    {
        if (operation[i] == x)
        {
            a = i;
            break;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (operation[i] == y)
        {
            b = i;
            break;
        }
    }
    //得到优先级关系并且作为返回值
    return checklist[a][b];
}

Ret operate(int x, int y, char symbol)
{
    Ret ret;
    switch (symbol)
    {
    case '+':
        ret.num = x + y;
        ret.m = true;
        break;
    case '-':
        ret.num = x - y;
        ret.m = true;
        break;
    case '*':
        ret.num = x * y;
        ret.m = true;
        break;
    case '/':
        if (y)
        {
            ret.num = x / y;
            ret.m = true;
            break;
        }
        else
        {
            printf("Divide 0.\n");
            ret.m = false;
            break;
        }
    case '%':
        ret.num = (int)fmod(x, y);
        ret.m = true;
        break;
    case '^':
        if (y >= 0)
        {
            ret.num = (int)pow(x, y);
            ret.m = true;
            break;
        }
        else
        {
            printf("error.\n");
            ret.m = false;
            break;
        }
    default:
        printf("error.\n");
        ret.m = false;
        break;
    }
    return ret;
}

int main()
{
    int n;
    int flag; //数字0，（ 为1，其他2
    char expr[100], *p, *nega;
    char fnega = '0';

    scanf("%d", &n);

    while (n--)
    {
        while (!num.empty())
        {
            num.pop();
        }
        while (!sig.empty())
        {
            sig.pop();
        }

        flag = 2;
        memset(expr, '\0', 100);
        scanf("%s", expr);

        strcat(expr, "#");
        p = expr;
        nega = expr;

        // 第一个符号是负数号且第二个字符是数字
        // 把负数号替换为0
        if (*nega == '-' && *(nega + 1) == '(')
        { //型如-(2+2)+1 直接在num.stack中插入一个0
            num.push(char2num(&fnega));
        }

        if (*nega == '-' && *(nega + 1) >= '0' && *(nega + 1) <= '9')
        {
            *nega = '0';
        }
        nega++;
        // 遍历每一个字符
        for (; *nega != '\0'; nega++)
        {
            if ((*(nega - 1) < '0' || *(nega - 1) > '9') && (*nega == '-') && *(nega - 1) != ')')
            {
                *nega = '0';
            }
        }
        sig.push('#');
        int dead = 0;
        while (*p != '#' || sig.top() != '#')
        {
            if (*p >= '0' && *p <= '9')
            {
                if (flag == 0)
                {
                    if (num.top() <= 0)
                    {
                        int q = num.top();
                        num.pop();
                        num.push((q * 10 + char2num(p++) * (-1)));
                    }
                    else
                    {
                        int q = num.top();
                        num.pop();
                        num.push(q * 10 + char2num(p++));
                    }
                }
                else
                    num.push(char2num(p++));
                flag = 0;
            }
            else
            {
                //（+
                if (flag == 1)
                {
                    if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%' || *p == '^')
                    {
                        printf("error.\n");
                        {
                            dead = 1;
                            break;
                        }
                    }
                }
                //左括号标记为1
                if (*p == '(')
                {
                    flag = 1;
                }
                else
                    flag = 2;

                if (sig.empty())
                {
                    printf("error.\n");
                    {
                        dead = 1;
                        break;
                    }
                }
                else
                {
                    char ch = sig.top(), ans;
                    sig.pop();
                    //优先级比较
                    ans = compare(ch, *p);
                    if (ans == ' ')
                    {
                        printf("error.\n");
                        {
                            dead = 1;
                            break;
                        }
                    }
                    else if (ans == '<')
                    {
                        sig.push(ch); 
                        sig.push(*p++);
                        continue;
                    }
                    
                    else if (ans == '=')
                    {
                        p++;
                        continue;
                    }
                    else
                    {
                        int integer_x, integer_y;
                        integer_y = num.top();
                        num.pop();
                        integer_x = num.top();
                        num.pop();
                        Ret judge = operate(integer_x, integer_y, ch);
                        if (judge.m == false)
                        {
                            dead = 1;
                            break;
                        }
                        else
                            num.push(judge.num);
                        continue;
                    }
                    p++;
                }
            }
        }
        if (!dead && num.size() == 1 && sig.size() == 1)
            printf("%d\n", num.top());
        else if (!dead)
        {
            printf("error.\n");
        }
    }
    return 0;
}