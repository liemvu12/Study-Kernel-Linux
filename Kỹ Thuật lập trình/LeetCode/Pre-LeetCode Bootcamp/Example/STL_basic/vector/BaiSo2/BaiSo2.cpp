// Xóa tất cả số lẻ trong vector.
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> ptr = {2, 1, 4, 5, 9};
    for(auto it = ptr.begin(); it !=ptr.end(); ){
        if ((*it) %2 == 1){
            it = ptr.erase(it); //cập nhật it.
        }else {
            cout << *it << " ";
            ++it ;
        }
    }
}