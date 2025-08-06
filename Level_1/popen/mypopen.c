
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pipe(fd);
    
    if (fork() == 0)
    {
        if (type== 'r')
            dup2(fd[1], 1);
        else
            dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(file, argv);
    }
    if (type == 'r')
        return (close (fd[1]), fd[0]);
    return (close (fd[0]), fd[1]);
}
#define BUFFER_SIZE 42
char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int read_byt;
    static int position;
    int i = 0;
    char *line = malloc(1000);

    if (fd < 0 || BUFFER_SIZE <= 0 || !line)
        return NULL;
    while (1)
    {
        if (position >= read_byt)
        {
            read_byt = read(fd, buffer, BUFFER_SIZE);
            position = 0;
            if (read_byt <= 0)
                break;
        }
        if ((line[i++] = buffer[position++]) == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
    {
        free (line);
        return NULL;
    }
    return line;
}

int main() {
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'w');

	char *line;
	while(line = get_next_line(0))
        write(fd, line, strlen(line));
	//    printf("%s",line);
}
