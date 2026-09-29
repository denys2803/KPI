#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>


const char text_intro[] = "Буде обчислено задану функцію у, при х є [-3; 6] з кроком 0.5\n";
const char text_intro_result[] = "Результати обчислень:\n";
const char text_intro_x_y[] = "%10s | %15s\n";
const char text_x_y_result[] = "%10.1f | %15.8f\n";

const double MIN_X = -3; // Початкове значення х
const double MAX_X = 6; // Кінцеве значення х
const double STEP_X = 0.5; // Крок значень х

const double BORDER_X = 2;  // Значення розмежування формул обчислення функції
const int SUM_MIN = 3; // Початкове значення і для обчислення суми
const int SUM_MAX = 5; // Кінцеве значення і для обчислення суми


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("%s", text_intro);
    system("pause");

    double x, y;
    printf("%s", text_intro_result);
    printf(text_intro_x_y, "x", "y");
    printf("-----------------------------\n");
    for (x = MIN_X; x <= MAX_X; x += STEP_X) {
        if (x < BORDER_X) {
            double sum = 0;
            for (int i = SUM_MIN; i <= SUM_MAX; i++) {
                sum += ((i + x)*(i + x)) / (3*i);
            }
            y = (x + 5) * sum;
        }
        else {
            double exponent = 5 - x;
            y = pow(x, exponent) + x;
        }

        printf(text_x_y_result, x, y);
    }

    system("pause");
    return 0;
}