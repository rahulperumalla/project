#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char branch[30];
};

// Function prototypes
void addStudent(FILE *fp);
void displayStudents(FILE *fp);
void removeStudent();
void editStudent();
void clearScreen();
void printHeader();

int main() {
    FILE *fp;
    int choice;

    while (1) {
        clearScreen();
        printHeader();

        printf("1. View All Students\n");
        printf("2. Add New Student\n");
        printf("3. Remove Student\n");
        printf("4. Edit Student Details\n");
        printf("5. Exit Program\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fp = fopen("students.txt", "r");
                if (fp == NULL) {
                    printf("\nNo records found!\n");
                } else {
                    displayStudents(fp);
                    fclose(fp);
                }
                break;

            case 2:
                fp = fopen("students.txt", "a");
                if (fp == NULL) {
                    printf("\nError opening file!\n");
                    break;
                }
                addStudent(fp);
                fclose(fp);
                break;

            case 3:
                removeStudent();
                break;

            case 4:
                editStudent();
                break;

            case 5:
                printf("\nExiting program... Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    return 0;
}

void addStudent(FILE *fp) {
    struct Student *s = (struct Student *)malloc(sizeof(struct Student));

    clearScreen();
    printHeader();
    printf("--- Add New Student ---\n");

    printf("Enter ID: ");
    scanf("%d", &s->id);
    printf("Enter Name: ");
    scanf(" %s[^\n]", s->name);
    printf("Enter Age: ");
    scanf("%d", &s->age);
    printf("Enter Branch: ");
    scanf(" %s[^\n]", s->branch);

    fprintf(fp, "%d %s %d %s\n", s->id, s->name, s->age, s->branch);
    printf("\nStudent added successfully!\n");

    free(s);
}

void displayStudents(FILE *fp) {
    struct Student s;
    clearScreen();
    printHeader();

    printf("--- Student List ---\n");

    int count = 0;
    while (fscanf(fp, "%d %s %d %s", &s.id, s.name, &s.age, s.branch) == 4) {
        printf("\nStudent #%d\n", ++count);
        printf("ID     : %d\n", s.id);
        printf("Name   : %s\n", s.name);
        printf("Age    : %d\n", s.age);
        printf("Branch : %s\n", s.branch);
        printf("----------------------------\n");
    }

    if (count == 0)
        printf("\nNo student records available.\n");
}

void removeStudent() {
    struct Student s;
    FILE *fp, *temp;
    int id, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("\nNo records to delete.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    clearScreen();
    printHeader();

    printf("Enter Student ID to remove: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %s", &s.id, s.name, &s.age, s.branch) == 4) {
        if (s.id != id)
            fprintf(temp, "%d %s %d %s\n", s.id, s.name, s.age, s.branch);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("\nStudent record deleted successfully!\n");
    else
        printf("\nStudent ID not found!\n");
}

void editStudent() {
    struct Student s;
    FILE *fp, *temp;
    int id, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    clearScreen();
    printHeader();

    printf("Enter Student ID to edit: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %s", &s.id, s.name, &s.age, s.branch) == 4) {
        if (s.id == id) {
            found = 1;
            printf("\nEnter new details for student ID %d:\n", id);
            printf("Enter Name: ");
            scanf(" %s[^\n]", s.name);
            printf("Enter Age: ");
            scanf("%d", &s.age);
            printf("Enter Branch: ");
            scanf(" %s[^\n]", s.branch);
        }
        fprintf(temp, "%d %s %d %s\n", s.id, s.name, s.age, s.branch);
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("\nStudent details updated successfully!\n");
    else
        printf("\nStudent ID not found!\n");
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader() {
    printf("=====================================\n");
    printf("       STUDENT MANAGEMENT SYSTEM     \n");
    printf("=====================================\n\n");
}