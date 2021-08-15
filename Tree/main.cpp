#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> arr;
    arr.push_back(6);
    arr.push_back(5);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(2);
    for (int a : arr) {
        // 这样做可以让 1 放在 0 的位置， 2 放在 1, 3 放在 2
        while (a > 0 && a <= arr.size() && a != arr[a - 1]) swap(a, arr[a - 1]);
    }
    for (int a : arr) {
        cout<<a<<endl;
    }
    return 0;
}
