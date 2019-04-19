#include "ft_nm_otool.h"

void ft_print_section(void *data)
{
    struct section_64   *ptr;

    if (!data)
        return ;
    ptr = (struct section_64*)data;
    if (ptr)
        return;
}

void    ft_print_arch64(t_object *ptr_obj)
{
    t_data  *tmp;

    if (!ptr_obj)
        return ;
    tmp = ptr_obj->event.data;
    if (!tmp)
        return ;
    while (tmp)
    {
        if (tmp->seqnum == SECTION)
            ft_print_section(tmp->ptr_data);
        tmp = tmp->next;
    }
}