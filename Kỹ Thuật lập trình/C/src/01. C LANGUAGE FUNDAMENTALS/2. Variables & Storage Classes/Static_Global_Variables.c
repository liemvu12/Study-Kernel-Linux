#include <stdio.h>
int get_value() { return 42; }

void problematic_static() {
    static int value = get_value();  // LỖI: không phải constant expression
}
