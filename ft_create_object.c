#include "ft_nm_otool.h"

static int ft_init_nm_flag(t_object *ptr_obj, int ac, char **av)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((ptr_obj->flag = ft_check_flag(ac, av)) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}


static int ft_object_process(t_object *ptr_obj, int ac, char **av)
{
    int     i;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    i = 0;
    ptr_obj->event.event_constructor(ptr_obj);
    while (++i < ac)
    {
        if (av[i][0] == '-')
            continue ;
        ptr_obj->event.file_name = av[i];
        if (ptr_obj->event.ft_event_hendler((void*)ptr_obj) == EXIT_FAILURE)
        {
            if (ptr_obj->event.error_lvl > WORNING)
                return (EXIT_FAILURE);
            ptr_obj->event.error_lvl = SUCCESS;
        }
    }
    if (1 == i)
    {
        ptr_obj->event.file_name = "a.out";
        if (ptr_obj->event.ft_event_hendler((void*)ptr_obj) == EXIT_FAILURE)
            return (EXIT_FAILURE);

    }
    return (EXIT_SUCCESS);
}

static int ft_object_destructor(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if (ptr_obj->event.event_destructor(ptr_obj) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static int	ft_object_crash(t_object *ptr_obj, char *msg1, char *msg2)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.event_destructor(ptr_obj);
    return ft_error(msg1, msg2);
}


void        ft_object_cronstructor(t_object *ptr_obj)
{
    ptr_obj->object_destructor = ft_object_destructor;
    ptr_obj->object_crash_destructor = ft_object_crash;
    ptr_obj->init_flag = ft_init_nm_flag;
    ptr_obj->object_process = ft_object_process;
    ptr_obj->event.event_constructor = ft_event_init;
    ptr_obj->event.event_destructor = ft_event_destructor;
}

