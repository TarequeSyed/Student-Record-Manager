// student.h
#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void addOrUpdateStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

#endif
