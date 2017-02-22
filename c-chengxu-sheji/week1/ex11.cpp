#include <iostream>
using namespace std;

int main(){
        int num;
        cin >> num;
        int value; 
        for (int i=0; i<num; i++){
                cin >> value;
                if (value==i){
                        cout << value << endl;
                        return 0;
                }
        }
        cout << "N"<<endl;
        return -1;
}

