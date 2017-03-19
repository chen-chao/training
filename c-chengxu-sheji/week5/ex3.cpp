/*编程题＃3：寻找山顶

来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述

在一个m×n的山地上，已知每个地块的平均高程，请求出所有山顶所在的地块（所谓山顶，就是其地块平均高程不比其上下左右相邻的四个地块每个地块的平均高程小的地方)。

输入

第一行是两个整数，表示山地的长m（5≤m≤20）和宽n（5≤n≤20）。

其后m行为一个m×n的整数矩阵，表示每个地块的平均高程。每行的整数间用一个空格分隔。

输出

输出所有上顶所在地块的位置。每行一个。按先m值从小到大，再n值从小到大的顺序输出。

样例输入
10 5
0 76 81 34 66
1 13 58 4 40
5 24 17 6 65
13 13 76 3 20
8 36 12 60 37
42 53 87 10 65
42 25 47 41 33
71 69 94 24 12
92 11 71 3 82
91 90 20 95 44
样例输出
0 2
0 4
2 1
2 4
3 0
3 2
4 3
5 2
5 4
7 2
8 0
8 4
9 3

Solution: 对矩阵进行右，下遍历相邻元素之差，若差为4，即为山顶。
*/

#include <iostream>
#include <vector>


void print(int **p, size_t dim1, size_t dim2){
        for (size_t i=0; i<dim1; i++){
                for (size_t j=0; j<dim2; j++){
                        std::cout << p[i][j] << ' ';
                }
                std::cout << std::endl;
        }
}

int find_peak(int **mountain, size_t dim1, size_t dim2, std::vector<int> &peakx, std::vector<int> &peaky){
        int x, y;
        int **height_delta;
        int dirnx[2]={1, 0};
        int dirny[2]={0, 1};
        height_delta = new int*[dim1+2];
        for (size_t i=0; i<=dim1+1; i++){
                height_delta[i] = new int[dim2+2];
                for (size_t j=0; j<=dim2+1; j++){
                        height_delta[i][j] = 0;
                }
        }

        
        for (size_t i=0; i<=dim1; i++){
                 for (size_t j=0; j<=dim2; j++){
                         // std::cout << i << ',' << j << std::endl;
                         for (size_t d=0; d<2; d++){
                                 x = i+dirnx[d];
                                 y = j+dirny[d];
                                 if (mountain[x][y]>mountain[i][j] ){
                                         height_delta[i][j]--;
                                         height_delta[x][y]++;
                                 } else {
                                         height_delta[i][j]++;
                                         height_delta[x][y]--;
                                 }
                         }
                         // print(height_delta, dim1+1, dim2+1);                         
                         if (height_delta[i][j]==4){
                                 peakx.push_back(i);
                                 peaky.push_back(j);
                         }
                 }
        }
        return 0;
}



int main(){
        size_t dim1, dim2;
        std::cin >> dim1 >> dim2;
        int **mountain;
        mountain = new int*[dim1+2];
        for (size_t i=0; i<dim1+2; i++){
                mountain[i] = new int[dim2+2];
        }
        for (size_t i=1; i<=dim1; i++){
                for (size_t j=1; j<=dim2; j++){
                        std::cin >> mountain[i][j];
                }
        }
        for (size_t j=0; j<dim2+2; j++){
                mountain[0][j] = -1;
                mountain[dim1+1][j] = -1;
        }

        for (size_t i=0; i<dim1+2; i++){
                mountain[i][0] = -1;
                mountain[i][dim2+1] = -1;
        }

        // print(mountain, dim1+2, dim2+2);

        std::vector<int> peakx, peaky;
        find_peak(mountain, dim1, dim2, peakx, peaky);
        for (size_t i=0; i<peakx.size(); i++){
                std::cout << peakx[i]-1 << ' ' << peaky[i]-1 << std::endl;
        }
        return 0;
}
