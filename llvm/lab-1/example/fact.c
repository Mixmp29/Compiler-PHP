#include <stdio.h>

int factorial(int n)
{
    return n == 0 ? 1 : n * factorial(n - 1);
}

int main()
{
    int n;
    int f;

    scanf("%d", &n);

    if (n < 0) {
        return 1;
    }

    f = factorial(n);

    return 0;
}
