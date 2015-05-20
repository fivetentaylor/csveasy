#include <stdio.h>
#include <stdlib.h>

void test_safe_index(int num, int den) {
    div_t d = div(num, den);
    printf("num  = %-10dden  = %-10d\n", num, den);
    printf("quot = %-10drem  = %-10d\n", d.quot, d.rem);
}

void run_test_list() {
    printf("BEGIN div function tests\n");
    test_safe_index(10, 3);
    printf("\n");
    test_safe_index(2, 5);
    printf("\n");
    test_safe_index(-2, 10);
    printf("\n");
    test_safe_index(10, -2);
    printf("\n");
    test_safe_index(-3, 10);
    printf("\n");
    test_safe_index(10, -3);
    printf("END div function tests\n");
}
