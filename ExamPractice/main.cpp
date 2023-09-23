#include <iostream>
#include <iomanip>
#include <cctype>

int main() {
    int num,i, count;
    int n =2;

    for(num = 1;num<=n;num++){
        count = 0;
        for(i=2;i<=num/2;i++){
            if(num%i==0){
                count++;
                break;
            }
        }

        if(count==0 && num!= 1)
            std::cout << num << std::setw(3);
    }


    return 0;
}
