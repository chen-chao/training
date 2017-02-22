#include <iostream>
#include <algorithm>
using namespace std;

int fackanswer[16] = {3,1,0,4,  2,4,3,1,   0,3,0,4,  1,3,4,2};

void show(int *p, int length ){
        for (int i=0; i<length; i++){
                cout << *(p+i) << endl;
        }
}

int check(int length, int *s1, int *s2){
        int same=0;
        for (int i=0; i<length; i++){
                if (*(s1+i)==0)
                        continue;
                if (*(s1+i)==*(s2+i) )
                        same++;
        }
        return same;
}

int main(){
        int length = 4;
        int candidate[4]={4,3,2,1};

        do{
                // cout << "This is show of candidates."<<endl;
                // show(candidate, length);
                // cout << "-------------"<<endl;
                bool answerFound = true;
                for (int i=0; i<length; i++){
                     if (check(length, candidate, fackanswer+i*length) !=1 ){
                             answerFound = false;
                             break;
                         }
                }
                if (answerFound){
                        // cout << "Found" << endl;
                        show(candidate, length);
                        // cout << "-------------" << endl;
                        return 0;
                }
        
        } while(prev_permutation(candidate, candidate+length) );
        return -1;
}

