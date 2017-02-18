#include <iostream>
#include <stdio.h>
#include <math.h>
#define N 25
#define K 7
#define TWO_K 128
using namespace std;

double best = 0;
int n, k, two_k_lines;
int containers[N], group_vals[N][K];
double fit_vals[N][TWO_K], bound_aux_values[N][TWO_K][K+1];

double powerOfTwo(int exp) {
    double pow = 1;
    for (int i = 0; i < exp; i++) {
        pow *= 2;
    }
    return pow;
}

double bound_calculator(int used) {
    int aux[N], aux2[N];

    for (int i = 0; i < n; i++) {
        aux2[i] = 0;
        int j;
        for (j = 0; j < k; j++) {
            if (group_vals[i][j] >= used) {
                break;
            }
            aux2[i] += containers[group_vals[i][j]] * powerOfTwo(k-1-j);
        }
        aux[i] = j;
    }
    double bound = 0;
    for (int i = 0; i < n; i++) {
        bound += bound_aux_values[i][aux2[i]][k-aux[i]];
    }

    return bound;
}

void worker(int used) {
    if (used >= n) {
        double bound = bound_calculator(used);

        if(bound > best) {
            best = bound;
        }

        return;
    }

    double bound = bound_calculator(used);
    if (bound > best) {
        containers[used] = 0;
        worker(used+1);

        if (bound > best) {
            containers[used] = 1;
            worker(used+1);

        }
    }
}

int main() {

    scanf("%d %d", &n, &k);
    k = k + 1;
    two_k_lines = powerOfTwo(k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%d", &group_vals[i][j]);
        }
    }

    for (int l = 0; l < n; l++) {
        for (int i = 0; i < two_k_lines; i++) {
            scanf("%lf", &fit_vals[l][i]);
        }
        for (int i = 0; i < two_k_lines; i++) {
            bound_aux_values[l][i][0] = fit_vals[l][i];
        }

        int offset = 1, j_offset = 2;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < two_k_lines; j+=j_offset) {
                double max_fit_val = max(bound_aux_values[l][j][i], bound_aux_values[l][j+offset][i]);

                for (int m = 0; m < j_offset; m++) {
                    bound_aux_values[l][j+m][i+1] = max_fit_val;
                    bound_aux_values[l][j+offset+m][i+1] = max_fit_val;
                }

            }
            offset *= 2;
            j_offset *= 2;
        }
    }

    for (int i1 = 0; i1 < n; i1++) {
        for (int i = 0; i < two_k_lines; i++) {
            for (int j = 0; j < k+1; j++) {
                printf("%8.6f ", bound_aux_values[i1][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    worker(0);
    printf("%.6f\n", best);



    return 0;
}