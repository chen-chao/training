// 单词翻转
#include <iostream>
#include <string>

void reverse_show(std::string s, int i, int j){
        if (i==j){
                std::cout << s[i];
                return;
        }
        if (j>i){
                std::cout << s[j];
                reverse_show(s, i+1, j-1);
                std::cout << s[i];
        }
        
}


int main(){
        std::string line;
        getline(std::cin, line);
        // std::string line=" abcdef r.";
        int wordBegin = 0;
        auto len = line.size();
        unsigned i=0;
        while (i<len ){
                while (i<len && line[i]==' '){
                        std::cout << " ";
                        i++;
                }
                wordBegin = i;
                while (i<len && line[++i]!=' '){}
                reverse_show(line, wordBegin, i-1);
        }
        std::cout << std::endl;
        return 0;
}
