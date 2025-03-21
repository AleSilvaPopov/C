#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, x, p, m, g;
    string tamanho;
    int totalmuros = 1;

    cin >> n >> x; 
    cin >> tamanho; 
    cin >> p >> m >> g;

    int alturamuro = x;

    for (int i = 0; i < n; i++) {
        int tamanhotitan;

        if (tamanho[i] == 'P') {
            tamanhotitan = p;
        } else if (tamanho[i] == 'M') {
            tamanhotitan = m;
        } else {
            tamanhotitan = g;
        }

        if (tamanhotitan > alturamuro) {
            totalmuros += (tamanhotitan - 1) / x; 
            alturamuro = x - (tamanhotitan % x);
            
            if (alturamuro == x) {
                alturamuro = 0;
            }
        } else {
            alturamuro -= tamanhotitan;
        }
    }
    cout << totalmuros << endl;

    return 0;
}