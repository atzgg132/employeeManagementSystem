#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMPLOYEES 1000

// Define the structure for an employee
typedef struct {
    int id;
    char name[100];
    int age;
    float salary;
} Employee;

// Function prototypes
void addEmployee();
void deleteEmployee();
void modifyEmployee();
void viewEmployees();
void searchEmployee();
void sortEmployees();

// File name
const char *filename = "employees.txt";

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Modify Employee\n");
        printf("4. View Employees\n");
        printf("5. Search Employee\n");
        printf("6. Sort Employees\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                modifyEmployee();
                break;
            case 4:
                viewEmployees();
                break;
            case 5:
                searchEmployee();
                break;
            case 6:
                sortEmployees();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Implement the functions declared above
void addEmployee() {
    Employee e;
    FILE *fp;

    fp = fopen(filename, "ab");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter employee ID: ");
    scanf("%d", &e.id);
    printf("Enter name: ");
    scanf("%s", e.name); // Note: This simplistic approach does not handle spaces in names
    printf("Enter age: ");
    scanf("%d", &e.age);
    printf("Enter salary: ");
    scanf("%f", &e.salary);

    fwrite(&e, sizeof(Employee), 1, fp);

    fclose(fp);
}

// Delete Employee Function

void deleteEmployee() {
    int id;
    Employee e;
    FILE *fp, *temp;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        return;
    }

    printf("Enter employee ID to delete: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(Employee), 1, fp)) {
        if (e.id != id) {
            fwrite(&e, sizeof(Employee), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    printf("Employee deleted successfully\n");
}

// Modify Employee Function

void modifyEmployee() {
  int id;
  Employee e;
  FILE *fp, *temp;

  fp = fopen(filename, "rb+");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  printf("Enter employee ID to modify: ");
  scanf("%d", &id);

  while (fread(&e, sizeof(Employee), 1, fp)) {
    if (e.id == id) {
      printf("Enter new name: ");
      scanf("%s", e.name);
      printf("Enter new age: ");
      scanf("%d", &e.age);
      printf("Enter new salary: ");
      scanf("%f", &e.salary);

      fseek(fp, -sizeof(Employee), SEEK_CUR);
      fwrite(&e, sizeof(Employee), 1, fp);
      break;
    }
  }

  fclose(fp);

  printf("Employee modified successfully\n");
}

void viewEmployees() {
    Employee e;
    FILE *fp;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&e, sizeof(Employee), 1, fp)) {
        printf("\nID: %d", e.id);
        printf("\nName: %s", e.name);
        printf("\nAge: %d", e.age);
        printf("\nSalary: %.2f\n", e.salary);
    }

    fclose(fp);
}

// Search Employee Function

void searchEmployee() {
  int id;
  Employee e;
  FILE *fp;

  fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  printf("Enter employee ID to search: ");
  scanf("%d", &id);

  while (fread(&e, sizeof(Employee), 1, fp)) {
    if (e.id == id) {
      printf("\nID: %d", e.id);
      printf("\nName: %s", e.name);
      printf("\nAge: %d", e.age);
      printf("\nSalary: %.2f\n", e.salary);
      fclose(fp);
      return;
    }
  }

  printf("Employee not found\n");
  fclose(fp);
}

// Sort Employee Function

void sortEmployees() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    FILE *fp;

    // Open the file for reading
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Read employees from file into array
    while (fread(&employees[numEmployees], sizeof(Employee), 1, fp) == 1) {
        numEmployees++;
    }
    fclose(fp);

    // Sort employees by ID using bubble sort
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (employees[j].id > employees[j + 1].id) {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }

    // Open the file for writing
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Write sorted employees back to file
    for (int i = 0; i < numEmployees; i++) {
        fwrite(&employees[i], sizeof(Employee), 1, fp);
    }
    fclose(fp);

    printf("Employees sorted successfully\n");
}