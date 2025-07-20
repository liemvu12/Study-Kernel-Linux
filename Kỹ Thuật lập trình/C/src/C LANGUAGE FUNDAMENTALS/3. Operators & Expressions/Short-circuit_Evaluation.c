#include <stdio.h>

int expensive_function() {																			
    printf("Expensive function called\n");																			
    return 1;																			
}																			
																			
void short_circuit_and() {																			
    int x = 0;																			
    																			
    printf("Testing: x && expensive_function()\n");																			
    if (x && expensive_function()) {  // expensive_function() không được gọi																			
        printf("Both true\n");																			
    } else {																			
        printf("At least one false\n");																			
    }																			
    																			
    printf("Testing: (x = 1) && expensive_function()\n");																			
    if ((x = 1) && expensive_function()) {  // expensive_function() được gọi																			
        printf("Both true\n");																			
    }																			
}

int main(){
    short_circuit_and();
}
