#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct Course
{
    char name[50];
    char instructor[50];
    char tema[50];
    double rating;
    double cost;
    int time;
};

void WriteToFile(struct Course courses[], int courseCount);
void ReadFromFile(struct Course courses[], int courseCount);
void bubbleSort(struct Course arr[], int n);
void displayWelcomeScreen();
void inputCourseInfo(struct Course* course);
void printCourse(struct Course* course);

int main()
{
    setlocale(LC_ALL, "RUS");
    struct Course courses[100];
    int courseCount = 0;
    int choice;

    system("chcp 1251");
    do
    {
        displayWelcomeScreen();
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            if (courseCount < 100)
            {
                struct Course newCourse;
                inputCourseInfo(&newCourse);
                courses[courseCount] = newCourse;
                courseCount++;
                printf("Курс успешно добавлен!\n");
            }
            else
            {
                printf("Достигнуто максимальное количество курсов!\n");
            }
            break;
        case 2:
            if (courseCount == 0)
            {
                printf("Нет доступных курсов\n");
            }
            else
            {
                char searchName[50];
                printf("Введите название курса для поиска: ");
                fgets(searchName, sizeof(searchName), stdin);
                int found = 0;
                for (int i = 0; i < courseCount; i++)
                {
                    if (strcmp(courses[i].name, searchName) == 0)
                    {
                        printf("Название: %s", courses[i].name);
                        printf("Преподаватель: %s", courses[i].instructor);
                        printf("Тема: %s", courses[i].tema);
                        printf("Рейтинг: %.2f\n", courses[i].rating);
                        printf("Стоимость: %.2f\n", courses[i].cost);
                        printf("Длительность: %d\n", courses[i].time);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("Курс с указанным названием не найден\n");
                }
            }
            break;
        case 3:
            if (courseCount == 0)
            {
                printf("Нет доступных курсов\n");
            }
            else
            {
                float searchCost;
                printf("Введите стоимость курса для поиска: ");
                scanf("%f", &searchCost);
                int found = 0;
                for (int i = 0; i < courseCount; i++)
                {
                    if (courses[i].cost == searchCost)
                    {
                        printf("Название: %s", courses[i].name);
                        printf("Преподаватель: %s", courses[i].instructor);
                        printf("Тема: %s", courses[i].tema);
                        printf("Рейтинг: %.2f\n", courses[i].rating);
                        printf("Стоимость: %.2f\n", courses[i].cost);
                        printf("Длительность: %d\n", courses[i].time);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("Курсы с указанной стоимостью не найдены\n");
                }
            }
            break;
        case 4:
            if (courseCount == 0) {
                printf("Нет доступных курсов для сортировки\n");
            }
            else {
                bubbleSort(courses, courseCount);
                printf("Курсы успешно отсортированы по рейтингу!\n");
                for (int i = 0; i < courseCount; i++) {
                    printCourse(&courses[i]);
                }
            }
            break;
        case 5:
            if (courseCount > 0) {
                WriteToFile(courses, courseCount);
            }
            else {
                printf("База данных пуста. Нечего записывать в файл.\n");
            }
            break;
        case 6:
            if (courseCount > 0) {
                ReadFromFile(courses, courseCount);
            }
            else {
                printf("База данных пуста. Нечего читать из файла.\n");
            }
            break;
        case 7:
            printf("Выход из программы\n");
            break;
        default:
            printf("Некорректный выбор. Пожалуйста, попробуйте снова\n");
            break;
        }
    } while (choice != 7);
}

void bubbleSort(struct Course arr[], int n) {
    int i, j;
    struct Course temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].rating < arr[j + 1].rating) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void displayWelcomeScreen()
{
    printf("Добро пожаловать в программу управления образовательными курсами!\n");
    printf("_________________________________________________________________\n");
    printf("Меню:\n");
    printf("1. Добавить курс\n");
    printf("2. Поиск курса по названию\n");
    printf("3. Поиск курса по стоимости\n");
    printf("4. Сортировать курсы по рейтингу\n");
    printf("5. Записать в файл\n");
    printf("6. Вывести содержимое файла\n");
    printf("7. Выйти из программы\n");
    printf("-----------------------------------------------------------------\n");
}

void inputCourseInfo(struct Course* course)
{
    printf("Введите название курса: ");
    fgets(course->name, sizeof(course->name), stdin);
    printf("Введите имя преподавателя: ");
    fgets(course->instructor, sizeof(course->instructor), stdin);
    printf("Введите тему курса: ");
    fgets(course->tema, sizeof(course->tema), stdin);
    printf("Введите рейтинг курса: ");
    scanf("%lf", &course->rating);
    getchar();
    printf("Введите стоимость курса: ");
    scanf("%lf", &course->cost);
    getchar();
    printf("Введите длительность курса (в часах): ");
    scanf("%d", &course->time);
    getchar();
}

void printCourse(struct Course* course)
{
    printf("Название: %s", course->name);
    printf("Преподаватель: %s", course->instructor);
    printf("Тема: %s", course->tema);
    printf("Рейтинг: %.2f\n", course->rating);
    printf("Стоимость: %.2f\n", course->cost);
    printf("Длительность: %d\n", course->time);
    printf("------------------------------\n");
}

void WriteToFile(struct Course courses[], int courseCount) {
    FILE* file = fopen("course.txt", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    for (int i = 0; i < courseCount; ++i) {
        fprintf(file, "Название: %s", courses[i].name);
        fprintf(file, "Преподаватель: %s", courses[i].instructor);
        fprintf(file, "Тема: %s", courses[i].tema);
        fprintf(file, "Рейтинг: %.2f\n", courses[i].rating);
        fprintf(file, "Стоимость: %.2f\n", courses[i].cost);
        fprintf(file, "Длительность: %d\n", courses[i].time);
        fprintf(file, "------------------------------\n");
    }
    fclose(file);
    printf("Данные успешно записаны в файл.\n");
}

void ReadFromFile(struct Course courses[], int courseCount)
{
    FILE* file;
    char filename[] = "course.txt";
    char buffer[1000];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка при открытии файла");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}