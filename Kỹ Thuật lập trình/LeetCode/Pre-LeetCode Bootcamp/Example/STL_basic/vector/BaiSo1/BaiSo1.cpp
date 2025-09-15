// Đọc n số, lưu vào `vector`, in ra đảo ngược.
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    cout << "\n";
    vector<int> ptr(n);
    for(int i = 0; i < n; i++){
        cin >> ptr[i];
    }
    cout << "\n";
    for(auto it = ptr.rbegin(); it != ptr.rend(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
}