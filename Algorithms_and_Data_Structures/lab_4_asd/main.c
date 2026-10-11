#include <stdio.h>
#include <windows.h>
#include <stdbool.h>


unsigned int ackermann(unsigned int n, unsigned int m);
void input_unsigned(const char name[], unsigned int *value, unsigned int limit_num);


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    unsigned int n, m;

    printf("Для обчислення функції Акермана А(n, m) введіть невід'ємні цілі числа n та m:\n");
    
    input_unsigned("n", &n, 3);
    input_unsigned("m", &m, 12);

    unsigned int ackermann_result = ackermann(n, m);
    printf("Значення A(%u, %u) = %u\n", n, m, ackermann_result);

    system("pause");
    return 0;
}


unsigned int ackermann(unsigned int n, unsigned int m) {
    if (n == 0) {
        return m + 1;
    } else if (m == 0) {
        return ackermann(n - 1, 1);
    } else {
        return ackermann(n - 1, ackermann(n, m - 1));
    }
}


void input_unsigned(const char name[], unsigned int *value, unsigned int limit_num) {
    bool valid = false;
    int temp;

    do {
        printf("Введіть %s <= %d: ", name, limit_num);
        int scan_result = scanf("%d", &temp);
        if (scan_result == 1 && temp >= 0 && temp <= limit_num) {
            *value = temp;
            valid = true;
        }
        else {
            printf("Помилка ввода даних! Не вводьте зайвих букв чи символів, тільки невід'ємні цілі числа в запропонованому діапазоні. Спробуйте знову.\n");
        }
        while (getchar() != '\n');
    } while (!valid);
}
