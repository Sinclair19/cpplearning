#include<iostream>
int main(){
    using std::cin;
    using std::cout;
    using std::endl;
    int n,a[110],i=0;
    int s1=0;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>a[i];
    }
    int k = 0;
    int max = 0;
    int s2 = 0;
    while(s1>=0&s1<n-1){
        if(a[s1]==0){
            break;       
        }
        s1 += a[s1];
        if(s1>=max){
            max = s1;
        }
        if(s2>=0&s2<n-1){
            s2 += a[s2];
            if(s2>=0&s2<n-1)
                s2 += a[s2];
        }
        k += 1;
        if(s1==s2){
            break;
        }
    }
    if(s1==n-1){
        cout<<"True"<<endl;
        cout<<k<<endl;
    }
    else{
        cout<<"False"<<endl;
        cout<<max<<endl;
    }
    return 0;
}