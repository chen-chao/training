/*
  编程题＃3：运算符判定

  来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

  注意： 总时间限制: 1000ms 内存限制: 65536kB

  描述

  两个整数 a 和 b 运算后得到结果 c。表示为：a ? b = c，其中，？可能是加法 +，减法 -，乘法 *，整除 / 或 取余 %。请根据输入的 a,b,c 的值，确定运算符。如果某种运算成立，则输出相应的运算符，如果任何运算都不成立，则输出 error.

  例如：

  输入：

  3,4,5

  输出：

  error

  若输入：

  3,4,3

  则输出：

  %

  输入

  a b和 c 的值在意行内输入，以逗号间隔

  输出

  五个运算符之一或 error

  样例输入
  6,7,13
  样例输出
  +

*/

#include <iostream>

int possible_res(int a, int b, int op){
        int res;
        switch (op) {
        case 0:
                res = a+b;
                break;
        case 1:
                res = a-b;
                break;
        case 2:
                res = a*b;
                break;
        case 3:
                res = a/b;
                break;
        case 4:
                res = a%b;
                break;
        }
        return res;
}

int guess_op(int a, int b, int c){
        char ops[] = "+-*/%";
        int i=0;
        while (i<5 && possible_res(a, b, i)!=c ){
                i++;
        }
        if (i==5){
                std::cout << "error" << std::endl;
                return -1;
        }
        std::cout << ops[i] << std::endl;
        return 0;
}

int main(){
        char sep;
        int a, b, c;
        std::cin >> a >> sep >> b >> sep >> c;
        guess_op(a, b, c);
        return 0;
}
