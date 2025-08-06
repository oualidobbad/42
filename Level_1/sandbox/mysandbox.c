#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>


int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int pid;
    int status;

    pid = fork ();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        alarm(timeout);
        f();
        exit (0);
    }
    waitpid(pid, &status, 0);
    if (WEXITSTATUS(status) == 0) {
        if (verbose)
            printf("Nice function!\n");
        return (1);
    } else {
        if (verbose)
            printf("Bad function: exit status %d\n", WEXITSTATUS(status));
        return (0);
    }
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGALRM) {
            if (verbose)
                printf("Bad function: timeout%d", timeout);
        }
        else {
            if (verbose)
                printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
        }
        return (0);
    }
    return (0);
}       
int main()
{

}