#include "ft_nm_otool.h"

int         ft_init_nm_flag(t_object *ptr_obj, int ac, char **av)
{
    if ((ptr_obj->flag = ft_check_flag(ac, av)) == EXIT_FAILURE)
        return (EXIT_FAILURE);
}


int         ft_object_process(t_object *ptr_obj, int ac, char **av)
{
    int     i;

    ptr_obj->event = ft_event_init();
    i = 0;
    while (++i < ac)
    {
        if (av[i][0] == '-')
            continue ;
        ptr_obj->event.file_name = av[i];
        if (ptr_obj->event.ft_event_hendler((void*)ptr_obj) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void        ft_object_create(t_object *ptr_obj, int ac, char **av)
{
    ptr_obj->crash = ft_error;
    ptr_obj->init_flag = ft_init_nm_flag;
    ptr_obj->object_process = ft_object_process;
    ptr_obj->cllback_fat = NULL; // To go!!
    ptr_obj->event = ft_event_init();
}

