#include<iostream>
#include<vector>
#include<iterator>
using namespace std;

int main(){
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    vector<int> num(begin(a),end(a));
    for(auto a:num){
        if(a%2 != 0){
            a *=2;
        }
        cout<<a<< " ";
    }
    cout<<endl;
    
    return 0;
}