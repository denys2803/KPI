#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>


void print_dashes(int count)
{
    for (int i = 0; i < count; i++){
        printf("-");
    }
    printf("\n");
}


void error_message()
{
    print_dashes(30);
    printf("ПОМИЛКА: введене значення невірне! Перевірте, щоб не було букв, або спеціальних символів. Вводьте значення, що задовільняють умові.\n");
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("Для дослідження області визначення і обчислення значення функції y(x) = (Ln(d))/(|b^2-a^2|sin(c)), введіть такі значення:\n");

    double d, b, a, c;

    printf("Введіть значення d (d > 0) = ");
    scanf("%lf", &d);

    if(d > 0) {
        printf("Введіть значення b = ");
        scanf("%lf", &b);
        printf("Введіть значення a (a ≠ %g, a ≠ %g) = ", b, -1*b);
        scanf("%lf", &a);

        if(a != b && a != -1*b) {
            printf("Введіть значення c (c > 0, c < 360, c ≠ 180) = ");
            scanf("%lf", &c);

            if(c > 0 && c < 360 && c != 180) {
                double result;
                result = log(d) / (fabs(b * b - a * a) * sin(c * M_PI / 180));
                print_dashes(50);
                printf("Область визначення функції: x ∈ R\nРезультат обчислення функції: %.10g\n", result);
                print_dashes(50);

            } else {
                error_message();
            }

        } else {
            error_message();
        }

    } else {
        error_message();
    }

    system("pause");
    return 0;
}