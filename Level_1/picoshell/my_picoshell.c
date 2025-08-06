/*
Allowed functions:
pipe, fork, dup2, execvp, close, exit, wait

Write the following function:

	int picoshell(char **cmds[])

It has to simulate the pipe. cmds[i] contains the command with its arguments.
Use execvp(cmds[i][0], cmds) to execute a command.
It has to return 1, if a command fail. Do not leak file descriptors.
In the exam, a main file will be given to test your picoshell
*/



int picoshell(char **cmds[])
{
    int fd[2];
    fd[0] = -1;
    fd[1] = -1;
    int fd_save = -1;
    int pid;
    int status;
    
    for (int i = 0; cmds[i]; i++)
    {
        if (cmds[i + 1])
        {
            fd_save = fd[0];
            pipe(fd);
        }
        pid = fork();
        if (pid == 0)
        {
            if (cmds[i + 1] && i == 0)
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }   
            else if (!cmds[i + 1] && i)
            {
                dup2(fd[0], 0);
                close(fd[0]);
            }
            else if (cmds[i + 1])
            {
                dup2(fd_save, 0);
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd_save);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit (127);
        }
        if (fd[1] != -1)
        {
            close(fd[1]);
            fd[1] = -1;
        }
        if (fd_save != -1)
        {
            close(fd_save);
            fd_save = -1;
        }
    }
    close (fd[0]);
    while (wait(NULL) != -1)
    {
    }
    return (0);
}


