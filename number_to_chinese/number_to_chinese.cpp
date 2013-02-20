// number_to_chinese.cpp : Defines the entry point for the console application.
//

#include <tchar.h>

#include <cstdio>
#include <cassert>
#include <stack>
#include <locale>

using namespace std;

wchar_t chinese_name[10] = { L'零', L'一', L'三', L'四', L'五', L'六', L'七', L'八', L'九', L'十' };


void print(long long num)
{
    if (num < 0)
    {
        wprintf(L"¸º");
        num = -num;
    }

    stack<wchar_t> statement;
    for (int i = 0; num > 0; ++i)
    {
        static bool bSwitchUnit = false;
        bool bNeedZero = false;

        int n = num % 10;
        num /= 10;

        if (n > 0)
        {
            switch (i / 4)
            {
            case 0:
                break;

            case 1:
                if (bSwitchUnit)
                {
                    bSwitchUnit = false;
                    statement.push(L'万');
                }
                break;

            case 2:
                if (bSwitchUnit)
                {
                    bSwitchUnit = false;
                    statement.push(L'亿');
                }
                break;
            }

            switch (i % 4)
            {
            case 0:
                break;    // 个位

            case 1:
                statement.push(L'十');
                break;

            case 2:
                statement.push(L'百');
                break;

            case 3:
                statement.push(L'千');
                break;
            }

            statement.push(chinese_name[n]);
        }
        else
        {
            assert(0 == n);
            if (statement.size() > 0 && statement.top() != chinese_name[0]/* && !bSwitchUnit*/)
            {
                bNeedZero = true;
            }
            //else if (bSwitchUnit && i % 4 == 3)
            //{
            //    bNeedZero = true;
            //}

            if (bNeedZero)
            {
                statement.push(chinese_name[n]);
            }
        }

        if (i % 4 == 3)
        {
            bSwitchUnit = true;
        }
    }

    // special case for zero.
    if (0 == statement.size())
    {
        statement.push(chinese_name[0]);
    }

    while (statement.size() > 0)
    {
        wprintf(L"%c", statement.top());
        statement.pop();
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
    locale::global(locale("chinese_china"));

    long long num;
    scanf("%lld", &num);
    print(num);
    return 0;
}

