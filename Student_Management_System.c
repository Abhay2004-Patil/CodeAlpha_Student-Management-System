#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {

    int choice;

    while(1) {

        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Program Exited Successfully.\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

// Function to Add Student
void addStudent() {

    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "ab");

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student Record Added Successfully.\n");
}

// Function to Display Students
void displayStudents() {

    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "rb");

    if(fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    while(fread(&s, sizeof(s), 1, fp)) {

        printf("Roll Number : %d\n", s.roll);
        printf("Name        : %s\n", s.name);
        printf("Marks       : %.2f\n", s.marks);
        printf("----------------------------\n");
    }

    fclose(fp);
}

// Function to Search Student
void searchStudent() {

    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "rb");

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.roll == roll) {

            printf("\nStudent Found\n");
            printf("Roll Number : %d\n", s.roll);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Student Record Not Found!\n");
    }

    fclose(fp);
}

// Function to Update Student
void updateStudent() {

    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "rb+");

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.roll == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);

            fwrite(&s, sizeof(s), 1, fp);

            printf("Record Updated Successfully.\n");

            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Record Not Found!\n");
    }

    fclose(fp);
}

// Function to Delete Student
void deleteStudent() {

    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "rb");
    temp = fopen("temp.txt", "wb");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.roll == roll) {

            found = 1;
        }
        else {

            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found) {
        printf("Record Deleted Successfully.\n");
    }
    else {
        printf("Record Not Found!\n");
    }
}