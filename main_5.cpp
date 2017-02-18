#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct Info {
    int duration;
    int deadline;
};

bool sortByDeadline(const Info &lhs, const Info &rhs) { return lhs.deadline < rhs.deadline; }

int main() {
    int n, count, days_passed, best;

    while (scanf("%d", &n) > 0) {
        vector<Info> array(n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &array[i].duration, &array[i].deadline);
        }
        scanf("%d", &count);

        sort(array.begin(), array.end(), sortByDeadline);

        best = 0;

        for (int j = 0; j < n; j++) {
            count += array[j].duration;

            if ((days_passed = count - array[j].deadline) > best) {
                    best = days_passed;
            }
        }

        printf("%d\n", best);
    }
    return 0;
}