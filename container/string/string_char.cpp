#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;
// string和str互转
void test() {
    // string to cstr
    string str = "itcast";
    const char* cstr = str.c_str();

    cout << "type of str " << typeid(str).name() << endl;
    cout << "type of cstr " << typeid(cstr).name() << endl;

    // cstr to string
    char* s = "itcast";
    string sstr = s;
}

// []和at方法比较
void test01() {
    string s1 = "gaoziqiang";
    try {
        // []访问越界不会报异常
//        cout << s1[100] << endl;
        cout << s1.at(100) << endl;
    }
    catch(...) {
        cout << "越界!" << endl;
    }
}

// 拼接操作
void test02() {
    // 1 重载+=操作符
    string s = "abcd";
    string s2 = "1234";
    s += "abcd";// 拼接char*
    s += s2;// 拼接string
    s += '!';// 拼接char
    cout << s << endl;

    // 2 重载+操作符
    string s3 = s + s2;
    cout << s3 << endl;
    // append方法
    s.append(s2);
    cout << s << endl;
}

// 查找操作
void test03() {
    string s = "abcdfdgfd";
    int pos = s.find("fd");// 第一次出现的位置--从前往后
    cout << pos << endl;
    pos = s.rfind("fd");// 最后一次出现的位置
    cout << pos << endl;
}

// 替换操作
void test04() {
    // 替换从pos开始n个字符为字符串str
    string s = "abcdef";
    s.replace(0,4,"111");
    cout << s << endl;
}

// 比较操作
void test05() {
    string s1 = "abcd";
    string s2 = "abce";

    if (s1.compare(s2) == 0)
        cout << "字符串相等" << endl;
    else
        cout << "字符串不相等" << endl;
}

// 取子串操作
void test06() {
    string s = "abcd";
    string sub_str = s.substr(1, 3);
    cout << sub_str << endl;
}

// 插入和删除
void test07() {
    string s = "abcd";
    s.insert(2, "111");
    cout  << s << endl;

    s.erase(0,2);
    cout << s << endl;
}
int main() {
    test07();
}