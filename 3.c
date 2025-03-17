#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 100
struct Task{
    char description[MAX_DESCRIPTION_LENGTH];
    bool completed;
};
void displayTasks(const struct Task* tasks, size_t size){
    printf("Task list: \n");
    for(size_t i=0; i<size; ++i){
        printf("[%zu] %s %s\n", i+1, tasks[i].completed ? "[Completed]" : "[Pending]", tasks[i].description);
    }
}
void addTask(struct Task* tasks, size_t* size, const char* description){
    if(*size >= MAX_TASKS){
        printf("Error: Task list is full.\n");
        return;
    }
    struct Task newTask = {.completed = false};
    strncpy(newTask.description, description, MAX_DESCRIPTION_LENGTH - 1);
    tasks[(*size)++] = newTask;
}
void editTask(struct Task* tasks, size_t size, size_t taskIndex, const char* newDescription){
    if(taskIndex < size){
        strncpy(tasks[taskIndex].description, newDescription, MAX_DESCRIPTION_LENGTH -1);
    }else{
        printf("Invalid task index.\n");
    }
}
void completeTask(struct Task* tasks, size_t size, size_t taskIndex){
 if(taskIndex < size){
        tasks[taskIndex].completed = true;
    }else{
        printf("Invalid task index.\n");
    }
}
void saveTasks(const struct Task* tasks, size_t size, const char* filename){
    FILE* file = fopen(filename, "w");
    if(file != NULL){
        for(size_t i=0; i<size; ++i){
            fprintf(file, "%d %s\n", tasks[i].completed, tasks[i].description);
        }
        fclose(file);
    }else{
        printf("Error: Unable to save tasks to file,\n");
    }
}
void loadTasks(struct Task* tasks, size_t* size, const char* filename){
    FILE* file = fopen(filename,"r");
    if(file != NULL){
        *size = 0;
        while(fscanf(file, "%d", &tasks[*size].completed) != EOF){
            fgets(tasks[*size].description, MAX_DESCRIPTION_LENGTH, file);
tasks[*size].description[strcspn(tasks[*size].description, "\n")] = '\0';  // Remove trailing newline
            (*size)++;
        }
        fclose(file);
    }else{
        printf("Error: Unable to load tasks from file.\n");
    }
}
int main()
{
    struct Task tasks[MAX_TASKS];
    size_t size = 0;
    const char* filename = "task_history.txt";
    loadTasks(tasks, &size, filename);
    while(1){
        printf("\nOPTIONS:\n");
        printf("1. Display Tasks\n");
        printf("2. Add Tasks\n");
        printf("3. Edit Tasks\n");
        printf("4. Complete Task\n");
        printf("5. Save and Quit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
              displayTasks(tasks, size);
              break;
            case 2:
            {
                char description[MAX_DESCRIPTION_LENGTH];
                printf("Enter task description: ");
                getchar();
                scanf("%[^\n]", description);
                addTask(tasks, &size, description);
                break;
            }
            case 3:
            {
                size_t taskIndex;
                char newDescription[MAX_DESCRIPTION_LENGTH];
                printf("Enter task index to edit: ");                scanf("%zu", &taskIndex);
                printf("Enter new task description: ");
                getchar();
                scanf("%[^\n]", newDescription);
                editTask(tasks, size, taskIndex -1, newDescription);
                break;
            }
            case 4:
            {
                size_t taskIndex;
                printf("Enter task index to mark as completed: ");
                scanf("%zu", &taskIndex);
                completeTask(tasks, size, taskIndex - 1);
                break;
            }
            case 5:
            {
                saveTasks(tasks, size, filename);
                return 0;
            }
            default:
                printf("Invalid choice!!\n");
        }
    }
    return 0;
}


