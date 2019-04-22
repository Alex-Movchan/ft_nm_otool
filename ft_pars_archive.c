#include "ft_nm_otool.h"
#include <ar.h>

int     get_archv_arch64(t_object *ptr_obj, void *ptr)
{
    void    *tmp;

    if (!ptr_obj || !ptr)
        return (EXIT_FAILURE);
    tmp = ptr_obj->event.data_buff;
    ptr_obj->event.data_buff = ptr;
    ptr_obj->event.methods.sort_cmp = ft_cmp_arch64;
    if (ft_parser_arch64(ptr_obj) == EXIT_FAILURE)
    {
        ptr_obj->event.data_buff = tmp;
        return (EXIT_FAILURE);
    }
    ft_print_arch64(ptr_obj);
    ptr_obj->event.data_buff = tmp;
    ft_free_datalist(&(ptr_obj->event.data));
    return (EXIT_SUCCESS);
}

int     get_archv_arch32(t_object *ptr_obj, void *ptr)
{
    void    *tmp;

    if (!ptr_obj || !ptr)
        return (EXIT_FAILURE);
    tmp = ptr_obj->event.data_buff;
    ptr_obj->event.data_buff = ptr;
    ptr_obj->event.methods.sort_cmp = ft_cmp_arch32;
    if (ft_parser_arch32(ptr_obj) == EXIT_FAILURE)
    {
        ptr_obj->event.data_buff = tmp;
        return (EXIT_FAILURE);
    }
    ft_print_arch32(ptr_obj);
    ptr_obj->event.data_buff = tmp;
    ft_free_datalist(&(ptr_obj->event.data));
    return (EXIT_SUCCESS);
}

void ft_print_archv(t_object *ptr_obj)
{
    if (!ptr_obj)
        return;
}

int     ft_name_offset(t_object *ptr_obj, struct ar_hdr *hdr)
        {
    int offset;
    char *name;

    if (!ptr_obj || !hdr)
        return (0);
    offset = 0;
    if (!ft_strncmp(hdr->ar_name, "#1/", 3))
    {
        offset = ft_atoi(hdr->ar_name + 3);
        if (offset > 0)
         name = (void*)hdr + sizeof(*hdr);
    } else
        name = hdr->ar_name;
    if (ft_strcmp(SYMDEF_SORTED, name))
    {

       ft_printf("\n%s(%s):\n", ptr_obj->event.file_name, name);
    }
    return (offset);
}

int     ft_pars_archv(t_object *ptr_obj)
{
    struct ar_hdr	*hdr;
    unsigned int    magic;
    int             size;
    int offset = 0;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    offset = SARMAG;
    hdr = ptr_obj->event.data_buff + offset;
    size = ft_atoi(hdr->ar_size);
    while (size)
    {
        offset = ft_name_offset(ptr_obj, hdr);
        magic = *(unsigned int*)((void*)hdr + sizeof(struct ar_hdr) + offset);
        if (MH_MAGIC == magic)
            get_archv_arch32(ptr_obj, (void*)hdr + sizeof(struct ar_hdr) + offset);
        else if (MH_MAGIC_64 == magic)
            get_archv_arch64(ptr_obj, (void*)hdr + sizeof(struct ar_hdr) + offset);
        hdr = (void*)hdr + size + sizeof(struct ar_hdr);
        size = ft_atoi(hdr->ar_size);
    }
    return (EXIT_SUCCESS);
}