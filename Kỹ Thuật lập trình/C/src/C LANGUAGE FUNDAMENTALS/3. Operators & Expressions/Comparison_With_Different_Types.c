#include<stdio.h>
void comparison_types() {	
    int a = -1;	
    unsigned int b = 1;	
    	
    printf("int a = %d, unsigned b = %u\n", a, b);	
    printf("a < b: %s\n", (a < b) ? "true" : "false");  // false! (surprising)	
    	
    // Explanation: a được convert thành unsigned, trở thành very large number	
    printf("a as unsigned: %u\n", (unsigned)a);	
    	
    // Safe comparison	
    printf("Safe comparison: %s\n", 	
           (a < 0 || (unsigned)a < b) ? "true" : "false");	
}	

int main(){
    comparison_types();
}