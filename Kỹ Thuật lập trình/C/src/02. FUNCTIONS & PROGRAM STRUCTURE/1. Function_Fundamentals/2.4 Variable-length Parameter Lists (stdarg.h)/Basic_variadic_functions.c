#include <stdio.h>
#include <stdarg.h>

// Simple variadic function: tính tổng của các số nguyên
int sum(int count, ...) {
    va_list args;              // Khai báo danh sách đối số
    va_start(args, count);     // Khởi tạo danh sách từ tham số "count"

    int total = 0;
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int); // Lấy đối số tiếp theo kiểu int
        total += value;
    }

    va_end(args);              // Giải phóng danh sách đối số
    return total;
}

// Entry point
int main() {
    int result = sum(4, 10, 20, 30, 40);   // Tổng = 100
    printf("Sum = %d\n", result);         // Output: Sum = 100

    int result2 = sum(2, 7, 8);           // Tổng = 15
    printf("Sum = %d\n", result2);        // Output: Sum = 15

    return 0;
}
