#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.erase(v.begin()+1);
    for (auto i:v)
        cout << i << endl;
    return 0;
}
