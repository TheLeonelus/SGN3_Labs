#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 15
#define SUBJECT_COUNT 5
#define F_AMOUNT 2

typedef struct student
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int age;
    int grade[SUBJECT_COUNT];
    double averageGrade;
    int group;
} student;

int inputAmount();
void arrayFullfill(student *array, int amount);
void groupDefine(student *array, int amount);
int countingSortStudentByGroup(student *array, int amount);
void arrayOutput(student *array, int amount);
void averageGradeDefine(student *array, int amount);
int deleteStudents(student *array, int amount);
int sortArrayByName(student *array, int amount);
int stringCompare(const void *a, const void *b);

int main()
{
    int amount = inputAmount();
    student *array = (student *)malloc(amount * sizeof(student));
    arrayFullfill(array, amount);
    groupDefine(array, amount);
    if (sortArrayByName(array, amount))
        return EXIT_FAILURE;
    if (countingSortStudentByGroup(array, amount))
        return EXIT_FAILURE;
    averageGradeDefine(array, amount);
    arrayOutput(array, amount);
    amount = deleteStudents(array, amount);
    printf_s("\n\n---[After deleting]---\n");
    arrayOutput(array, amount);
    free(array);
    return EXIT_SUCCESS;
}

// Ввод количества студентов
int inputAmount()
{
    int check = 0;
    int n;
    do {
        printf_s("\nInput amount of students: ");
        scanf("%d", &n);
        if (n <= 0)
            printf_s("\nInappropriate input! Please try again.");
        else
            check++;
    } while (check <= 0);
    return n;
}

// Ввод полей структур в массиве
void arrayFullfill(student *array, int amount)
{
    printf_s("\n\nFullfilling array of students...\n");
    for (int i = 0; i < amount; i++) {
        getchar();
        printf_s("\nStudent №%i. \nInput name: ", i + 1);
        fgets((array + i)->name, MAX_SIZE, stdin);
        *((array + i)->name + strcspn((array + i)->name, "\r\n")) = 0;
        *(array + i)->name = toupper(*(array + i)->name);
        printf_s("\nInput surname:");
        fgets((array + i)->surname, MAX_SIZE, stdin);
        *((array + i)->surname + strcspn((array + i)->surname, "\r\n")) = 0;
        *(array + i)->surname = toupper(*(array + i)->surname);
        while (1) {
            printf_s("\nInput age: ");
            scanf("%i", &(array + i)->age);
            if ((array + i)->age <= 0)
                printf_s("\nInappropriate input! Please try again.");
            else
                break;
        }
        printf_s("\nInput grades from 2 to 5..");
        for (int j = 0; j < SUBJECT_COUNT; j++) {
            while (1) {
                printf_s("\nGrade №%i: ", j + 1);
                scanf("%i", &*((array + i)->grade + j));
                if (*((array + i)->grade + j) > 5 || *((array + i)->grade + j) < 2)
                    printf_s("\nInappropriate input! Please try again.");
                else
                    break;
            }
        }
    }
}

// Определение группы студента
void groupDefine(student *array, int amount)
{
    for (int i = 0; i < amount; i++) {
        (array + i)->group = 5;
        for (int j = 0; j < 5; j++) {
            if (*((array + i)->grade + j) == 2) {
                (array + i)->group = 2;
                break;
            }
            if (*((array + i)->grade + j) < (array + i)->group)
                (array + i)->group = *((array + i)->grade + j);
        }
    }
}

// Сортировка массива студентов подсчётом по группам
int countingSortStudentByGroup(student *array, int amount)
{
    student *output = (student*) malloc(amount * sizeof(student));
    if (output == NULL)
        return EXIT_FAILURE;
    int *count = (int*) calloc(6, sizeof(int));
    if (count == NULL)
        return EXIT_FAILURE;
    for (int i = 0; i < amount; i++) {
        *(count + (array + i)->group) += 1;
    }
    for (int i = 1; i <= 5; i++) {
        *(count + i) += *(count + i - 1);
    }
    for (int i = amount - 1; i >= 0; i--) {
        *(output + *(count + (array + i)->group) - 1) = *(array + i);
        *(count + (array + i)->group) -= 1;
    }
    for (int i = 0; i < amount; i++) {
        *(array + i) = *(output + i);
    }
    free(output);
    free(count);
    return EXIT_SUCCESS;
}

