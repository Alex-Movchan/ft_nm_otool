#include "ft_nm_otool.h"

static int ft_get_flag(int flag, char *str)
{
    if (!strcmp(str, "-j"))
        return (SET_BIT(flag, FLAG_J));
    if (!strcmp(str, "-u"))
        return (SET_BIT(flag, FLAG_U));
    if (!strcmp(str, "-U"))
        return (SET_BIT(flag, FLAG_UP_U));
    if (!strcmp(str, "-r") && !CHECK_BIT(flag, FLAG_P))
        return (SET_BIT(flag, FLAG_R));
    if (!strcmp(str, "-p"))
    {
        RESET_BIT(flag, FLAG_R);
        return (SET_BIT(flag, FLAG_P));
    }
    return (ft_error("Error: unknow flag:", str));
}

int     ft_check_flag(int ac, char **av)
{
    int     i;
    int     flag;

    i = 0;
    flag = 0;
    while (++i < ac)
    {
        if (av[i][0] == '-')
        {
            if ((flag = ft_get_flag(flag, av[i])) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
    }
    return flag;
}