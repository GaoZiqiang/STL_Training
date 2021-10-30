#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void printVec(int val) {
    cout << val << " ";
}

// 基本数据类型
void test01() {
    // 容器
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    // 迭代器
    vector<int>::iterator p_begin = vec.begin();
    vector<int>::iterator p_end = vec.end();

    // 算法
    for_each(p_begin, p_end, printVec);// printVec为回调函数
}

class Person {
public:
    Person(int _id, int _age) : id(_id), age(_age) {}
    static void show(Person& per) {cout << per.id << " " << per.age << endl;}

private:
    int id;
    int age;
};
// 自定义数据类型
void test02() {
    // 创建容器
    vector<Person> vec;
    Person p1(1, 20), p2(2, 21), p3(3, 25);
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);

    // 自定义遍历
//    for (vector<Person>::iterator it = vec.begin(); it != vec.end(); it++) {
////        cout << (*it).id << " " << (*it).age << endl;
//        it->show();
//    }

    for_each(vec.begin(), vec.end(), Person::show);
}

int main() {
//    test01();
    test02();
}