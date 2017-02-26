// 排队游戏
#include <iostream>
#include <string>
#include <vector>

void get_match(std::string line, size_t len, std::vector<int> leftBraces, size_t rightPos){
        if (rightPos > len-1){return ;}
        if (line[leftBraces[0] ] != line[rightPos]){
                std::cout << leftBraces[leftBraces.size()-1] << " " << rightPos << std::endl;
                leftBraces.pop_back();
        } else {
                leftBraces.push_back(rightPos);
        }
        get_match(line, len, leftBraces, ++rightPos);
}

int main(){
        std::string line;
        getline(std::cin, line);
        std::vector<int> leftBraces;
        leftBraces.push_back(0);
        size_t len=line.size();
        get_match(line, len, leftBraces, 1 );
}
