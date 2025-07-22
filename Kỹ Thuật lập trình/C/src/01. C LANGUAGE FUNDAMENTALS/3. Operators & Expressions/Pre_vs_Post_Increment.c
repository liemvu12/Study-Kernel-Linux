#include<stdio.h>

void pre_post_increment() {
    int a = 5, b = 5;
    int x, y;
    
    x = ++a;  // Pre-increment: a tăng trước, sau đó assign
    y = b++;  // Post-increment: assign trước, sau đó b tăng
    
    printf("Pre-increment: a=%d, x=%d\n", a, x);  // a=6, x=6
    printf("Post-increment: b=%d, y=%d\n", b, y);  // b=6, y=5
}

int main(){
    pre_post_increment();
}