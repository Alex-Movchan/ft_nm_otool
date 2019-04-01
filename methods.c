#include "ft_nm_otool.h"

int    ft_destructor_mtd(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.print = NULL;
    ptr_obj->event.methods.parser = NULL;
    //to do: free ptr_obj->event.data;
    return (EXIT_SUCCESS);
}

t_arch      ft_get_arch(t_object *ptr_obj)
{
    unsigned int    magic;

    if (!ptr_obj)
        return (UNKNOW);
    magic = *(unsigned int *)ptr_obj->event.data_buff;
    if (magic == MH_MAGIC_64)
        return (ARCH64);
    if (magic == MH_MAGIC)
        return (ARCH32);
    if (magic == FAT_MAGIC || magic == FAT_CIGAM)
        return  (FAT);
    if (!ft_strncmp(ptr_obj->event.data_buff, ARMAG, SARMAG))
        return (ARMIVE);
    return (UNKNOW);
}

int    ft_constructor_mtd(t_object *ptr_obj)
{
    t_arch  arch;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.destructor_mtd = ft_destructor_mtd;
    ptr_obj->event.methods.get_event_arch = ft_get_arch;
    if ((arch = ptr_obj->event.methods.get_event_arch(ptr_obj)) == UNKNOW)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: unknow architecture:", ptr_obj->event.file_name));
    if (arch == FAT)
        return (ptr_obj->event.cllback_fat(ptr_obj));
    if (arch == ARMIVE)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = NULL; //To do!
    }
    else if (ARCH64 == arch || ARCH32 == arch)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = (ARCH64 == arch) ? pars_arch64_mtd : pars_arch32_mtd;
    }
    //to do: malloc init data
    return (EXIT_SUCCESS);
}