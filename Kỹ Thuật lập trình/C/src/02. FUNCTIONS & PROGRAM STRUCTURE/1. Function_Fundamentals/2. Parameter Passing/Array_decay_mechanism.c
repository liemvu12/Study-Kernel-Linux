#include<stdio.h>

// These are equivalent				
void func1(int arr[]);				
void func2(int arr[10]);        // Size ignored!				
void func3(int *arr);				
				
// Proof of decay				
void print_sizes(int arr[]) {				
    printf("sizeof(arr) = %zu\n", sizeof(arr));        // Size of pointer!				
    printf("sizeof(int*) = %zu\n", sizeof(int*));      // Same value				
}				
				
int main() {				
    int array[10];				
    printf("sizeof(array) = %zu\n", sizeof(array));    // 40 bytes				
    print_sizes(array);                                 // 8 bytes (on 64-bit)				
    return 0;				
}				
