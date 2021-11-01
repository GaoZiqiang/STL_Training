#include <iostream>
#include <array>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
const long ASIZE = 500000L;

// utils function
long getATargetLong() {
    long target = 0;

    cout << "target (0 ~ " << RAND_MAX << "): " << endl;
    cin >> target;

    return target;
}

string getATargetString() {
    long target = 0;
    char buf[10];

    cout << "target (0 ~ " << RAND_MAX << "):";
    cin >> target;
    snprintf(buf, 10, "%d", target);

    return string(buf);
}

int compareLongs(const void* a, const void* b) {
    return (*(long*)a - *(long*)b);
}

// 从大到小
int sortCompare(const string a, const string b) {
    return a > b;
}
int compareStrings(const void* a, const void* b) {
    if (*(string*)a > *(string*)b)
        return 1;
    else if (*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

// test array
void testArray() {
    cout << "test array......" << endl;

    array<long, ASIZE> arr;

    clock_t time_start = clock();
    for (long i = 0; i < ASIZE; i++)
        arr[i] = rand();

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "array.size() = " << arr.size() << endl;
    cout << "array.front() = " << arr.front() << endl;// 就是第一个元素
    cout << "array[0] = " << arr[0] << endl;
    cout << "array.back() = " << arr.back() << endl;
    cout << "array[499999] = " << arr[499999] << endl;// 最后一个元素
    cout << "array.data() = " << arr.data() << endl;// 返回一个指向容器首个元素的指针

    long target = getATargetLong();

    time_start = clock();
    ::qsort(arr.data(), ASIZE, sizeof(long), compareLongs);
    long* p_item = (long*)::bsearch(&target, (arr.data()), ASIZE, sizeof(long), compareLongs);
    cout << "qsort()+bsearch(), milli-seconds: " << (clock() - time_start) << endl;
    if (p_item != nullptr)
        cout << "found, " << *p_item << endl;
    else
        cout << "not found!" << endl;
}

#include <vector>
#include <string>
#include <algorithm> 	//sort()
#include <typeinfo>

// test vector
void testVector(long& value) {

    cout << "test vector......" << endl;

    vector<string> vec;
    char buf[10];

    clock_t time_start = clock();

    for (long i = 0; i < value; i++) {
        snprintf(buf, 10, "%d", rand());// 将格式化的数据写入字符串
        try {
            vec.push_back(string(buf));// str-->string
        } catch(exception& p) {// 捕获异常
            cout << "异常, i = " << i << " " << p.what() << endl;
            abort();
        }
    }

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "vector.max_size() = " << vec.max_size() << endl;// max_size():当前程序最大可能可以容纳的元素个数
    cout << "vector.size() = " << vec.size() << endl;
    cout << "vector.front() = " << vec.front() << endl;
    cout << "vector.back() = " << vec.back() << endl;
    cout << "vector.data() = " << vec.data() << endl;
    cout << "vector.capacity() = " << vec.capacity() << endl;// capacity():当前程序已经分配给该vector对象的内存大小（单位为元素个数）

    string target = getATargetString();
    {
        time_start = clock();
        // 标准库函数--顺序查找
        auto p_item = find(vec.begin(), vec.end(), target);// find()--algorithmfwd.h
        cout << "std::find(), milli-seconds: " << (clock() - time_start) << endl;

        if (p_item != vec.end())
            cout << "found, " << *p_item << endl;
        else
            cout << "not found" << endl;
    }

    {
        time_start = clock();
        // 排序--自定义--从大到小
        cout << "vec.begin(): " << *vec.begin() << endl;
        cout << "type of *vec.begin(): " << typeid(*vec.begin()).name() << endl;
        sort(vec.begin(), vec.end(), sortCompare);
        cout << "sort(), milli-seconds: " << (clock() - time_start) << endl;

        time_start = clock();
        // 二分查找
        string* p_item = (string*)::bsearch(&target, (vec.data()), vec.size(), sizeof(string), compareStrings);
        cout << "bsearch(), milli-seconds: " << (clock() - time_start) << endl;

        if (p_item != nullptr)
            cout << "found, " << *p_item << endl;
        else
            cout << "not found!" << endl;

        vec.clear();
    }
}

#include <list>
// test list--双向链表，非连续存储空间
void testList(long& value) {
    cout << "test list......" << endl;
    list<string> list;
    char buf[10];

    clock_t time_start = clock();
    for (long i = 0; i < value; i++) {
        snprintf(buf, 10,  "%d", rand());
        try {
            list.push_back(string(buf));
        } catch(exception& p) {
            cout << "i = " << i << " " << p.what() << endl;
            abort();
        }
    }

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "list.size() = " << list.size() << endl;
    cout << "list.max_size() = " << list.max_size() << endl;
    cout << "list.front() = " << list.front() << endl;
    cout << "list.back() = " << list.back() << endl;

    string target = getATargetString();
    time_start = clock();
    auto p_item = find(list.begin(), list.end(), target);
    cout << "std::find(), milli-seconds: " << (clock() - time_start) << endl;

    if (p_item != list.end())
        cout << "found, " << *p_item << endl;
    else
        cout << "not found!" << endl;

    time_start = clock();
    // 使用list自带的sort方法--因为list的存储空间不是连续的，不能向vector等连续空间容器一样，使用他们的sort()方法
    list.sort();
    cout << "list.sort(), milli-seconds: " << (clock() - time_start) << endl;

    list.clear();
}

#include <forward_list>
// test forward_list--单向链表
void testForwardList(long& value) {
    cout << "test forward_list......" << endl;

    forward_list<string> flist;
    char buf[10];

    clock_t time_start;
    for (long i = 0; i < value; i++) {
        snprintf(buf, 10, "%d", rand());
        try {
            flist.push_front(string(buf));
        } catch(exception& p) {
            cout << "i = " << i << " " << p.what() << endl;
            abort();
        }
    }

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "forward_list.max_size() = " << flist.max_size() << endl;
    cout << "forward_list.front() = " << flist.front() << endl;

    string target = getATargetString();

    time_start = clock();
    auto p_item = find(flist.begin(), flist.end(), target);
    cout << "std::find(), milli-seconds: " << (clock() - time_start) << endl;

    if (p_item != flist.end())
        cout << "found, " << *p_item << endl;
    else
        cout << "not found!" << endl;

    time_start = clock();
    // forward_list自带的sort()方法
    flist.sort();
    cout << "flist.sort(), milli-seconds: " << (clock() - time_start) << endl;

    flist.clear();

}
int main() {
    int choice;
    long value;

    cout << "select: ";
    cin >> choice;

    if (choice != 1) {
        cout << "how many elements: ";
        cin >> value;
    }

    switch (choice) {
        case 1:
            testArray();
            break;
        case 2:
            testVector(value);
            break;
        case 3:
            testList(value);
            break;
        case 4:
            testForwardList(value);
            break;
    }
}