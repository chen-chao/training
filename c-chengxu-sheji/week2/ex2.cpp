// 角谷猜想
#include <iostream>

void process(unsigned number){
        if (number==1){
                std::cout << "END" << std::endl;
                return ;
        }
        if (number %2==0){
                std::cout << number;
                number /=2;
                std::cout << "/2=" << number<< std::endl;
                process(number);
        } else {
                std::cout << number;
                number = number*3+1;
                std::cout << "*3+1=" << number << std::endl;
                process(number);
        }
        
}

int main(){
        int number;
        std::cin >> number;
        process(number);
        return 0;
}
