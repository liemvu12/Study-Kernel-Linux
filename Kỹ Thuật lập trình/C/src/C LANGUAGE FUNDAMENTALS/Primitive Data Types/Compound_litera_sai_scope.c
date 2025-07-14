#include <stdio.h>
int *p;	
int main(){
    {	
    p = (int[]){1, 2, 3};	
    }	
    printf("%d\n", p[0]); // Behavior?	

}