// Вывод массива студентов
void arrayOutput(student *array, int amount)
{
    printf_s("\nArray of students");
    for (int i = 0; i < amount; i++)
    {
        printf_s("\n{name: %.8s | surname: %.8s | age: %i | grades:", (array + i)->name, (array + i)->surname, (array + i)->age);
        for (int j = 0; j < SUBJECT_COUNT; j++)
            printf_s(" %i |", *((array + i)->grade + j));
        printf_s(" average grade: %3.3f | group: %i", (array + i)->averageGrade, (array + i)->group);
    }
}

// Подсчёт среднего балла
void averageGradeDefine(student *array, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        (array + i)->averageGrade = 0.0;
        for (int j = 0; j < SUBJECT_COUNT; j++)
            (array + i)->averageGrade += *((array + i)->grade + j);
        double temp = SUBJECT_COUNT;
        (array + i)->averageGrade = (array + i)->averageGrade / temp;
    }
}

// Удаление двух студентов с 2+ двойками
int deleteStudents(student *array, int amount)
{
    int buff = amount;
    for (int i = 0; i < buff;)
    {
        if ((array + i)->group == 3)
            break;
        int count = 0;
        for (int j = 0; j < 5; j++)
        {
            if (*((array + i)->grade + j) == 2)
                count++;
        }
        if (count > F_AMOUNT)
        {
            buff--;
            for (int j = i; j < buff; j++)
                *(array + j) = *(array + j + 1);
            array = (student*) realloc(array, buff * sizeof *array);
        }
        else
            i++;
    }
    return buff;
}

// Сортировка массива по именам
int sortArrayByName(student *array, int amount)
{
    char **stringArray = (char**) malloc(amount * sizeof(char *));
    if (stringArray == NULL)
        return EXIT_FAILURE;
    for (int i = 0; i < amount; i++) // Вынесение имён из структур в массив строк
    {
        int length = strlen((array + i)->name) + 1;
        *(stringArray + i) = (char*) malloc(length * sizeof(char));
            if (*(*stringArray + i) == NULL) {
                for (i--; i >= 0; i--)
                    free(*stringArray + i);
                free(*stringArray);
                **stringArray = NULL;
                return EXIT_FAILURE;
            }
        strcpy(*(stringArray + i), (array + i)->name);
    }
    qsort(stringArray, amount, sizeof(char *), stringCompare); // qsort массива строк
    for (int i = 0; i < amount; i++) // Выставление по позициям имён в массиве строк имена в массиве студентов
    {
        for (int j = 0; j < amount; j++)
        {
            if (strcmp(*(stringArray + i), (array + j)->name) == 0)
            {
                student temp = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = temp;
                break;
            }
        }
    }
    for (int i = 0; i < amount; i++)
        free(*(stringArray + i));
    free(stringArray);
    return EXIT_SUCCESS;
}

// Сравнение строк для qsort
int stringCompare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}


/*
Условие Л.р. №10
10.1.
Вводится массив структур student. У каждого студента есть, как минимум поля имя и массив из 5 оценок
(при желании можно добавить больше полей, характеризующих студента).
Необходимо сгруппировать массив по 4 группам:
отличники (все 5), хорошисты (хотя бы одна 4),троечники(хотя бы одна 3) и двоечники(хотя бы одна 2).
В каждой группе - отсортировать студентов по алфавиту.
10.2.
Удалить всех студентов, у которых больше двух двоек.
Для каждого студента вычислить его средний балл (поместить в соответствующее поле структуры).
*/