#include <iostream>
void swap1 (int a ,int b ) ;
void swap2 (int &a ,int &b ) ;
void swap3 (int &a ,int &b ) ;

int main() {

    int x = 0;
    int y = 1;
    std::cout << " x = " << x << "  y = " << y << " \n" ;
    swap1 (x ,  y ) ;std::cout << " x = " << x << "  y = " << y << " \n" ;
    swap2 (x ,  y ) ;std::cout << " x = " << x << "  y = " << y << " \n" ;
    swap3 (x ,  y ) ;std::cout << " x = " << x << "  y = " << y << " \n" ;
    return 0;
}

void swap1 (int a ,int b) {
    int temp = a ;
    a = b ;
    b = temp ;
}

void swap2 (int &a ,int &b)  {
    int temp = a ;
    a = b ;
    b = temp ;
}
void swap3 (int & a ,int &b)  {
    int temp = b ;
    a = b ;
    a = temp ;
}