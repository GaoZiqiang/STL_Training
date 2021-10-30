#include <iostream>

using namespace std;

int mycount(int* begin, int* end, int val)
{
    int num = 0;
    while (begin != end)
    {
        if (*begin == val)
            num++;
        begin++;
    }
    return num;
}

int main()
{
    // 定义数组--容器
    int arr[] = {0,2,5,8,9,0};
    int* pBegin = arr;// 指向元素第一个位置
    int* pEnd = &arr[sizeof(arr) / sizeof(int)];// 最后一个元素之后的位置

    int res = mycount(pBegin, pEnd, 0);
    cout << "result: " << res << endl;
}