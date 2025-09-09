/**
 * Assignment 2
 * Name - Sachit Singh Chawla
 * ID- B00865842
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_LINE 80
#define MAX_HISTORY 10

typedef struct {
    char command[MAX_LINE];
    pid_t pid;
} history_entry;

history_entry history[MAX_HISTORY];
int historyCount = 0;

void addHistory(char inputCommand[MAX_LINE], pid_t pid) {
    if (historyCount != MAX_HISTORY) {
        historyCount++;
        //shift everything down
        for (int i = historyCount - 1; i > 0; i--) {
            strcpy(history[i].command, history[i-1].command);
            history[i].pid = history[i-1].pid;
        }
    }
    else if(historyCount == MAX_HISTORY) {
        //shift everything down and delete if have to
        for (int i = MAX_HISTORY - 1; i > 0; i--) {
            strcpy(history[i].command, history[i-1].command);
            history[i].pid = history[i-1].pid;
        }
    }
    //add it to the top of the array
    if(strcmp(history[0].command,inputCommand)!=0){
        strcpy(history[0].command, inputCommand);
        history[0].pid = pid;
    }
}
void displayHistory() {
    if (historyCount == 0) {
        printf("No command in history!\n");
        return;
    }
    printf("ID  PID    Command\n");
    for (int i = 0; i < historyCount; i++) {
        printf("%d   %d    %s\n", i+1, history[i].pid, history[i].command);
    }
}
void executeCommand(char *input);

void executeRecent() {
    if (historyCount == 0) {
        printf("No command in history!\n");
        return;
    }
    printf("Executing: %s\n", history[0].command);
    executeCommand(history[0].command);
}

void executeNthCommand(int N) {
    if (historyCount == 0) {
        printf("No command in history!\n");
        return;
    }
    if (N < 1 || N > historyCount) {
        printf("Such a command is NOT in history!\n");
        return;
    }
    printf("Executing: %s\n", history[N - 1].command);
    executeCommand(history[N - 1].command);
}
void executeCommand(char *input) {
    char *args[MAX_LINE / 2 + 1];
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Tokenize the input
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // In the child process
        if (execvp(args[0], args) == -1) {
            printf("Invalid Command!");
            exit(1);
        }
    } else {
        // In the parent process
        wait(NULL);
        addHistory(input, pid);  // Add the executed command to the history
    }
}

int main(void) {
    char input[MAX_LINE];
    int should_run = 1;

    while (should_run) {
        printf("CSCI3120> ");
        fflush(stdout);
        fgets(input, MAX_LINE, stdin);

        //handleing the next line character
        input[strcspn(input, "\n")] = 0;

        // Handle the 'exit' command
        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            continue;
        }
        else if (strcmp(input, "history") == 0) {
            displayHistory();
            continue;
        }
        else if (strcmp(input, "!!") == 0) {
            executeRecent();
            continue;
        }
            // Handle '!N' command (execute Nth command from history)
        else if (input[0] == '!' && isdigit(input[1])) {
            int N = atoi(&input[1]);
            executeNthCommand(N);
            continue;
        }
        executeCommand(input);

    }
    return 0;

}