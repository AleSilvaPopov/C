#include <iostream>
using namespace std;

int salto(int n);
int sobrevivente(int n, int k);

int main(){
    int N;

    while(true){
        cin >> N;
        if(N == 0){
            break;
        }
        cout  << salto(N) << endl;
    }
    return 0;
}

int sobrevivente(int n, int k){
    if(n == 1){
        return 0;
    }
    return (sobrevivente(n - 1, k) + k) % n;
}

int salto(int n){
    for(int k = 1; k < n; k++) {
        cout << sobrevivente(n, k) << endl;
        if(sobrevivente(n, k) + 1 == 13){
            return k;
        }
    }
    return -1;
}