// student.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void addOrUpdateStudent() {
    struct Student s, temp;
    int found = 0;

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    FILE *fp = fopen("students.dat", "rb");
    
    // First time run, no students.dat
    if (fp == NULL) {
        fp = fopen("students.dat", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        fclose(fp);
        printf("New student added (file created).\n\n");
        return;
    }
    // Normal path: update or add
    FILE *tempfile = fopen("temp.dat", "wb");

    while (fread(&temp, sizeof(temp), 1, fp)) {
        if (temp.roll == s.roll) {
            fwrite(&s, sizeof(s), 1, tempfile);   // Overwrite existing
            found = 1;
        } else {
            fwrite (&temp, sizeof(temp), 1, tempfile);  // keep existing
        }
    }

    if (!found) {
        fwrite(&s, sizeof(s), 1, tempfile);     // Append new
        printf("New student added.\n\n");
    } else {
        printf("Existing student updated.\n\n");
    }

    fclose(fp);
    fclose(tempfile);

    remove("students.dat");
    rename("temp.dat", "students.dat");
}

void viewStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    if (fp == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\nAll Students:\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
    printf("\n");
}

void searchStudent() {
    int roll;
    int found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Found: Roll: %d | Name: %s | Marks: %.2f\n\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with roll %d not found.\n\n", roll);

    fclose(fp);
}

void updateStudent() {
    int roll;
    int found = 0;
    struct Student s;

    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            printf("Student updated successfully!\n\n");
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (!found)
        printf("Student with roll number %d not found.\n\n", roll);
}

void deleteStudent() {
    int roll;
    int found = 0;
    struct Student s;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue; // skip this one
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student deleted successfully.\n\n");
    else
        printf("Student not found.\n\n");
}
