#include <stdio.h>
#include <locale.h>
#include <conio.h>

int main(){
    setlocale(LC_ALL, "uk_UA.UTF-8");

    int num_in, num_last, result;

    printf("Введіть тризначне число: ");
    scanf("%d", &num_in);

    num_last = num_in % 10;
    num_in = num_in / 10;
    result = num_last * 100 + num_in;

    printf("Результат: %d\n", result);

    getch();
    return 0;

}