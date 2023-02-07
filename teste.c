#include <stdio.h>

int main(){
    int m, n, r;
    scanf("%d %d", &m, &n);
    r = m -+ n;
    printf("%d", r);
    return 0;
}