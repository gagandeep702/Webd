#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    char name[20];
    int deadline;
    int priority;
    int start_time;
    int end_time;
} Task;

void run_task(Task *task) {
    printf("Running %s\n", task->name);
    task->start_time = time(NULL);
    sleep(1);
    task->end_time = time(NULL);
}

void edf_scheduler(Task tasks[], int num_tasks) {
    int current_time = 0;
    int i;

    while (true) {
        int earliest_deadline = INT_MAX;
        int earliest_deadline_task_index = -1;

        for (i = 0; i < num_tasks; i++) {
            if (tasks[i].deadline < earliest_deadline && tasks[i].deadline > current_time) {
                earliest_deadline = tasks[i].deadline;
                earliest_deadline_task_index = i;
            }
        }

        if (earliest_deadline_task_index == -1) {
            break;
        }

        run_task(&tasks[earliest_deadline_task_index]);

        current_time++;
    }
}

void print_gantt_chart(Task tasks[], int num_tasks) {
    printf("\nGantt Chart:\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num_tasks; i++) {
        printf("| %-10s ", tasks[i].name);
    }
    printf("|\n");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num_tasks; i++) {
        int task_duration = tasks[i].end_time - tasks[i].start_time;
        printf("| %-10d ", task_duration);
    }
    printf("|\n");

    printf("------------------------------------------------------------\n");
}

void print_task_table(Task tasks[], int num_tasks) {
    printf("\nTask Information:\n");
    printf("------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s |\n", "Task", "Deadline", "Priority");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num_tasks; i++) {
        printf("| %-10s | %-10d | %-10d |\n", tasks[i].name, tasks[i].deadline, tasks[i].priority);
    }
    printf("------------------------------------------------------------\n");
}

int main() {
    int num_tasks, i;

    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Task *tasks = (Task*)malloc(num_tasks * sizeof(Task));

    for (i = 0; i < num_tasks; i++) {
        printf("Enter task name: ");
        scanf("%s", tasks[i].name);

        printf("Enter task deadline: ");
        scanf("%d", &tasks[i].deadline);

        printf("Enter task priority: ");
        scanf("%d", &tasks[i].priority);
    }

    edf_scheduler(tasks, num_tasks);

    print_gantt_chart(tasks, num_tasks);
    print_task_table(tasks, num_tasks);

    free(tasks);

    return 0;
}
