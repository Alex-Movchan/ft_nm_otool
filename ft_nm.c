#include "ft_nm_otool.h"

int         main(int ac, char **av)
{
    t_object    object;

    if (ac < 2)
        ft_error("Error: count argumens.", NULL);
    ft_object_create(&object, ac, av);
    object.init_flag(&object, ac, av);
    if (object.object_process(&object, ac, av) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}