#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student 
{
    int rollNo;
    char name[50];
    float marks;
    struct Student* next;
};
struct Student* createStudent(int rollNo, char* name, float marks) 
{
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newStudent->rollNo = rollNo;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}
void addStudent(struct Student** head, int rollNo, char* name, float marks) 
{
    struct Student* newStudent = createStudent(rollNo, name, marks);
    if (*head == NULL) 
    {
        *head = newStudent;
        return;
    }
    struct Student* temp = *head;
    while (temp->next != NULL) 
    {
        temp = temp->next;
    }
    temp->next = newStudent;
}
void deleteStudent(struct Student** head, int rollNo) 
{
    struct Student* temp = *head;
    struct Student* prev = NULL;
    // If the node to be deleted is the head node
    if (temp != NULL && temp->rollNo == rollNo) 
    {
        *head = temp->next;
        free(temp);
        return;
    }
    // Search for the node to be deleted
    while (temp != NULL && temp->rollNo != rollNo) 
    {
        prev = temp;
        temp = temp->next;
    }
    // If the roll number was not found
    if (temp == NULL) return;
    // Unlink the node from the linked list
    prev->next = temp->next;
    free(temp);
}
struct Student* searchStudent(struct Student* head, int rollNo) 
{
    struct Student* temp = head;
    while (temp != NULL) 
    {
        if (temp->rollNo == rollNo) 
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void displayStudents(struct Student* head) 
{
    struct Student* temp = head;
    while (temp != NULL) 
    {
        printf("Roll No: %d\n", temp->rollNo);
        printf("Name: %s\n", temp->name);
        printf("Marks: %.2f\n\n", temp->marks);
        temp = temp->next;
    }
}
void updateStudentMarks(struct Student* head, int rollNo, float newMarks) 
{
    struct Student* student = searchStudent(head, rollNo);
    if (student != NULL) {
        student->marks = newMarks;
    } else {
        printf("Student with roll number %d not found.\n", rollNo);
    }
}
void freeAllStudents(struct Student* head) 
{
    struct Student* temp;
    while (head != NULL) 
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main() 
{
    struct Student* head = NULL;
    int choice, rollNo;
    char name[50];
    float marks;
    while (1) 
    {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Search Student\n");
        printf("4. Display All Students\n");
        printf("5. Update Student Marks\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                printf("Enter Roll No: ");
                scanf("%d", &rollNo);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Marks: ");
                scanf("%f", &marks);
                addStudent(&head, rollNo, name, marks);
                break;
            case 2:
                printf("Enter Roll No to Delete: ");
                scanf("%d", &rollNo);
                deleteStudent(&head, rollNo);
                break;
            case 3:
                printf("Enter Roll No to Search: ");
                scanf("%d", &rollNo);
                struct Student* student = searchStudent(head, rollNo);
                if (student != NULL) 
                {
                    printf("Roll No: %d\n", student->rollNo);
                    printf("Name: %s\n", student->name);
                    printf("Marks: %.2f\n", student->marks);
                } 
                else 
                {
                    printf("Student not found.\n");
                }
                break;
            case 4:
                displayStudents(head);
                break;
            case 5:
                printf("Enter Roll No to Update: ");
                scanf("%d", &rollNo);
                printf("Enter New Marks: ");
                scanf("%f", &marks);
                updateStudentMarks(head, rollNo, marks);
                break;
            case 6:
                freeAllStudents(head);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}