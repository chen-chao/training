// 流感传染
// 问题 定义全局动态数组 数组边界溢出 

#include <iostream>
using namespace std;
size_t size;
int *dorm = nullptr;
int *ill_pos = nullptr;
int ill_count = 0;

int coord(int x, int y){
        return x*size+y;
}

void set_healthy(int x, int y){
        dorm[coord(x,y) ] = 0;
}

void set_ill(int x, int y){
        dorm[coord(x,y) ] = 1;
}

void set_vacant(int x, int y){
        dorm[coord(x,y) ] = 2;
}

bool is_ill(int x, int y){
        if (dorm[coord(x, y) ]==1 ){
                return true;
        }
        return false;
}

bool is_healthy(int x, int y){
        if (dorm[coord(x, y) ]==0 ){
                return true;
        }
        return false;
}

bool is_vacant(int x, int y){
        if (dorm[coord(x, y) ]==2 ){
                return true;
        }
        return false;
}

void set_state(int x, int y, char c){
        if (c=='.'){
                set_healthy(x, y);
        }
        if (c=='@'){
                set_ill(x, y);
                ill_pos[2*ill_count] = x;
                ill_pos[2*ill_count+1] = y;
                ill_count++;

        }
        if (c=='#'){
                set_vacant(x, y);
         }
}


void show(){
        cout << "---------------------"<<endl;
        for (int i=0; i<size; i++){
                for (int j=0; j<size; j++){
                        cout << *(dorm + coord(i, j) );
                }
                cout << endl;
        }
}


// avoid searching backward
// right, left, upward, downward
int x_offset[4] = {-1, 1, 0, 0};
int y_offset[4] = {0, 0 , -1, 1};
int baned_direction[4] = {1, 0, 3, 2};

void contaminate(int x, int y, int days, int direction){
        if (days==0 || x<0 || x>size-1 || y<0 || y>size-1 || is_vacant(x, y) ){
                return ;
        }

        set_ill(x, y);
        for (int i=0; i<4; i++){
                if (i==direction) {continue;}
                contaminate(x+x_offset[i], y+y_offset[i], days-1, baned_direction[i] );
        }

}

int main(){
        cin >> size;
        dorm = new int[size*size];
        ill_pos = new int[size*2];
        char c;
        for (int i=0; i<size;i++ ){
                for (int j=0; j<size; j++){
                        cin >> c;
                        set_state(i, j, c);
                }
        }


        // show();
        int days;
        cin >> days;

        for (int i=0; i<ill_count; i++){
                contaminate(ill_pos[2*i], ill_pos[2*i+1], days, -1);
                // show();
        }

        int ill_number=0;
        for (int i=0; i<size; i++){
                for (int j=0; j<size; j++){
                        if (is_ill(i, j) ){
                                ill_number++;
                        }
                }
        }
        cout << ill_number <<endl;
        return 0;
}
