// 细菌分类
// 将繁殖率排序后 Amax, A1, A2, ..., Amin, Bmax, ..., Bmin
// 必有 Amax-Amin< Amin-Bmax > Bmax-Bmin
#include <iostream>
using namespace std;

int size;
float *rate = nullptr;
int *tag = nullptr;

// int size=5;
// float rate[5]={345.6, 564.4, 456.6, 11.7, 11.1};
// int tag[5] = {1,2,3,4,5};

// 2Amin>Amax+Bmax
// 2Bmax<Amin+Bmin
bool check(int pos){
        if (*(rate+pos)*2<*(rate+pos+1)+*(rate)){
                return false;
        }
        if (*(rate+pos+1)*2>*(rate+pos)+*(rate+size-1)){
                return false;
        }
        return true;
}

void print(int pos){
        cout << pos+1 << endl;
        for (int i=pos; i>=0; i--){
                cout << tag[i] << endl;
        }
        cout << size-pos-1 << endl;
        for (int i=size-1; i>pos; i--){
                cout << tag[i] << endl;
        }
}

template <class some_pointer>
void swap(some_pointer *p, int i, int j){
        int tmp;
        tmp = p[i];
        p[i] = p[j];
        p[j] = tmp;
}

void sort(){
        for (int i=0; i<size; i++){
                for (int j=i+1; j<size; j++){
                        if (rate[i]<*(rate+j)){
                                swap(rate, i, j);
                                swap(tag, i, j);
                        }
                }
        }
}

int main(){
        cin >> size;
        if (size < 4){
                return -1;
        }
        rate = new float[size];
        tag = new int[size];
        
        int before, after;
        for (int i=0; i<size; i++){
                cin >> tag[i];
                cin >> before >> after;
                rate[i] = after*1.0/before;
        }

        sort();
        int pos=0;
        bool not_found=true;
        while (not_found && pos<size-2){
                not_found = not (check(pos++));
        }
        if (not_found){return -1;}
        print(pos-1);
        return 0;
}
