// 展示STL六大组件之间的关系
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main()
{
    int ia[6] = {27,210,12,47,109,83};
    // container:vector allocator:allocator<int>()
    vector<int, allocator<int>> vi(ia, ia + 6);

    // algorithm:count_if iterator:vi.begin() vi.end()
    // function object:less<int>() function adapter:binder
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));

    return 0;
}