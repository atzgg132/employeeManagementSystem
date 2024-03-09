#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
int getMaxId();
bool shouldSwap(Employee a, Employee b, int choice, bool descending);
void toLowerCase(const char *input, char *lower);
void displayEmployee(Employee e);

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

    e.id = getMaxId() + 1;
    printf("Employee ID assigned: %d\n", e.id);

    // Validate Name
    printf("Enter name: ");
    getchar(); // Consume the leftover newline character
    scanf("%[^\n]%*c", e.name);
    // Add additional name validation if necessary

    // Validate Age
    int ageInputValid = 0;
    while (!ageInputValid) {
        printf("Enter age: ");
        if (scanf("%d", &e.age) != 1 || e.age <= 0) {
            printf("Invalid input. Please enter a positive integer for age.\n");
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            ageInputValid = 1;
        }
    }

    // Validate Salary
    int salaryInputValid = 0;
    while (!salaryInputValid) {
        printf("Enter salary: ");
        if (scanf("%f", &e.salary) != 1 || e.salary < 0) {
            printf("Invalid input. Please enter a positive number for salary.\n");
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            salaryInputValid = 1;
        }
    }

    fwrite(&e, sizeof(Employee), 1, fp);
    fclose(fp);
}

int getMaxId() {
    Employee e;
    int maxId = 0;
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return 0; // If the file doesn't exist or is empty, start IDs from 1
    }

    while (fread(&e, sizeof(Employee), 1, fp) == 1) {
        if (e.id > maxId) {
            maxId = e.id;
        }
    }

    fclose(fp);
    return maxId;
}

// Delete Employee Function

void deleteEmployee() {
    int deleteOption, id, choice, found = 0;
    char name[100], lowerName[100], lowerEmployeeName[100];
    Employee e;
    FILE *fp, *temp;
    int matchedIDs[MAX_EMPLOYEES], matchedCount = 0;

    printf("Delete by: \n1. ID\n2. Name\nEnter your choice: ");
    scanf("%d", &deleteOption);

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

    if (deleteOption == 1) {
        printf("Enter employee ID to delete: ");
        scanf("%d", &id);
        while (fread(&e, sizeof(Employee), 1, fp)) {
            if (e.id != id) {
                fwrite(&e, sizeof(Employee), 1, temp);
            } else {
                found = 1;
            }
        }
    } else if (deleteOption == 2) {
        printf("Enter employee name to delete: ");
        getchar(); // Consume the leftover newline character
        scanf("%[^\n]%*c", name);
        toLowerCase(name, lowerName);

        while (fread(&e, sizeof(Employee), 1, fp)) {
            toLowerCase(e.name, lowerEmployeeName);
            if (strstr(lowerEmployeeName, lowerName) == NULL) {
                fwrite(&e, sizeof(Employee), 1, temp);
            } else {
                matchedIDs[matchedCount++] = e.id;
                printf("Found: ID %d, Name: %s, Age: %d, Salary: %.2f\n", e.id, e.name, e.age, e.salary);
            }
        }

        if (matchedCount > 1) {
            printf("Multiple records found. Enter the ID of the employee to delete: ");
            scanf("%d", &id);
            rewind(fp);
            rewind(temp);
            freopen("temp.txt", "wb", temp); // Reopen temp file to start over

            while (fread(&e, sizeof(Employee), 1, fp)) {
                if (e.id != id) {
                    fwrite(&e, sizeof(Employee), 1, temp);
                } else {
                    found = 1;
                }
            }
        } else if (matchedCount == 1) {
            found = 1;
        }
    } else {
        printf("Invalid delete option.\n");
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    if (found) {
        printf("Employee deleted successfully.\n");
    } else {
        printf("Employee not found.\n");
    }
}

// Modify Employee Function

void modifyEmployee() {
    int id;
    Employee e;
    FILE *fp;
    int found = 0;

    fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter employee ID to modify: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(Employee), 1, fp) && !found) {
        if (e.id == id) {
            found = 1;
            printf("Enter new name: ");
            getchar(); // Consume the leftover newline character
            scanf("%[^\n]%*c", e.name);
            
            // Validate Age
            int ageInputValid = 0;
            while (!ageInputValid) {
                printf("Enter new age: ");
                if (scanf("%d", &e.age) != 1 || e.age <= 0) {
                    printf("Invalid input. Please enter a positive integer for age.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                } else {
                    ageInputValid = 1;
                }
            }

            // Validate Salary
            int salaryInputValid = 0;
            while (!salaryInputValid) {
                printf("Enter new salary: ");
                if (scanf("%f", &e.salary) != 1 || e.salary < 0) {
                    printf("Invalid input. Please enter a positive number for salary.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                } else {
                    salaryInputValid = 1;
                }
            }

            // Go back and update the record
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&e, sizeof(Employee), 1, fp);
            printf("Employee modified successfully\n");
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(fp);
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
    int searchOption;
    char name[100], inputName[100], lowerName[100];
    Employee e;
    FILE *fp;
    int found = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Search by: \n1. ID\n2. Name\nEnter your choice: ");
    scanf("%d", &searchOption);

    if (searchOption == 1) {
        int id;
        printf("Enter employee ID to search: ");
        scanf("%d", &id);

        while (fread(&e, sizeof(Employee), 1, fp)) {
            if (e.id == id) {
                displayEmployee(e);
                found = 1;
                break;
            }
        }
    } else if (searchOption == 2) {
        printf("Enter employee name to search: ");
        getchar(); // Consume the leftover newline character
        scanf("%[^\n]%*c", inputName);
        toLowerCase(inputName, lowerName);

        while (fread(&e, sizeof(Employee), 1, fp)) {
            toLowerCase(e.name, name);
            if (strstr(name, lowerName) != NULL) {
                displayEmployee(e);
                found = 1;
            }
        }
    } else {
        printf("Invalid search option.\n");
    }

    if (!found) {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

void toLowerCase(const char *input, char *lower) {
    while (*input) {
        *lower = tolower((unsigned char) *input);
        lower++;
        input++;
    }
    *lower = 0;
}

void displayEmployee(Employee e) {
    printf("\nID: %d", e.id);
    printf("\nName: %s", e.name);
    printf("\nAge: %d", e.age);
    printf("\nSalary: %.2f\n", e.salary);
}


// Sort Employee Function

void sortEmployees() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    FILE *fp;
    int choice, order;
    bool descending = false;

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

    printf("Sort by: \n1. ID\n2. Name\n3. Age\n4. Salary\nEnter your choice: ");
    scanf("%d", &choice);
    printf("Order:\n1. Ascending\n2. Descending\nEnter your choice: ");
    scanf("%d", &order);
    if (order == 2) {
        descending = true;
    }

    // Sort employees based on user choice
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (shouldSwap(employees[j], employees[j + 1], choice, descending)) {
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

bool shouldSwap(Employee a, Employee b, int choice, bool descending) {
    bool swap = false;
    switch (choice) {
        case 1: // ID
            swap = descending ? a.id < b.id : a.id > b.id;
            break;
        case 2: // Name
            swap = descending ? strcmp(a.name, b.name) < 0 : strcmp(a.name, b.name) > 0;
            break;
        case 3: // Age
            swap = descending ? a.age < b.age : a.age > b.age;
            break;
        case 4: // Salary
            swap = descending ? a.salary < b.salary : a.salary > b.salary;
            break;
        default:
            printf("Invalid choice for sorting.\n");
            break;
    }
    return swap;
}
