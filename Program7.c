// Write a C program to sort the info of n students based on CGPA


#include <stdio.h>
#include <string.h>

struct student {
    char name[50];
    int roll_no;
    int age;
    float cgpa;
};

void inputStudents(struct student s[], int n) {
    for(int i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Name: ");
        scanf(" %[^\n]s", s[i].name);

        printf("Roll No: ");
        scanf("%d", &s[i].roll_no);

        printf("Age: ");
        scanf("%d", &s[i].age);

        printf("CGPA: ");
        scanf("%f", &s[i].cgpa);
    }
}

void sortByCGPA(struct student s[], int n) {
    struct student temp;

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(s[j].cgpa < s[j + 1].cgpa) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void displayStudents(struct student s[], int n) {
    printf("\n--- Students Sorted by CGPA ---\n");

    for(int i = 0; i < n; i++) {
        printf("\nName: %s", s[i].name);
        printf("\nRoll No: %d", s[i].roll_no);
        printf("\nAge: %d", s[i].age);
        printf("\nCGPA: %.2f\n", s[i].cgpa);
    }
}

int main() {
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    struct student s[n];

    inputStudents(s, n);
    sortByCGPA(s, n);
    displayStudents(s, n);

    return 0;
}