#include <iostream>
#include <queue>
using namespace std;

void sort(queue<int> &q) {
    int n = q.size();
    int max = q.front();
    q.pop();
    for(int i = 0; i < n - 1; i++) {
        int curr = q.front();
        q.pop();
        if (max < curr) {
            int tmp = curr;
            curr = max;
            max = tmp;
        }
        q.push(curr);
    }
    q.push(max);
}

int main() {
    queue<int> q1;
    queue<int> result;

    q1.push(321);
    q1.push(34);
    q1.push(31);
    q1.push(45);
    q1.push(1235);
    q1.push(900);
    q1.push(901);

    sort(q1);
    while (!q1.empty()) {
        result.push(q1.front());
        q1.pop();
    }

    // Print the sorted result queue
    while (!result.empty()) {
        
        cout << result.front() << " ";
        result.pop();
    }

    return 0;
}

