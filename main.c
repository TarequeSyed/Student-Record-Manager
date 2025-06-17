#include <stdio.h>
#include <string.h>

#define MAX 100

// Using Typedef, I named this all 's', so next time, I want to define this structure, I will just type 's'.
typedef struct {                         
    char name[50];                              
    int roll;
    float marks;
} S;                                      

// Function to add Students:

void AddStudents() {
    S students;
    printf("Enter roll number: ");
    scanf(" %d", &students.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", students.name);    // To read full lines with spaces.
    
    printf("Enter Marks: ");
    scanf("%f", &students.marks);

    // Save data to file (in binary):
    FILE *fl = fopen("students.dat", "ab");          // ab = append in binary
    if (fl == NULL) {
        printf("Error opening file!!!\n");
        return;
    }


    fwrite (&students, sizeof(S), 1, fl);
    fclose(fl);
    printf("Student data added and saved successfully.\n\n");

} 

// Function to display menu:
void DisplayMenu () {
    printf("========Student Record Manager========\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Students\n");
    printf("4. Update Student's Data\n");
    printf("5. Delete Student's Data\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

// View all student:
void ViewStudents () {
    S students;
    FILE *fl = fopen("students.dat", "rb");     // Read in binary.

    if (fl == NULL) {
        printf("Error reading this file!");
        return;
    }
    printf("\n-------------Students Record------------------\n");
    while (fread (&students, sizeof(students), 1, fl)) {
        printf("Roll: %d\n", students.roll);
        printf("Name: %s\n", students.name);
        printf("Marks: %.2f\n\n", students.marks);
    }
    fclose(fl);
    
}

// Search Student:
void SearchStudent() {
    FILE *fl = fopen("students.dat", "rb");
    int roll, found = 0;
    S students;

    if (fl == NULL) {
        printf("Error opening the file!!");
        return;
    }
    printf("Enter the roll number of the student you want to search: ");
    scanf(" %d", &roll);

    while (fread (&students, sizeof(S), 1, fl)) {
        if (students.roll == roll) {
            printf("\nStudent Found:\n");
            printf("Roll number: %d\nName: %s\nMarks: %.2f\n", students.roll, students.name, students.marks);
            found = 1;
            break;
        }
    }
    fclose(fl);
   
    if (!found) {
        printf("Student with roll number %d is not found!!!", roll);
    }

}
// Update student data:            (You can also do similar like 'deleting data' code here)
void UpdateStudent() {
    FILE *fl = fopen("students.dat", "rb");
    int roll, found = 0;
    S students;
    if (fl == NULL) {
        printf("Error reading the file!!!");
        return;
    }
   
    printf("Enter student's Roll number to update: ");
    scanf(" %d", &roll);
    while (fread (&students, sizeof(S), 1, fl)) {
        if (students.roll == roll) {
            printf("\nCurrent Data:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n\n", students.roll, students.name, students.marks);

            printf("Enter new name: ");
            scanf( "%[^\n]", students.name);
            printf("Enter new marks: ");
            scanf("%d", &students.marks);

            // Move back one character
            fseek (fl, - sizeof(S), SEEK_CUR);
            // Overwrite update struct:
            fwrite (&students, sizeof(S), 1, fl);
            printf("Records updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("The student with roll number %d is not found!!!", roll);
    }
    fclose(fl);
}

// Deleting Students Data: 
void DeleteStudent() {
    S students;
    int roll, found = 0;
    FILE *fl = fopen ("students.dat", "rb");
    FILE *temp = fopen ("temp.dat", "wb");

    if (fl == NULL || temp == NULL) {
        printf("Error opening the files!\n");
        return;
    }
    
    printf("Enter the student's roll number of which data you want to delete: ");
    scanf("%d", &roll);

    while (fread (&students, sizeof(S), 1, fl)) {
        if (students.roll == roll) {
            printf("\ncurrent Data\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n\n", students.roll, students.name, students.marks);
            printf("Mentioned Student's Data Deleted.\n");
            found = 1;
            continue;    // Skip writing this student.
        }
        fwrite (&students, sizeof(S), 1, temp);  // Copy everything else.
    }
    fclose(fl);
    fclose(temp);

    remove("students.dat");         // Remove the original file
    rename("temp.dat", "students.dat");   // Rename the temp file as original file

    if (!found) {
        printf("Student with %d roll number is not found!!!", roll) ;
    }
}

int main() {
    int choice;

    while(1) {
        DisplayMenu();
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                AddStudents();
                break;
            case 2:
                ViewStudents();
                break;
            case 3:
                SearchStudent();
                break;
            case 4:                                                         
                UpdateStudent();
                break;
            case 5:
                DeleteStudent();
            case 6:
                printf("Exitting the system...");
                return 0;
            default:
                printf("Invalid choice, try again!\n\n");
        }
    }
    return 0;
}

