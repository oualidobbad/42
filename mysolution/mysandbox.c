#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int pid = fork();
    if (pid == 0)
    {
        alarm(timeout);
        f();
        exit(0);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 0)
        {
            if (verbose)
                printf("Nice function!\n");
            return 1;
        }
        else
            printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
        return 0;
    }
    if (WTERMSIG(status) == SIGALRM)
    {
        if (verbose)
            printf("Bad function: timed out after %u seconds\n", timeout);
    }
    else
    {
        if (verbose)
            printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
    }
    return 0;
}