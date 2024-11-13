#include "pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGC 3

int main(int argc, char** argv) {
    size_t i, n;
    int prev_pipe, pfds[2];

    n = argc - 1;
    printf("num args = %lu\n", n);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) {
        // create pipes
        pipe(pfds);

        if (!fork()) {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            // execvp(commands[i][0], commands[i]);
            execlp(argv[i + 1], argv[i + 1], NULL);

            perror("execvp failed");
            exit(1);
        }
        // parent

        // Close read end of previous pipe (not needed in the parent)
        close(prev_pipe);

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    // Start last command
    // execvp(commands[i][0], commands[i]);
    execlp(argv[i + 1], argv[i + 1], NULL);

    perror("execvp failed");

    return 0;
}
