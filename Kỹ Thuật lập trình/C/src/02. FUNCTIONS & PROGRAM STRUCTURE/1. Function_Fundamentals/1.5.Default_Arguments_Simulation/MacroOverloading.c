#include <stdio.h>

// Giả lập overload bằng macro
#define print_number(x)         print_number_impl(x, 10)     // Default base = 10
#define print_number_base(x,b)  print_number_impl(x, b)

void print_number_impl(int number, int base) {
    printf("Number %d in base %d: ", number, base);

    if (base == 10) {
        printf("%d\n", number);
    } else if (base == 16) {
        printf("%X\n", number);
    } else if (base == 2) {
        // In nhị phân (thủ công)
        for (int i = 31; i >= 0; i--) {
            printf("%d", (number >> i) & 1);
        }
        printf("\n");
    } else {
        printf("Unsupported base\n");
    }
}

int main() {
    print_number(255);           // in ra: 255 (mặc định base 10)
    print_number_base(255, 16);  // in ra: FF
    print_number_base(255, 2);   // in ra: 00000000000000000000000011111111
    return 0;
}
