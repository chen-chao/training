// 查找未匹配括号
// int foo(string/char *s??, other_args){s++;} to iterate the whole string.
// int foo(string s, int pos, other_args) avoid explicit iterating over the index.
// dynamic char array or string to be modified for output.

#include <iostream>
#include <string>
#include <vector>

bool is_not_brace(char c){
        if (c=='(' or c==')'){
                return false;
        }
        return true;
}

bool is_left_brace(char c){
        if (c=='('){
                return true;
        }
        return false;
}

bool is_right_brace(char c){
        if (c==')'){
                return true;
        }
        return false;
}

int mismatch(const char *s, int *mismatchLeftBraceNum, char *output){
        // returns mismatch right parenthesis number
        // mismathchLeftNum indicates the mismatch left parenthesis number

        if ( *s=='\0'){
                return 0;
        }
        while ( *s!='\0' && is_not_brace( *s) ){
                *output=' ';
                output++;
                s++;
        }
        int num;
        
        if (is_left_brace( *s ) ){
                (*mismatchLeftBraceNum)++;
                num = mismatch(s+1, mismatchLeftBraceNum, output+1);
                if (num==0) {
                        *output='?';
                        return 0;
                } else {
                        *output='l';
                        return --num;
                }
        }
        if (is_right_brace( *s ) ){
                if (*mismatchLeftBraceNum<1){
                        *output='$';
                } else {
                        (*mismatchLeftBraceNum)--;
                        *output='r';
                }
                num = mismatch(s+1, mismatchLeftBraceNum, output+1);                
                return ++num;                
        }

        
}


int mismatch_right(std::string line, int len, int pos, int *mismatchLeftBraceNum, char *output){

        if (pos>=len){
                return 0;
        }

        while ( pos<len && is_not_brace(line[pos])){
                output[pos]=' ';
                pos++;
        }

        int num;

        if (is_left_brace(line[pos])){
                (*mismatchLeftBraceNum)++;
                num = mismatch_right(line, len, pos+1, mismatchLeftBraceNum, output);
                if (num==0) {
                        output[pos]='?';
                        return 0;
                } else {
                        output[pos]='l';
                        return --num;
                }
        }
        if (is_right_brace(line[pos])){
                if ((*mismatchLeftBraceNum)<1){
                        output[pos]='$';
                } else {
                        (*mismatchLeftBraceNum)--;
                        output[pos]='r';
                }
                num = mismatch_right(line, len, pos+1, mismatchLeftBraceNum, output);                
                return ++num;                
        }

 }

int main(){
        std::string line;
        getline(std::cin, line);
        // char line[100] = "5+(4*5)111)(7+8))";
        char *output=nullptr;

        std::cout << line << std::endl;
        int len= (int) line.size();
        output = new char[len];
        int mismatchLeftBraceNum = 0;

        mismatch_right(line, len, 0, &mismatchLeftBraceNum, output  );
        std::cout <<output << std::endl;
        const char *s=line.c_str();
        mismatch(s, &mismatchLeftBraceNum, output);
        std::cout<<output << std::endl;
        return 0;
}
