#include "ft_nm_otool.h"




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
        if (tmp->type == FUNC_NAME)
        {
            ft_printf("%c %s\n", tmp->seqnum, tmp->ptr_data);
        }
        tmp = tmp->next;
    }
}