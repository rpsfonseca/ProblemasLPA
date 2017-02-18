#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <array>

int n;
int m;
int max;
int matrix[500][500];
int smallest;
int actual;
int hours_spent;
int proficiency;
int sequences[12][4][2];

using namespace std;

int main(int argc, char** argv) {

    int aux, aux1, aux2, aux3, sum, max_best, i_aux;
    string score1;

    hours_spent = 0;
    proficiency = 0;
    sum = 0;
    max_best = 0;

    cin >> n;
    cin >> m;

    int seq[n];

    for (int i = 0; i < (n*m); i++) {
        scanf("%d %d %d\n", &aux1, &aux2, &aux3);
        matrix[aux1-1][aux2-1] = aux3;
    }

    for (int t = 0; t < n; t++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                aux = matrix[i][j];
                if (aux > max_best) {
                    max_best = aux;
                    i_aux = i;
                }
            }
            int aux_aux[2] = {i_aux,max_best};
            max_best = 0;
            sequences[t][] = (aux_aux);
        }
    }

    cout << max_best << endl;

    return 0;
}
