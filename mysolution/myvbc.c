#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int parse_expr(char **s);
int parse_term(char **s);
int parse_factor(char **s);

int parse_expr(char **s)
{
    int a = parse_term(s);
    if (a == -1)
        return -1;
    while (**s == '+')
    {
        (*s)++;
        int b = parse_term(s);
        if (b == -1)
            return -1;
        a = a + b;
    }
    return a;
}

int parse_term(char **s)
{
    int a = parse_factor(s);
    if (a == -1)
        return -1;
    while (**s == '*')
    {
        (*s)++;
        int b = parse_factor(s);
        if (b == -1)
            return -1;
        a = a * b;
    }
    return a;
}

int parse_factor(char **s)
{
    if (**s && isdigit(**s))
        return *(*s)++ - '0';
    else if (**s == '(')
    {
        (*s)++;
        int a = parse_expr(s);
        if (a == -1)
            return -1;
        if (**s == ')')
            return ((*s)++, a);
    }
    if (!**s)
        return (printf("Unexpected end of file\n"), -1);
    return (printf("Unexpected token '%c'\n", **s), -1);
}

int main (int ac, char **av)
{
    if (ac != 2)
       return 1; 
    int res = parse_expr(++av);
    if (res == -1)
        return 1;
    if (**av)
        return (printf("Unexpected token '%c'\n", **av), 1);
    printf("%d\n", res);
}
