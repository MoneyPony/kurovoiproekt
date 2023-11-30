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
        printf("������� ��� �����: ");
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
                printf("���� ������� ��������!\n");
            }
            else
            {
                printf("���������� ������������ ���������� ������!\n");
            }
            break;
        case 2:
            if (courseCount == 0)
            {
                printf("��� ��������� ������\n");
            }
            else
            {
                char searchName[50];
                printf("������� �������� ����� ��� ������: ");
                fgets(searchName, sizeof(searchName), stdin);
                int found = 0;
                for (int i = 0; i < courseCount; i++)
                {
                    if (strcmp(courses[i].name, searchName) == 0)
                    {
                        printf("��������: %s", courses[i].name);
                        printf("�������������: %s", courses[i].instructor);
                        printf("����: %s", courses[i].tema);
                        printf("�������: %.2f\n", courses[i].rating);
                        printf("���������: %.2f\n", courses[i].cost);
                        printf("������������: %d\n", courses[i].time);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("���� � ��������� ��������� �� ������\n");
                }
            }
            break;
        case 3:
            if (courseCount == 0)
            {
                printf("��� ��������� ������\n");
            }
            else
            {
                float searchCost;
                printf("������� ��������� ����� ��� ������: ");
                scanf("%f", &searchCost);
                int found = 0;
                for (int i = 0; i < courseCount; i++)
                {
                    if (courses[i].cost == searchCost)
                    {
                        printf("��������: %s", courses[i].name);
                        printf("�������������: %s", courses[i].instructor);
                        printf("����: %s", courses[i].tema);
                        printf("�������: %.2f\n", courses[i].rating);
                        printf("���������: %.2f\n", courses[i].cost);
                        printf("������������: %d\n", courses[i].time);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("����� � ��������� ���������� �� �������\n");
                }
            }
            break;
        case 4:
            if (courseCount == 0) {
                printf("��� ��������� ������ ��� ����������\n");
            }
            else {
                bubbleSort(courses, courseCount);
                printf("����� ������� ������������� �� ��������!\n");
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
                printf("���� ������ �����. ������ ���������� � ����.\n");
            }
            break;
        case 6:
            if (courseCount > 0) {
                ReadFromFile(courses, courseCount);
            }
            else {
                printf("���� ������ �����. ������ ������ �� �����.\n");
            }
            break;
        case 7:
            printf("����� �� ���������\n");
            break;
        default:
            printf("������������ �����. ����������, ���������� �����\n");
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
    printf("����� ���������� � ��������� ���������� ���������������� �������!\n");
    printf("_________________________________________________________________\n");
    printf("����:\n");
    printf("1. �������� ����\n");
    printf("2. ����� ����� �� ��������\n");
    printf("3. ����� ����� �� ���������\n");
    printf("4. ����������� ����� �� ��������\n");
    printf("5. �������� � ����\n");
    printf("6. ������� ���������� �����\n");
    printf("7. ����� �� ���������\n");
    printf("-----------------------------------------------------------------\n");
}

void inputCourseInfo(struct Course* course)
{
    printf("������� �������� �����: ");
    fgets(course->name, sizeof(course->name), stdin);
    printf("������� ��� �������������: ");
    fgets(course->instructor, sizeof(course->instructor), stdin);
    printf("������� ���� �����: ");
    fgets(course->tema, sizeof(course->tema), stdin);
    printf("������� ������� �����: ");
    scanf("%lf", &course->rating);
    getchar();
    printf("������� ��������� �����: ");
    scanf("%lf", &course->cost);
    getchar();
    printf("������� ������������ ����� (� �����): ");
    scanf("%d", &course->time);
    getchar();
}

void printCourse(struct Course* course)
{
    printf("��������: %s", course->name);
    printf("�������������: %s", course->instructor);
    printf("����: %s", course->tema);
    printf("�������: %.2f\n", course->rating);
    printf("���������: %.2f\n", course->cost);
    printf("������������: %d\n", course->time);
    printf("------------------------------\n");
}

void WriteToFile(struct Course courses[], int courseCount) {
    FILE* file = fopen("course.txt", "w");
    if (file == NULL) {
        printf("�� ������� ������� ���� ��� ������.\n");
        return;
    }
    for (int i = 0; i < courseCount; ++i) {
        fprintf(file, "��������: %s", courses[i].name);
        fprintf(file, "�������������: %s", courses[i].instructor);
        fprintf(file, "����: %s", courses[i].tema);
        fprintf(file, "�������: %.2f\n", courses[i].rating);
        fprintf(file, "���������: %.2f\n", courses[i].cost);
        fprintf(file, "������������: %d\n", courses[i].time);
        fprintf(file, "------------------------------\n");
    }
    fclose(file);
    printf("������ ������� �������� � ����.\n");
}

void ReadFromFile(struct Course courses[], int courseCount)
{
    FILE* file;
    char filename[] = "course.txt";
    char buffer[1000];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("������ ��� �������� �����");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}