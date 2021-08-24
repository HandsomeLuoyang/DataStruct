/*
-------------------------------------------------
   Author :       86178
   date:          2021/8/24 21:47
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;

/*
 * 无序列表顺序查找
 */
int sequenceDisorderedSearch(vector<int> arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

/*
 * 有序列表顺序查找
 */
int sequenceOrderedSearch(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
        else if (arr[i] > target) return -1;
    }
    return -1;
}

/*
 * 二分查找
 */
int binarySearch(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int lo = 0, hi = arr.size(), mid;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    int a[] = {10, 23, 165, 4, 234, 78, 15, 54, 67, 99};
    vector<int> arr(begin(a), end(a));
    vector<int> test(begin(a), end(a));
    sort(test.begin(), test.end());
    for (auto i:test) {
        cout << i << " ";
    }
    cout << endl;
    cout << sequenceDisorderedSearch(arr, 54) << endl;
    cout << sequenceOrderedSearch(arr, 54) << endl;
    cout << binarySearch(arr, 54) << endl;
    return 0;
}