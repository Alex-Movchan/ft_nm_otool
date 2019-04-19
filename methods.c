#include "ft_nm_otool.h"


static t_arch      ft_get_methods_from_arch(t_object *ptr_obj)
{
    unsigned int    magic;

    if (!ptr_obj)
        return (UNKNOWN);
    magic = *(unsigned int *)ptr_obj->event.data_buff;
    if (magic == FAT_MAGIC || magic == FAT_CIGAM)
        return (FAT);
    if (magic == MH_MAGIC_64)
        return (ARCH64);
    if (magic == MH_MAGIC)
        return (ARCH32);
    if (!ft_strncmp(ptr_obj->event.data_buff, ARMAG, SARMAG))
        return (ARMIVE);
    return (UNKNOWN);
}

int    ft_constructor_mtd(t_object *ptr_obj)
{
    t_arch  arch;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.offset = 0;
    ptr_obj->event.methods.get_event_arch = ft_get_methods_from_arch;
    ptr_obj->event.methods.new_data = ft_add_datalist;
    if ((arch = ptr_obj->event.methods.get_event_arch(ptr_obj)) == UNKNOWN)
        return (EXIT_FAILURE);
    if (arch == FAT)
        arch = ptr_obj->event.cllback_fat(ptr_obj);
    if (arch == ARMIVE)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = ft_pars_archv;
        ptr_obj->event.methods.sort_cmp = NULL; // to do
    }
    else if (ARCH64 == arch || ARCH32 == arch)
    {
        ptr_obj->event.methods.print = (ARCH64 == arch) ? ft_print_arch64 : NULL; //To do!
        ptr_obj->event.methods.parser = (ARCH64 == arch) ? ft_parser_arch64 : pars_arch32_mtd;
        ptr_obj->event.methods.sort_cmp = (ARCH64 == arch) ? ft_cmp_arch64 : ft_cmp_arch32;
    }
    return (EXIT_SUCCESS);
}

int    ft_destructor_mtd(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.print = NULL;
    ptr_obj->event.methods.parser = NULL;
    ptr_obj->event.methods.sort_cmp = NULL;
    return (EXIT_SUCCESS);
}