#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


struct node
{
    char inf[256];
    struct node* next;
};

struct node* head = NULL;

void set_console_russian()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

    printf("Введите название объекта: ");

    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("Ошибка ввода\n");
        free(p);
        return NULL;
    }

    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }

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


void spstore(void)
{
    struct node* p = NULL;
    p = get_struct();

    if (p != NULL)
    {
        p->next = head;
        head = p;
        printf("Элемент '%s' добавлен в стек\n", p->inf);
    }
}


void review(void)
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Содержимое стека (от вершины к основанию):\n");
    while (struc)
    {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}


void del_stack(void)
{
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = head;
    printf("Удален элемент: %s\n", temp->inf);
    head = head->next;
    free(temp);
}


void find_element(void)
{
    char search_name[256];

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Введите имя для поиска: ");

    if (fgets(search_name, sizeof(search_name), stdin) == NULL) {
        printf("Ошибка ввода\n");
        return;
    }

    size_t len = strlen(search_name);
    if (len > 0 && search_name[len - 1] == '\n') {
        search_name[len - 1] = '\0';
    }

    struct node* struc = head;
    int found = 0;

    while (struc)
    {
        if (strcmp(search_name, struc->inf) == 0)
        {
            printf("Элемент найден: %s\n", struc->inf);
            found = 1;
            break;
        }
        struc = struc->next;
    }

    if (!found)
    {
        printf("Элемент не найден\n");
    }
}

int main()
{
    set_console_russian();

    int choice;

    do {
        printf("\nМеню операций со стеком:\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Просмотреть стек\n");
        printf("3 - Удалить элемент из стека\n");
        printf("4 - Поиск элемента\n");
        printf("5 - Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case 1:
            spstore();
            break;
        case 2:
            review();
            break;
        case 3:
            del_stack();
            break;
        case 4:
            find_element();
            break;
        case 5:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 5);

    
    while (head != NULL)
    {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
