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
