#include <stdio.h>

int main(){
    enum Level { LOW, MEDIUM = 5, HIGH };	
    printf("%d\n", HIGH);  // Output?	
    return 0;
}