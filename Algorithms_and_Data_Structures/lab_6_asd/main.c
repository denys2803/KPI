#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_ELEMENTS_ARR 15
#define MIN_ELEMENTS_ARR 0
#define MIN_ELEMENTS -1000
#define MAX_ELEMENTS 1000
#define INIT_ARRAY {12, -5, 0, 8, -3, 15, 4, -10, 6, 7}
#define INIT_ARRAY_SIZE ((int)(sizeof((int[])INIT_ARRAY) / sizeof(int)))


struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct DoublyList {
    struct Node* head;
    struct Node* tail;
};


void initList(struct DoublyList* list);
int isEmpty(struct DoublyList* list);
void pushBack(struct DoublyList* list, int value);
void chooseInputMethod(struct DoublyList* list);
void inputFromKeyboard(struct DoublyList* list, int n);
void inputFromArray(struct DoublyList* list);
void output(struct DoublyList* list, const char text[]);
void deleteNode(struct DoublyList* list, struct Node* target);
void createPositiveList(struct DoublyList* src, struct DoublyList* dst);
void processRemoveMultiples(struct DoublyList* list);
void removeMultiples(struct DoublyList* list, int k);
void freeList(struct DoublyList* list);


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("Програма визначає додатні елементи обраного масиву даних, та видаляє елементи кратні введеному числу.");
    do {
        struct DoublyList mainList;
        struct DoublyList positiveList;

        printf("\n------------------------------\n");

        initList(&mainList);
        chooseInputMethod(&mainList);

        output(&mainList, "\nВаш");

        createPositiveList(&mainList, &positiveList);
        processRemoveMultiples(&mainList);

        freeList(&mainList);
        freeList(&positiveList);

        printf("\nНатисніть ESC для виходу або будь-яку іншу клавішу для повторного запуску.\n");
    } while (_getch() != 27);

    return 0;
}


void initList(struct DoublyList* list)
{
    list->head = NULL;
    list->tail = NULL;
}


int isEmpty(struct DoublyList* list)
{
    return list->head == NULL;
}


void pushBack(struct DoublyList* list, int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("======== Помилка виділення пам'яті!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (isEmpty(list)) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        struct Node* oldTail = list->tail;
        oldTail->next = newNode;
        list->tail = newNode;
    }
}


void chooseInputMethod(struct DoublyList* list)
{
    char choice;
    int n;
    bool isValid = true;

    do {               
        isValid = true;
        printf("Оберіть спосіб заповнення списку:\n"
               "- натисніть 'a' для використання вбудованого масиву (%d елементів)\n"
               "- натисніть 'b' для вводу масиву з клавіатури\n"
               "Ваш вибір: ", INIT_ARRAY_SIZE);


        choice = _getche();
        choice = (char)tolower((unsigned char)choice);
        printf("\n");

        if (choice == 'a') {
            inputFromArray(list);
        }
        else if (choice == 'b') {
            do {
                printf("\nВведіть кількість елементів масиву (%d..%d): ", MIN_ELEMENTS_ARR, MAX_ELEMENTS_ARR);
                scanf("%d", &n);
                while (getchar() != '\n');
            } while (n < MIN_ELEMENTS_ARR || n > MAX_ELEMENTS_ARR);
            inputFromKeyboard(list, n);
        }
        else {
            printf("\n======== Помилка! Натисніть запропоновані варіанти!\n\n");
            isValid = false;
        }
    } while (!isValid);
}


void inputFromKeyboard(struct DoublyList* list, int n)
{
    int val;
    printf("Вводьте цілі елементи в діапазоні від %d до %d:\n", MIN_ELEMENTS, MAX_ELEMENTS);
    
    for (int i = 0; i < n; i++) {
        bool isValid = false;
        
        while (!isValid) {
            printf("Введіть елемент [%d/%d]: ", i + 1, n);
            
            int scan_val = scanf("%d", &val);
            if (scan_val != 1) {
                printf("======== Помилка: введіть ціле число!\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            
            if (val < MIN_ELEMENTS || val > MAX_ELEMENTS) {
                printf("======== Помилка: число має бути цілим в діапазоні від %d до %d!\n", MIN_ELEMENTS, MAX_ELEMENTS);
            } else {
                isValid = true;
            }
        }
        
        pushBack(list, val);
    }
}


void inputFromArray(struct DoublyList* list)
{
    int arr[INIT_ARRAY_SIZE] = INIT_ARRAY;
    for (int i = 0; i < INIT_ARRAY_SIZE; i++) {
        pushBack(list, arr[i]);
    }
}


void output(struct DoublyList* list, const char text[])
{
    if (isEmpty(list)) {
        printf("%s список порожній.\n", text);
        return;
    }
    struct Node* current = list->head;
    printf("%s список: ", text);
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


void deleteNode(struct DoublyList* list, struct Node* target)
{
    if (target == NULL) {
        return;
    }

    struct Node* leftNode = target->prev;
    struct Node* rightNode = target->next;

    if (leftNode != NULL) {
        leftNode->next = rightNode;
    }
    else {
        list->head = rightNode;
    }

    if (rightNode != NULL) {
        rightNode->prev = leftNode;
    }
    else {
        list->tail = leftNode;
    }

    free(target);
}


void createPositiveList(struct DoublyList* src, struct DoublyList* dst)
{
    initList(dst);
    int totalCount = 0;
    int positiveCount = 0;

    struct Node* current = src->head;
    while (current != NULL) {
        totalCount++;
        if (current->data > 0) {
            pushBack(dst, current->data);
            positiveCount++;
        }
        current = current->next;
    }

    printf("\n--- Додатні елементи ---\n");
    output(src, "Початковий");
    output(dst, "Новий");

    if (totalCount > 0) {
        double percent = (positiveCount * 100.0) / totalCount;
        printf("Кількість додатних: %d із %d (%.2f%%)\n", positiveCount, totalCount, percent);
    }
    else {
        printf("Початковий список порожній, відсоток: 0.00%%\n");
    }
}


void processRemoveMultiples(struct DoublyList* list)
{
    int k;
    printf("\n--- Видалення кратних чисел ---\n");
    output(list, "Початковий");
    printf("Введіть дільник (ціле число, не 0): ");
    scanf("%d", &k);
    while (getchar() != '\n');

    removeMultiples(list, k);
    output(list, "Новий");
}


void removeMultiples(struct DoublyList* list, int k)
{
    if (k == 0) {
        printf("На нуль ділити не можна. Нічого не видалено.\n");
        return;
    }

    int deletedCount = 0;
    struct Node* current = list->head;
    printf("Видалені елементи: ");

    while (current != NULL) {
        struct Node* nextNode = current->next;
        if (current->data % k == 0) {
            printf("%d ", current->data);
            deleteNode(list, current);
            deletedCount++;
        }
        current = nextNode;
    }

    if (deletedCount == 0) {
        printf("немає");
    }
    printf("\n");
}


void freeList(struct DoublyList* list)
{
    while (!isEmpty(list)) {
        deleteNode(list, list->head);
    }
}