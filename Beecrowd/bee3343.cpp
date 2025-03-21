#include <iostream>
#include <string>


using namespace std;

int main() {
    int n, x, p, m, g;
    int totalmuros = 1;
    string tamanho;


    cin >> n >> x;
    cin >> tamanho;
    cin >> p >> m >> g;

    int alturamuro = x;

    for (int i = 0; i < n; i++) {
        int tamanhotitan;

        if (tamanho[i] == 'P') {
            tamanhotitan = p;
        } else if (tamanho[i] == 'M' ) {
            tamanhotitan = m;
        } else {
            tamanhotitan = g;
        }

        if (alturamuro >= tamanhotitan) {
            alturamuro -= tamanhotitan;
        } else {
            totalmuros++;
            alturamuro = x;
            alturamuro -= tamanhotitan;
        }
        if(alturamuro == 0) {
            totalmuros++;
            alturamuro = x;
        }
    }
    cout << totalmuros << endl;

    return 0;
}