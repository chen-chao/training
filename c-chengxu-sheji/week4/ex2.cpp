/*二维数组右上左下遍历

  描述
  给定一个row行col列的整数数组array，要求从array[0][0]元素开始，按从右上到左下的对角线顺序遍历整个数组。

  输入
  输入的第一行上有两个整数，依次为row和col。
  余下有row行，每行包含col个整数，构成一个二维整数数组。
  （注：输入的row和col保证0 < row < 100, 0 < col < 100）

  输出
  按遍历顺序输出每个整数。每个整数占一行。
*/

#include <iostream>

int walk(int **p, int rowNumber, int columnNumber){
        int column=0, sum=0;
        while (sum<rowNumber+columnNumber-1){
                for (int i=column; i>=0&&(sum-i<rowNumber); i--){
                        // std::cout << "i: " << i << ", sum: " << sum << std::endl;
                        std::cout << p[sum-i][i] << std::endl;
                }
                if (column<columnNumber-1){
                        column++;
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
