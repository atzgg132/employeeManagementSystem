# Employee Management System

This comprehensive documentation covers the functionalities of the Employee Management System. This console-based application is designed for effective management of employee records, enabling operations like add, delete, modify, view, search, and sort.

## Data Structure Description

- **id**: Unique identifier for each employee. It's an integer that auto-increments for every new employee added, ensuring uniqueness.
- **name**: The employee's full name. This field can accommodate up to 99 characters, allowing for a broad range of names.
- **age**: Represents the employee's age. The system only accepts positive integers for this field.
- **salary**: The salary of the employee. This system ensures that the salary is a non-negative value, aligning with real-world expectations.

## Functionalities

### Add Employee (`void addEmployee()`)

Allows users to input new employee details and adds them to the system.

- **ID Generation**: Automatically assigns the next available unique ID.
- **Name Input**: Requests the user's name and ensures it doesn't exceed the buffer limit.
- **Age Input**: Ensures the user inputs a valid, positive integer for the age.
- **Salary Input**: Validates that the entered salary is a non-negative number.
- **File Writing**: Appends the new employee record to the file.

### Delete Employee (`void deleteEmployee()`)

Enables users to delete an employee record either by ID or name.

- **Selection Mechanism**: Users can choose to delete by ID or name.
- **Deletion by ID**: Directly finds and deletes the record with the matching ID.
- **Deletion by Name**: Lists all employees matching the input name (case-insensitive) and asks for the specific ID to delete, handling multiple records with identical names.
- **File Handling**: Creates a temporary file to store non-deleted records and replaces the original file.

### Modify Employee (`void modifyEmployee()`)

Allows users to update details for an existing employee identified by their ID.

- **Employee Search**: Finds the employee by ID.
- **Data Modification**: Users can update the name, age, and salary, with validations similar to the `addEmployee` function.
- **Record Update**: Writes the updated details back to the file at the correct position.

### View Employees (`void viewEmployees()`)

Displays all employee records in a readable format, showing ID, name, age, and salary.

- **Sequential Reading**: Reads the employee file sequentially and displays each record.

### Search Employee (`void searchEmployee()`)

Facilitates searching for employees using ID or name, supporting partial and case-insensitive name matches.

- **Search by ID**: Finds and displays the employee with the exact ID.
- **Search by Name**: Displays all employees whose names contain the input string, ignoring case differences.

### Sort Employees (`void sortEmployees()`)

Allows users to sort employee records based on different criteria in ascending or descending order.

- **Sorting Options**: Users can sort by ID, name, age, or salary.
- **Order Selection**: Users can choose ascending or descending order.
- **Sorting Algorithm**: Implements a bubble sort to reorder the records based on the selected criterion and order.

### Utility Functions

- **`int getMaxId()`**: Scans existing records to determine the highest ID, supporting the unique ID assignment.
- **`bool shouldSwap(Employee a, Employee b, int choice, bool descending)`**: Determines whether two records should be swapped during sorting.
- **`void toLowerCase(const char *input, char *lower)`**: Converts a string to lowercase, aiding in case-insensitive comparisons.
- **`void displayEmployee(Employee e)`**: Utility function to display an employee's details in a structured format.

## Edge Case Handling

- Input validation ensures that only logical and valid data is accepted (e.g., positive age, non-negative salary).
- Deletion and modification functions handle cases where the specified employee does not exist.
- Search and sort functionalities are designed to be intuitive and flexible, accommodating various user needs.

## File Management

- The system relies on a file (`employees.txt`) for persistent storage of employee records.
- Careful file handling ensures data integrity and system reliability.

## User Interaction

- A user-friendly console-based menu guides the user through various operations, ensuring ease of use and clarity.
