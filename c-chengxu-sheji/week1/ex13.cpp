/* 发票统计 */
#include <iostream>
#define PERSON 3
using namespace std;

char invoiceType[]="ABC";
float personTotal[PERSON];
float invoice[PERSON];
int stat(int count){
        char c;
        int value;
        int total = 0;
}
int stat(int person, int count){
        char c;
        float value;
        float total;
        
        for (int i=0; i<count; i++){
                cin >> c;
                cin >> value;
                total += value;
                if (c=='A')
                        invoice[0] += value;
                if (c=='B')
                        invoice[1] += value;
                if (c=='C')
                        invoice[2] += value;
        }
        personTotal[person] = total;
        
}
int main(){
        int person, count;
        for (int i=0; i<PERSON; i++){
                cin >> person;
                cin >> count;
                stat(person-1, count);
        }
        for (int i=0; i<PERSON; i++){
                printf("%d %.2f\n", i+1, personTotal[i]);
        }
        for (int i=0; i<PERSON; i++){
                printf("%c %.2f\n", invoiceType[i], invoice[i]);
        }
        return 0;
}  


