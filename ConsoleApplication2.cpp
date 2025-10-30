#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

struct node
{
    char inf[256];
    struct node* next;
};

struct node* front = NULL;
struct node* rear = NULL;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safe_input_string(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}


int safe_input_int() {
    char input[100];
    int number;

    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &number) == 1) {
                return number;
            }
            printf("Ошибка! Введите целое число: ");
        }
    }
}


struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите данные элемента: ");
    safe_input_string(s, sizeof(s));

    if (strlen(s) == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->next = NULL;

    return p;
}

void enqueue(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (rear == NULL)
    {
        front = p;
        rear = p;
    }
    else
    {
        rear->next = p;
        rear = p;
    }
    printf("Элемент '%s' добавлен в очередь!\n", p->inf);
}


void dequeue(void)
{
    if (front == NULL)
    {
        printf("Очередь пуста!\n");
        return;
    }

    struct node* temp = front;
    printf("Элемент '%s' удален из очереди!\n", front->inf);

    front = front->next;


    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);
}


void display_queue(void)
{
    struct node* current = front;
    if (front == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("\nСодержимое очереди\n");
    int count = 1;
    while (current)
    {
        printf("%d. %s\n", count, current->inf);
        current = current->next;
        count++;
    }
}


void search_element(void)
{
    if (front == NULL)
    {
        printf("Очередь пуста!\n");
        return;
    }

    char search_term[256];
    printf("Введите данные для поиска: ");
    safe_input_string(search_term, sizeof(search_term));

    struct node* current = front;
    int position = 1;
    int found_count = 0;

    printf("\nРезультаты поиска '%s':\n", search_term);

    while (current != NULL)
    {
        if (strcmp(current->inf, search_term) == 0)
        {
            printf("Найдено на позиции %d: %s\n", position, current->inf);
            found_count++;
        }
        current = current->next;
        position++;
    }

    if (found_count == 0)
    {
        printf("Элементы не найдены.\n");
    }
    else
    {
        printf("Всего найдено: %d элемент(ов)\n", found_count);
    }
}


void free_queue(void)
{
    struct node* current = front;
    struct node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    front = NULL;
    rear = NULL;
}

void menu(void)
{
    int choice;

    while (1)
    {
        printf("\nСТРУКТУРА ДАННЫХ 'ОЧЕРЕДЬ'\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Просмотреть очередь\n");
        printf("4. Поиск элемента\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");

        char input[100];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) == 1) {
                if (choice >= 1 && choice <= 5) {
                    switch (choice)
                    {
                    case 1:
                        enqueue();
                        break;
                    case 2:
                        dequeue();
                        break;
                    case 3:
                        display_queue();
                        break;
                    case 4:
                        search_element();
                        break;
                    case 5:
                        free_queue();
                        printf("Выход из программы. Память очищена.\n");
                        return;
                    }
                }
                else {
                    printf("Ошибка! Введите число от 1 до 5.\n");
                }
            }
            else {
                printf("Ошибка! Введите число от 1 до 5.\n");
            }
        }
    }
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    setlocale(LC_ALL, "Russian");
    menu();

    return 0;
}