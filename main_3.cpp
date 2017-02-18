#include <iostream>
#include <sstream>

int n;
int m;
int matrix[15][30];
int smallest;
int actual;

using namespace std;

bool checkIfBigger(int a, int b) {
    return a > b;
}

bool checkIfBiggerEqual(int a, int b) {
    return a >= b;
}

void smallestTime(int proc, int processors[]) {

    if ( checkIfBiggerEqual(actual,smallest) ) {
        return;
    }

    if ( checkIfBiggerEqual(proc,n) )  {
        smallest = actual;
        return;
    }

    for (int i = 0; i < m; i++) {
        int previous = actual;
        if ( checkIfBigger(smallest,(processors[i] + matrix[i][proc])) ) {
            processors[i] += matrix[i][proc];

            if( checkIfBigger(processors[i],actual) ) {
                actual = processors[i];
            }

            smallestTime(proc + 1, processors);

            actual = previous;
            processors[i] -= matrix[i][proc];
        }
    }
}

int main(int argc, char** argv) {

    int i;
    int j;
    string score1;
    smallest = 0;
    
    cin >> n;
    cin >> m;

    int processors[m];

    for (i = 0; i < m; i++) {
        processors[i] = 0;
        actual = 0;
        for (j = 0; j < n-1; j++) {
            getline(cin, score1, ' ');
            stringstream ss1(score1);
            ss1 >> matrix[i][j];
            actual += matrix[i][j];
        }
        getline(cin, score1);
        stringstream ss1(score1);
        ss1 >> matrix[i][j];
        actual += matrix[i][j];

        if (actual > smallest) {
            smallest = actual;
        }
    }
    actual = 0;

    smallestTime(0, processors);

    cout << smallest << endl;

    return 0;
}