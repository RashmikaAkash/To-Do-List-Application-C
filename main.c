#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Todo {
    char task[100];
    struct Todo* next;
} Todo;

Todo* head = NULL;

void addTask(const char* task) {
    Todo* newTask = (Todo*)malloc(sizeof(Todo));
    strcpy(newTask->task, task);
    newTask->next = head;
    head = newTask;
    printf("Task added successfully!\n");
}

void deleteTask(const char* task) {
    Todo *temp = head, *prev = NULL;

    if (temp != NULL && strcmp(temp->task, task) == 0) {
        head = temp->next;
        free(temp);
        printf("Task deleted successfully!\n");
        return;
    }

    while (temp != NULL && strcmp(temp->task, task) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Task not found!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Task deleted successfully!\n");
}

void displayTasks() {
    Todo* temp = head;
    if (temp == NULL) {
        printf("No tasks in the list.\n");
        return;
    }
    printf("Todo List:\n");
    while (temp != NULL) {
        printf("- %s\n", temp->task);
        temp = temp->next;
    }
}

void saveToFile() {
    FILE* file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Unable to open file for saving.\n");
        return;
    }

    Todo* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s\n", temp->task);
        temp = temp->next;
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

void loadFromFile() {
    FILE* file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No tasks to load.\n");
        return;
    }

    char task[100];
    while (fgets(task, sizeof(task), file)) {
        task[strcspn(task, "\n")] = 0;  // Remove newline character
        addTask(task);
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}

int main() {
    int choice;
    char task[100];

    loadFromFile(); // Load tasks from file when the program starts

    while (1) {
        printf("\nTodo List Application\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Display Tasks\n");
        printf("4. Save to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character from input buffer

        switch (choice) {
            case 1:
                printf("Enter the task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline character
                addTask(task);
                break;
            case 2:
                printf("Enter the task to delete: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = 0;  // Remove newline character
                deleteTask(task);
                break;
            case 3:
                displayTasks();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                saveToFile(); // Save before exiting
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

