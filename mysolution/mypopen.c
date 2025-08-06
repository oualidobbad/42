#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        if (type == 'r')
            dup2(fd[1], 1);
        else
            dup2(fd[0], 0);
        close (fd[0]);
        close (fd[1]);
        execvp(file, argv);
        exit(127);
    }
    if (type == 'r')
        return (close(fd[1]), fd[0]);
    else
        return (close(fd[0]), fd[1]);
}

int main()
{
    int fd = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    write(fd, "hello World\n", 12);
}