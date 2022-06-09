#include <stdio.h>

// Dupla: Gabriel Dias e Nicolas Henriques


typedef struct {
    int d;
    int x;
    int y;
} ExtendedEuclidNumbers;

ExtendedEuclidNumbers ExtendedEuclid(int a, int b);
void ModularLinearEquationSolver(int a, int b, int n);
void HasInverseModN(int a, int n);

void main() {
    int a;
    int b;
    int n;

    printf("Digite o valor de a: ");
    scanf("%d", &a);
    printf("Digite o valor de b: ");
    scanf("%d", &b);
    printf("Digite o valor de n: ");
    scanf("%d", &n);

    HasInverseModN(a, n);
    ModularLinearEquationSolver(a, b, n);
}


ExtendedEuclidNumbers ExtendedEuclid(int a, int b) {
    if (b == 0) {
        return (ExtendedEuclidNumbers) {
            .d = a,
            .x = 1,
            .y = 0
        };
    }

    ExtendedEuclidNumbers numbers = ExtendedEuclid(b, a % b);
    int d = numbers.d;
    int x = numbers.x;
    int y = numbers.y;

    return (ExtendedEuclidNumbers) {
        .d = d,
        .x = y,
        .y = x - (a / b) * y
    };
}


void HasInverseModN(int a, int n) {
    ExtendedEuclidNumbers numbers = ExtendedEuclid(a, n);
    int d = numbers.d;
    int x = numbers.x;
    int y = numbers.y;

    if (d == 1) {
        if (x < 0) {
            x += n;
        }

        printf("O inverso de %d em Z%d é %d\n", a, n, x);
    } else {
        printf("Este valor %d não possui inverso em Z%d\n", a, n);
    }
}


void ModularLinearEquationSolver(int a, int b, int n) {
    ExtendedEuclidNumbers numbers = ExtendedEuclid(a, n);
    int d = numbers.d;
    int x = numbers.x;
    int y = numbers.y;

    if (b % d == 0) {
        printf("----Há %d soluções para %dx === %d (mod %d)----\n", d, a, b, n);

        int x0 = (x * (b / d)) % n;

        if (x0 < 0) {
            x0 += n;
        }

        for (int i = 0; i <= d - 1; i++) {
            int xi = (x0 + i * (n / d)) % n;
            printf("x%d = %d, ", i, xi);
        }

        printf("\n");
    } else {
        printf("----Não há soluções para %dx === %d (mod %d)----\n", d, a, b, n);
    }
}
