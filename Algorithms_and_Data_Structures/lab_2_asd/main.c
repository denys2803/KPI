#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>


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
    
    char key;

    do {
        int count = 0;
        double d, b, a, c;
        
        do {
            printf("Введіть значення d (d > 0) = ");
            if (scanf("%lf", &d) == 1) {
                if(d > 0) {
                    count++;
                } else {
                    error_message();
                }
            } else {
                error_message();
            }
            while (getchar() != '\n');
        } while (count != 1);
        
        do {
            printf("Введіть значення b = ");
            if (scanf("%lf", &b) == 1) {
                count++;
            } else {
                error_message();
            }
            while (getchar() != '\n');
        } while (count != 2);

        do {
            printf("Введіть значення a (a ≠ %.10g, a ≠ %.10g) = ", b, -1*b);
            if (scanf("%lf", &a) == 1) {
                if(a != b && a != -1*b) {
                    count++;
                } else {
                    error_message();
                }
            } else {
                error_message();
            }
            while (getchar() != '\n');
        } while (count != 3);

        do {
            printf("Введіть значення c (c > 0, c < 360, c ≠ 180) = ");
            if (scanf("%lf", &c) == 1) {
                if(c > 0 && c < 360 && c != 180) {
                    count++;
                } else {
                    error_message();
                }
            } else {
                error_message();
            }
            while (getchar() != '\n');
        } while (count != 4);
        
        double result;
        result = log(d) / (fabs(b * b - a * a) * sin(c * M_PI / 180));
        print_dashes(50);
        printf("Область визначення функції: x ∈ R\nРезультат обчислення функції: %.10g\n", result);
        print_dashes(50);

        printf("Натисніть ESC для виходу, або будь-яку іншу клавішу для повторення розрахунків.\n");
        key = _getch();

    } while(key != 27);

    return 0;
}