/*编程题＃2： 配对碱基链

来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述

脱氧核糖核酸（DNA）由两条互补的碱基链以双螺旋的方式结合而成。而构成DNA的碱基共有4种，分别为腺瞟呤（A）、鸟嘌呤（G）、胸腺嘧啶（T）和胞嘧啶（C）。我们知道，在两条互补碱基链的对应位置上，腺瞟呤总是和胸腺嘧啶配对，鸟嘌呤总是和胞嘧啶配对。你的任务就是根据一条单链上的碱基序列，给出对应的互补链上的碱基序列。

输入

第一行是一个正整数n，表明共有n条要求解的碱基链。

以下共有n行，每行用一个字符串表示一条碱基链。这个字符串只含有大写字母A、T、G、C，分别表示腺瞟呤、胸腺嘧啶、鸟嘌呤和胞嘧啶。每条碱基链的长度都不超过255。

输出

共有n行，每行为一个只含有大写字母A、T、G、C的字符串。分别为与输入的各碱基链互补的碱基链。

*/

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
int complement(char c){
        switch (c){
        case 'A':
                std::cout << 'T';
                break;
        case 'T':
                std::cout << 'A';
                break;
        case 'G':
                std::cout << 'C';
                break;
        case 'C':
                std::cout << 'G';
                break;
                 
        }
        return 0;
}

int gene_complement(string s){
        for (auto c: s){
                complement(c);
        }
        std::cout << std::endl;
        return 0;
}

int main(){
        int number;
        vector<string> stringlist;
        std::cin >> number;
        string s;
        // to escape the newline tag after std::cin>>number
        getline(std::cin, s);
        for (int i=0; i<number;i++){
                getline(std::cin, s);
                stringlist.push_back(s);
        }
        std::cout << std::endl;
        for (int i=0; i<number; i++){
                gene_complement(stringlist[i]);
        }
        std::cout << std::endl;
        return 0;
}
