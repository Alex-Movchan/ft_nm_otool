#include "ft_nm_otool.h"

int    ft_error(char *msg, char *param)
{
    if (msg && param)
    {
        ft_putstr_fd(msg, STDERR_FILENO);
        ft_putchar_fd(' ', STDERR_FILENO);
        ft_putendl_fd(param, STDERR_FILENO);
    }
    else if (msg)
        ft_putendl_fd(msg, STDERR_FILENO);
    return(EXIT_FAILURE);
}