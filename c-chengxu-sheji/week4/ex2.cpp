#include <iostream>

int walk(int **p, int rowNumber, int columnNumber){
        int row=0, sum=0;
        while (sum<rowNumber+columnNumber-1){
                for (int i=row; i>=0&&(sum-i<columnNumber); i--){
                        // std::cout << "i: " << i << ", sum: " << sum << std::endl;
                        std::cout << p[i][sum-i] << std::endl;
                }
                if (row<rowNumber-1){
                        row++;
                }
                sum++;
        }
        return 0;
}

int main(){
        int rowNumber, columnNumber;
        std::cin >> rowNumber >> columnNumber;
        int **p = nullptr;
        p = new int*[rowNumber];
        for (int i=0; i<rowNumber; i++){
                p[i] = new int[columnNumber];
        }
        for (int i=0; i<rowNumber; i++){
                for (int j=0; j<columnNumber; j++){
                        std::cin >> p[i][j];
                }
        }
        walk(p, rowNumber, columnNumber);
        return 0;
}
