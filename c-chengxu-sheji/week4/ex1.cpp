/* 计算矩阵边缘元素之和

   描述
   输入一个整数矩阵，计算位于矩阵边缘的元素之和。所谓矩阵边缘的元素，就是第一行和最后一行的元素以及第一列和最后一列的元素。

   输入
   第一行为整数k，表示有k组数据。
   每组数据有多行组成，表示一个矩阵：
   第一行分别为矩阵的行数m和列数n（m < 100，n < 100），两者之间以空格分隔。
   接下来输入的m行数据中，每行包含n个整数，整数之间以空格作为间隔。

   输出
   输出对应矩阵的边缘元素和，一个一行。
*/

#include <iostream>
#include <vector>

int sum_boundary(int **p, size_t size1, size_t size2){
        int res = 0;
        for (size_t i=0; i<size2; i++){
                res += p[0][i];
                res += p[size1-1][i];
        }
        for (size_t i=1; i<size1-1; i++){
                res += p[i][0];
                res += p[i][size2-1];
        }
        return res;
}

int main(){
        int caseNumber;
        std::vector <int> res;
        std::cin >> caseNumber;
        size_t length, width;
        for (int i=0; i<caseNumber; i++){
                int **p=nullptr;

                std::cin>> length>>width;
                p = new int* [length];
                for (size_t j=0; j<length; j++){
                        p[j] = new int[width];
                }

                for (size_t j=0; j<length;j++){
                        for (size_t k=0; k<width; k++){
                                std::cin >> p[j][k];
                        }
                }
                res.push_back(sum_boundary(p,length,width));
                for (size_t i=0; i<length; i++){
                        delete[] p[i];
                }
                delete[] p;
        }
        for (auto v: res){
                std::cout << v << std::endl;
        }
        
        
}
