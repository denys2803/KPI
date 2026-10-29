#include <stdio.h>
#include <windows.h>
#include <stdlib.h>


void processSecondaryDiagonal(int matrix[5][5]); // Обробка побічної діагоналі
void processMainDiagonal(int matrix[5][5]); // Обробка головної діагоналі
void bubbleSortDescending(int arr[], int n); // Сортування обміном (бульбашка) за спаданням
void shakerSortDescending(int arr[], int n); // Шейкерне сортування за спаданням (покращена бульбашка)
int linearSearch(int arr[], int n, int key); // Лінійний пошук (перебір)
int binarySearchDescending(int arr[], int n, int key); // Бінарний пошук
int interpolationSearchDescending(int arr[], int n, int key); // Інтерполяційний пошук
void extractMainDiagonal(int matrix[5][5], int main_diag[], int n); // Копіювання головної діагоналі
void extractPositiveSecDiag(int matrix[5][5], int sec_diag[5], int *sec_count); // Визначення додатних значень побічної діагоналі
void printArray(int arr[], int n); // Виведення масивів
void printSearchResultSec(int matrix[5][5], int found_index, int key, int n); // Виведення результату пошуку для побічної діагоналі
void printSearchResultMain(int matrix[5][5], int found_index, int key, int n); // Виведення результату пошуку для головної діагоналі
void printMatrix(int matrix[5][5], char text[]); // Виведення матриці


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int matrix[5][5] = {
        {45, -12, 89, -21, 5},
        {67, -33, 11, 78, -90},
        {10, 44, -55, 23, 61},
        {-99, 14, 25, 38, 77},
        {15, -82, 31, 41, -12}
    };
    printMatrix(matrix, "Матриця 5x5:");
    
    processSecondaryDiagonal(matrix);
    processMainDiagonal(matrix);

    system("pause");
    return 0;
}


void processSecondaryDiagonal(int matrix[5][5]) 
{
    int sec_diag[5];
    int sec_count = 0;
    extractPositiveSecDiag(matrix, sec_diag, &sec_count);

    printf("\nДодатні елементи побічної діагоналі: ");
    if (sec_count == 0) {
        printf("відсутні.\n");
    } 
    else {
        printArray(sec_diag, sec_count);

        int key;
        printf("Введіть значення для пошуку серед додатних елементів побічної діагоналі: ");
        scanf("%d", &key);
        
        int found_index_sec = -1;
        found_index_sec = linearSearch(sec_diag, sec_count, key); // Лінійний пошук без сортування
        // shakerSortDescending(sec_diag, sec_count); // Шейкерне сортування
        // found_index_sec = interpolationSearchDescending(sec_diag, sec_count, key); // Інтерполяційний пошук

        printSearchResultSec(matrix, found_index_sec, key, 5);
    }
}


void processMainDiagonal(int matrix[5][5]) 
{
    int main_diag[5];
    extractMainDiagonal(matrix, main_diag, 5);
    
    bubbleSortDescending(main_diag, 5); // Сортування бульбашкою
    // shakerSortDescending(main_diag, 5); // Шейкерне сортування

    printf("\nВідсортована головна діагональ (за спаданням): ");
    printArray(main_diag, 5);

    int key_main;
    printf("Введіть значення для пошуку на головній діагоналі: ");
    scanf("%d", &key_main);

    int found_index_main = -1;
    
    found_index_main = binarySearchDescending(main_diag, 5, key_main); // Бінарний пошук
    // found_index_main = interpolationSearchDescending(main_diag, 5, key_main); // Інтерполяційний пошук

    printSearchResultMain(matrix, found_index_main, key_main, 5);
}


void bubbleSortDescending(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void shakerSortDescending(int arr[], int n) 
{
    int left = 0;
    int right = n - 1;
    int swapped;
    do {
        swapped = 0;
        for (int i = left; i < right; i++) {
            if (arr[i] < arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        } 

        swapped = 0;
        right--;

        for (int i = right; i > left; i--) {
            if (arr[i - 1] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;

    } while (swapped);
}


int linearSearch(int arr[], int n, int key) 
{
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}


int binarySearchDescending(int arr[], int n, int key) 
{
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        if (key > arr[mid]) {
            right = mid - 1;
        } 
        else {
            left = mid + 1;
        }
    }
    return -1;
}


int interpolationSearchDescending(int arr[], int n, int key) 
{
    int left = 0;
    int right = n - 1;
    while (left <= right && key <= arr[left] && key >= arr[right]) {
        if (arr[left] == arr[right]) {
            if (arr[left] == key) {
                return left;
            }
            return -1;
        }
        int pos = left + ((arr[left] - key) * (right - left)) / (arr[left] - arr[right]);
        
        if (arr[pos] == key) {
            return pos;
        }
        if (arr[pos] < key) {
            right = pos - 1; 
        }
        else {
            left = pos + 1;  
        }
    }
    return -1;
}


void extractMainDiagonal(int matrix[5][5], int main_diag[], int n) 
{
    for (int i = 0; i < n; i++) {
        main_diag[i] = matrix[i][i]; 
    }
}


void extractPositiveSecDiag(int matrix[5][5], int sec_diag[5], int *sec_count) 
{
    for (int i = 0; i < 5; i++) {
        int val = matrix[i][4 - i];
        if (val > 0) {
            sec_diag[*sec_count] = val;
            (*sec_count)++;
        }
    }
}


void printArray(int arr[], int n) 
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void printSearchResultSec(int matrix[5][5], int found_index, int key, int n) 
{
    if (found_index != -1) {
        for (int r = 0; r < n; r++) {
            if (matrix[r][n - 1 - r] == key) {
                printf("-> Елемент знайдено! Початкове розміщення: рядок %d, стовпець %d\n", r + 1, n - r);
                break;
            }
        }
    } 
    else {
        printf("-> Такий елемент відсутній.\n");
    }
}


void printSearchResultMain(int matrix[5][5], int found_index, int key, int n) 
{
    if (found_index != -1) {
        for (int r = 0; r < n; r++) {
            if (matrix[r][r] == key) {
                printf("-> Елемент знайдено! Початкове розміщення: рядок %d, стовпець %d\n", r + 1, r + 1);
                break;
            }
        }
    } 
    else {
        printf("-> Такий елемент відсутній.\n");
    }
}


void printMatrix(int matrix[5][5], char text[]) 
{
    printf("%s\n", text);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}