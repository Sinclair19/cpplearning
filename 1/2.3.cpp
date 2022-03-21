#include<iostream>

int main(){
    using std::cin;
    using std::cout;
    using std::endl;
    unsigned u = 10, u2 = 42;
    cout<<u2-2<<endl;
    cout<<u-u2<<endl;
    
    int i = 10, i2 = 42;
    cout<<i2-i<<endl;
    cout<<i-i2<<endl;
    cout<<i-u<<endl;
    cout<<u-i<<endl;

}

