#include <stdio.h>

// Bộ đếm số đối số (tối đa 3)
#define GET_MACRO(_1,_2,_3,NAME,...) NAME

// Định nghĩa các overload cho từng số lượng đối số
#define print_value1(v)            print_value_impl(v, 0, 0)
#define print_value2(v,w)          print_value_impl(v, w, 0)
#define print_value3(v,w,p)        print_value_impl(v, w, p)

// Macro chính
#define print_value(...) GET_MACRO(__VA_ARGS__, print_value3, print_value2, print_value1)(__VA_ARGS__)

// Hàm triển khai thật
void print_value_impl(int value, int width, int precision) {
    printf("Value: %d | Width: %d | Precision: %d\n", value, width, precision);
}

int main() {
    print_value(42);             // Value: 42 | Width: 0 | Precision: 0
    print_value(42, 5);          // Value: 42 | Width: 5 | Precision: 0
    print_value(42, 5, 2);       // Value: 42 | Width: 5 | Precision: 2
    return 0;
}
