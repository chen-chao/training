/*

  编程题＃5：走出迷宫

  来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

  注意： 总时间限制: 1000ms 内存限制: 65536kB

  描述

  当你站在一个迷宫里的时候，往往会被错综复杂的道路弄得失去方向感，如果你能得到迷宫地图，事情就会变得非常简单。

  假设你已经得到了一个n*m的迷宫的图纸，请你找出从起点到出口的最短路。

  输入

  第一行是两个整数n和m(1 <= n,m <= 100)，表示迷宫的行数和列数。

  接下来n行，每行一个长为m的字符串，表示整个迷宫的布局。字符'.'表示空地，'#'表示墙，'S'表示起点,'T'表示出口。

  输出

  输出从起点到出口最少需要走的步数。(你不能起出迷宫外)

  样例输入

  3 3
  S#T
  .#.
  ...

  样例输出
  6
*/

#include <iostream>
#include <vector>

int **maze = nullptr;
int **steps = nullptr;
int length, width;

struct coord{
public:
        int x, y;
        coord operator+(coord other){
                int xx = x+other.x;
                int yy = y+other.y;
                coord res = {xx, yy};
                return res;
        }
        
        coord operator-(coord other){
                int xx = x-other.x;
                int yy = y-other.y;
                coord res = {xx, yy};
                return res;
        }
        
        bool valid(){
                return (x>=0 && x<length && y>=0 && y<width);
        }
};

typedef std::vector<coord> coordvec;

int init(coord &start, coord &end){
        maze = new int*[length];
        steps = new int*[length];
        char c;
        for (int i=0; i<length; i++){
                maze[i] = new int[width];
                steps[i] = new int[width];
                for (int j=0; j<width; j++){
                        std::cin >> c;
                        steps[i][j] = -1;
                        switch (c){
                        case '#':
                                maze[i][j] = 1;
                                break;
                        case '.':
                                maze[i][j] = 0;
                                break;
                        case 'S':
                                maze[i][j] = 0;
                                start.x = i;
                                start.y = j;
                                steps[i][j] = 0;
                                break;
                        case 'T':
                                maze[i][j] = 0;
                                end.x = i;
                                end.y = j;
                                break;
                        }
                }
        }
        return 0;
}

int del(){
        for (int i=0; i<length; i++){
                for (int j=0; j<width; j++){
                        delete[] maze[i];
                        delete[] steps[i];
                }
        }
        maze = nullptr;
        steps = nullptr;
        return 0;
}

coord direct[4]={{1,0}, {-1,0}, {0,-1}, {0,1} };
int walk(coord xy){
        coordvec cvec;
        coord cd;
        for (int i=0; i<4; i++){
                if (not xy.valid() ){continue; }
                cd = xy+direct[i];
                if (cd.valid() &&  maze[cd.x][cd.y]!=-1 && steps[cd.x][cd.y]==-1){
                        cvec.push_back(cd);
                        steps[cd.x][cd.y] = steps[xy.x][xy.y]+1;
                }
        }
        for (auto &cd: cvec){
                walk(cd);
        }
        return 0;
}

int main(){
        std::cin >> length >> width;
        coord start, end;
        init(start, end);
        walk(start);
        std::cout << steps[end.x][end.y] << std::endl;
        del();
        return 0;
}

