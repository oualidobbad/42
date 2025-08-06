#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int parse_expr(char **s);
int parse_term(char **s);
int parse_factor(char **s);

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int parse_expr(char **s)
{
    int term1 = parse_term(s);
    if (term1 == -1)
        return -1;
    while (accept(s, '+'))
    {
        int term2 = parse_term(s);
        if (term2 == -1)
            return -1;
        term1 = term1 + term2;
    }
    return term1;
}
int parse_term(char **s)
{
    int fac1 = parse_factor(s);
    if (fac1 == -1)
        return -1;
    while (accept(s, '*'))
    {
        int fac2 = parse_factor(s);
        if (fac2 == -1)
            return -1;
        fac1 = fac1 * fac2;
    }
    return fac1;
}

int parse_factor(char **s)
{
    if (**s && isdigit(**s))
        return *(*s)++ - '0';
    else if (**s && **s == '(')
    {
        ++(*s);
        int sum = parse_expr(s);
        if (sum == -1)
            return -1;
        if (**s == ')')
            return (++(*s), sum);
    }
    unexpected(**s);
    return -1;
}

int main (int ac, char *av[])
{
    if (ac != 2)
        return 1;
    int result = parse_expr(++av);
    if (result == -1)
        return 1;
    if (**av)
        return (printf("Unexpected token '%c'\n", **av), 1);
    printf ("%d\n", result);
    return 0;
}