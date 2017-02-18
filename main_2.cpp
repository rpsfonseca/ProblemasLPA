#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <stdlib.h>

using namespace std;

bool checkInconsistency(int length, int scores[][2]) {
    int totalRounds = scores[length-1][0] + scores[length-1][1];

    int i, j;

    for (i = 0; i < length ; i++) {
        if (i != (length - 1)) {
            if ((scores[i][0] + scores[i][1]) > totalRounds) {
                return false;
            }
        }
        for (j = 0; j < 2; j++) {
            if (i != (length - 1)) {
                if (scores[i][j] > scores[i+1][j]) {
                    return false;
                }
            }
        }
    }

    return true;
}

long int combinations(int n, int k) {

    long int top = 1;
    int j = 1;

    for (int i = n; i > (n-k); i--) {
        if (j <= k) {
            top *= i;
            top /= j;
            j++;
        } else  {
            top *= i;
        }
    }

    return top;
}

long int chama(int length, int scores[][2]) {
    
    long int total = 1;

    if (length == 1) {
        total = combinations(scores[0][0] + scores[0][1], scores[0][0]);
    } else {
        total *= combinations(scores[0][0] + scores[0][1], scores[0][0]);
        for (int i = 1; i < length; i++) { 
            total *= combinations((scores[i][0]-scores[i-1][0]) + (scores[i][1]-scores[i-1][1]), (scores[i][0]-scores[i-1][0]));
        }
    }

    return total;
}

// compare function for qsort, taken from http://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv) {
    int nTestCases;
    int nScores;
    string score1, score2;
    bool check = true;

    cin >> nTestCases;
    for (int i = 0; i < nTestCases; ++i) {
        cin >> nScores;
        int scores[nScores][2];
        for (int j = 0; j < nScores; ++j) {
            getline(cin, score1, ' ');
            getline(cin, score2);
            stringstream ss1(score1);
            stringstream ss2(score2);
            ss1 >> scores[j][0];
            ss2 >> scores[j][1];
        }
        
        qsort(scores, nScores, sizeof(int[2]), compare);

        if (nScores>=2) {
            check = checkInconsistency(nScores, scores);
        }

        if (!check) {
            cout << -1 << endl;
        } else {
            cout << (long int)chama(nScores, scores) << endl;
        }
    }

    return 0;
}

