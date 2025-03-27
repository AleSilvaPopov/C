#include <iostream>

using namespace std;

int main(){
    int a, b;
    cin >> a >> b;

    int q, r;

    if(b != 0){
        q = a / b;
        r = a % b;
    }
    else{
        q = 0;
        r = 0;
    }

    cout << q << " " << r;

    return 0;
}