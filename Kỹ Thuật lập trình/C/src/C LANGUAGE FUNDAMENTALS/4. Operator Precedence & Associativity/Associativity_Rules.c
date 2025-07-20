#include <stdio.h>
void left_associativity() {
    int a = 10, b = 5, c = 2;
    
    // Arithmetic operators
    printf("10 - 5 - 2 = %d\n", a - b - c);      // (10 - 5) - 2 = 3
    printf("10 / 5 / 2 = %d\n", a / b / c);      // (10 / 5) / 2 = 1
    
    // Shift operators
    printf("8 >> 1 >> 1 = %d\n", 8 >> 1 >> 1);  // (8 >> 1) >> 1 = 2
}

int main(){
    left_associativity();
}