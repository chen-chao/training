/*
  编程题＃2：字符串中次数第2多的字母

  来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

  注意： 总时间限制: 1000ms 内存限制: 65536kB

  描述

  输入一串长度不超过500个符号的字符串，输出在串中出现第2多的英语字母(大小写字母认为相同)和次数（如果串中有其它符号，则忽略不考虑）。如果有多个字母的次数都是第2多，则按串中字母出现的顺序输出第1个。

  例 ab&dcAab&c9defgb

  这里，a 和 b都出现3次，c和d都出现2次，e、f 和 g 各出现1次，其中的符号&和9均忽略不考虑。因此，出现第2多的应该是 c 和 d，但是 d 开始出现的位置在 c 的前面，因此，输出为

  D+d:2

  (假定在字符串中，次数第2多的字母总存在)

  输入

  一个字符串

  输出

  大写字母+小写字母:个数

  样例输入
  ab&dcAab&c9defgb
  样例输出
  D+d:2
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

struct dict{
public:
        char c;
        int count=0;
        std::string show(){
                char upcase = std::toupper(c);
                char str[100];
                const char fmt[]="%c+%c:%d";
                std::sprintf(str, fmt, upcase, c, count);
                return str;
        }
};

typedef std::vector<dict> dict_vector;

bool is_letter(int c){
        if (c<'a' || c>'z'){
                return false;
        }
        return true;
}

int index(dict_vector dv, char c){
        int pos = 0;
        for (auto &d : dv){
                if (d.c==c){
                        return pos;
                }
                pos++;
        }
        return -1;
}

int count_str(std::string str, dict_vector &dv){
        int pos;
        for (auto const &c : str){
                if (not is_letter(c) ){
                        continue;
                }
                pos = index(dv, c);
                if (pos==-1){
                        dv.push_back(dict{c, 1} );
                } else {
                        dv[pos].count++;
                }
        }
        return 0;
}

int nth_letter(dict_vector dv, int len, int nth){
        int count=1;
        for (int i=0; i<len; i++){
                for (int j=0; j<len; j++){
                        if (i==j){
                                continue;
                        }
                        if (dv[i].count<dv[j].count){
                                count++;
                        }
                }
                if (count==nth){
                        std::cout << dv[i].show() << std::endl;
                        return 0;
                }
        }
        return -1;
}

int main(){
        std::string line;
        getline(std::cin, line);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        dict_vector dv;
        int res = count_str(line, dv);
        if (res!=0){
                std::cout << "count_str fails." << std::endl;
                return -1;
        }
        res = nth_letter(dv, dv.size(), 2);
        if (res!=0){
                std::cout << "nth_letter fails." << std::endl;
                return -2;
        }
        return 0;
}
