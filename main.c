#include <stdio.h>
#include "student.c"

void DisplayMenu() {
    printf("========Student Record Manager========\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Students\n");
    printf("4. Update Student's Data\n");
    printf("5. Delete Student's Data\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    
    while(1) {
        DisplayMenu();
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                addOrUpdateStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:                                                         
                updateStudent();
                break;
            case 5:
                deleteStudent();
            case 6:
                printf("Exitting the system...");
                return 0;
            default:
                printf("Invalid choice, try again!\n\n");
        }
    }
    return 0;
}

