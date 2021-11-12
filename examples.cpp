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
    snprintf(buf, 10, "%ld", target);

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

    // vector遍历
//    cout << "vector遍历" << endl;
//    vector<string>::iterator vec_it = vec.begin();
//    cout << "sizeof(vec_it): " << sizeof(vec_it) << endl;
//    cout << "typeid(vec_it).name(): " << typeid(vec_it).name() << endl;
//    for (auto it = vec.begin(); it != vec.end(); ++it)
//        cout << *it << endl;

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
    cout << "测试list的iterator" << endl;
    cout << "type of iterator" << typeid(list.begin()).name() << endl;
    cout << "size of iterator" << sizeof(list.begin()) << endl;
    cout << "data of iterator1 " << list.begin()->data() << endl;
    cout << "data of iterator2 " << *(list.begin()) << endl;
//    cout << list.begin()->data()

    // 遍历list
    cout << "遍历list" << endl;
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << it->data() << " " << *it << endl;

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

// 测试test
#include <set>
void testSet(long& value) {
    cout << "test set()......" << endl;

    set<string> my_set;
    char buf[10];

    clock_t time_start = clock();
    cout << "输入元素:" << endl;
    for (long i = 0; i < value; ++i) {
        long tmp = rand();// 输入元素为无序
        snprintf(buf, 10, "%ld", tmp);
        cout << tmp << endl;
        try {
            my_set.insert(string(buf));// c_str-->string 因为需要排序，所以set的插要慢一些
        } catch(exception& p) {
            cout << "i = " << i << p.what() << endl;
            abort();// 异常退出
        }
    }

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "set.size() = " << my_set.size() << endl;
    cout << "set.max_size() = " << my_set.max_size() << endl;

    // 遍历--输出变有序
    cout << "set遍历输出" << endl;
    for (auto it = my_set.begin(); it != my_set.end(); ++it)
        cout << *it << endl;

    string target = getATargetString();
    {
        time_start = clock();
        set<string>::iterator p_item = find(my_set.begin(), my_set.end(), target);// C标准库函数
        cout << "std::find(), milli-seconds: " << (clock() - time_start) << endl;
        if (p_item != my_set.end())
            cout << "found, " << *p_item << endl;
        else
            cout << "not found" << endl;
    }

    {
        time_start = clock();
        auto p_item = my_set.find(target);// STL set自带方法
        cout << "my_set.find(), milli-seconds: " << (clock() - time_start) << endl;
        if (p_item != my_set.end())
            cout << "found, " << *p_item << endl;
        else
            cout << "not found" << endl;
    }
}

#include <map>
void testMap(long& value)
{
    cout << "\ntest_map().......... \n";

    map<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    cout << "输入数据: " << endl;
    for(long i=0; i< value; ++i)
    {
        long tmp = rand();
        cout << tmp << endl;
        snprintf(buf, 10, "%ld", tmp);
        try {
            c[i] = string(buf);// 可以使用[]进行赋值
        }
        catch(exception& p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds : " << (clock()-timeStart) << endl;
    cout << "map.size()= " << c.size() << endl;
    cout << "map.max_size()= " << c.max_size() << endl;		//178956970

    // map遍历--没有针对data做排序
    cout << "map遍历" << endl;
    for (auto it = c.begin(); it != c.end(); ++it)
        cout << it->first << " " << it->second << endl;
//        cout << (*it).first << " " << (*it).second << endl;

//    long target = get_a_target_long();
//    timeStart = clock();
//    auto pItem = c.find(target);
//    cout << "c.find(), milli-seconds : " << (clock()-timeStart) << endl;
//    if (pItem != c.end())
//        cout << "found, value=" << (*pItem).second << endl;
//    else
//        cout << "not found! " << endl;

    c.clear();
}

#include <unordered_map>
void testUnorderedMap(long& value) {
    cout << "test unordered_map" << endl;

    unordered_map<long, string> umap;
    char buf[10];

    clock_t time_start = clock();
    for (long i = 0; i < value; i++) {
        snprintf(buf, 10, "%d", rand());
        try {
            umap.insert({i,string(buf)});
//            umap[i] = string(buf);
        } catch(exception& p) {
            cout << "i = " << i << p.what() << endl;
            abort();
        }
    }

    cout << "milli-seconds: " << (clock() - time_start) << endl;
    cout << "unordered_map.size() = " << umap.size() << endl;
    cout << "unordered_map.max_size() = " << umap.max_size() << endl;
    cout << "unordered_map.bucket_count() = " << umap.bucket_count() << endl;
    cout << "unordered_map.max_bucket_count() = " << umap.max_bucket_count() << endl;

    for (unsigned i = 0; i < umap.bucket_count(); ++i)
        cout << "bucket #" << i << " has " << umap.bucket_size(i) << " elements" << endl;
    
    // unordered_map遍历
    cout << "遍历unordered_map" << endl;
    for (auto it = umap.begin(); it != umap.end(); ++it)
        cout << it->first << " " << it->second << endl;

}

#include <set>
#include <functional>
// 测试红黑树
void testRbTree() {
    cout << "test Rb_tree......" << endl;

    _Rb_tree<int, int, _Identity<int>, less<int>> itree;
    cout << "sizeof(itree): " << sizeof(itree) << endl;
    cout << "itree.empty(): " << itree.empty() << endl;
    cout << "itree.size(): " << itree.size() << endl;


    // 插入元素
    // insert_unique()测试--元素不可重复
    itree._M_insert_unique(3);
    itree._M_insert_unique(8);
    itree._M_insert_unique(5);
    itree._M_insert_unique(9);
    itree._M_insert_unique(13);
    itree._M_insert_unique(5);// 插入重复元素5--不会报错,也不会插入
    cout << "itree.empty(): " << itree.empty() << endl;
    cout << "itree.size(): " << itree.size() << endl;
    cout << "itree.count(5): " << itree.count(5) << endl;// 统计元素5的个数

    // insert_equal()测试--元素可重复
    itree._M_insert_equal(5);
    itree._M_insert_equal(5);
    cout << "itree.size(): " << itree.size() << endl;
    cout << "itree.count(5): " << itree.count(5) << endl;
}

// 测试各种容器类对象的大小
void testComponentSize() {
    cout << "test components size..." << endl;

    cout << "sizeof(list<int>): " << sizeof(list<int>) << endl;
    cout << "sizeof(list<int>::iterator): " << sizeof(list<int>::iterator) << endl;
    cout << "sizeof(vector<int>): " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<int>::iterator): " << sizeof(vector<int>::iterator) << endl;
}

int main() {
    int choice;
    long value;

    cout << "select: ";
    cin >> choice;

    if (choice != 1 && choice != 0) {
        cout << "how many elements: ";
        cin >> value;
    }

    switch (choice) {
        case 0:
            testComponentSize();
            break;
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
        case 5:
            testRbTree();
            break;
        case 6:
            testSet(value);
            break;
        case 7:
            testMap(value);
            break;
        case 8:
            testUnorderedMap(value);
            break;
    }
}