#include "ft_nm_otool.h"

static void ft_create_method_for_archv(t_object *ptr_obj)
{
    if (PROGRAM_STATE == NM_PROGRAM)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = ft_pars_archv;
        ptr_obj->event.methods.sort_cmp = NULL; // to do
    }
    else if (PROGRAM_STATE == OTOOL_PROGRAM)
    {
        ptr_obj->event.methods.print = NULL; // to do
        ptr_obj->event.methods.parser = NULL; //to do
        ptr_obj->event.methods.sort_cmp = NULL; // to do
    }
}

static void ft_create_method_for_arch32(t_object *ptr_obj)
{
    if (PROGRAM_STATE == NM_PROGRAM)
    {
        ptr_obj->event.methods.print = ft_print_arch32;
        ptr_obj->event.methods.parser = ft_parser_arch32;
        ptr_obj->event.methods.sort_cmp = ft_cmp_arch32;
    }
    else if (PROGRAM_STATE == OTOOL_PROGRAM)
    {
        ptr_obj->event.methods.print = NULL; // to do
        ptr_obj->event.methods.parser = NULL; //to do
        ptr_obj->event.methods.sort_cmp = NULL; // to do
    }
}
static void ft_create_method_for_arch64(t_object *ptr_obj)
{
    if (PROGRAM_STATE == NM_PROGRAM)
    {
        ptr_obj->event.methods.print = ft_print_arch64;
        ptr_obj->event.methods.parser = ft_parser_arch64;
        ptr_obj->event.methods.sort_cmp = ft_cmp_arch64;
    }
    else if (PROGRAM_STATE == OTOOL_PROGRAM)
    {
        ptr_obj->event.methods.print = ft_print_otool_arch64;
        ptr_obj->event.methods.parser = ft_parser_arch64;
        ptr_obj->event.methods.sort_cmp = NULL;
    }

}


int    ft_constructor_mtd(t_object *ptr_obj)
{
    unsigned int    magic;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.offset = 0;
    ptr_obj->event.methods.new_data = ft_add_datalist;
    magic = *(unsigned int *)ptr_obj->event.data_buff;
    if (magic == FAT_MAGIC || magic == FAT_CIGAM)
    {
        if (ptr_obj->event.cllback_fat(ptr_obj) == EXIT_FAILURE)
            return (ptr_obj->event.event_crash(ptr_obj, "Error parsing fat", NULL, ERROR_EVENT));
        magic = *(unsigned int *)ptr_obj->event.data_buff;
    }
    if (magic == MH_MAGIC_64)
        ft_create_method_for_arch64(ptr_obj);
    else if (magic == MH_MAGIC)
        ft_create_method_for_arch32(ptr_obj);
    else if (!ft_strncmp(ptr_obj->event.data_buff, ARMAG, SARMAG))
        ft_create_method_for_archv(ptr_obj);
    else
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}