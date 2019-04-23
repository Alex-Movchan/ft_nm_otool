#include "ft_nm_otool.h"

void    ft_print_arch32(t_object *ptr_obj)
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
            if (CHECK_BIT(tmp->data_flag, ARCH_64_SHOW_ADDR))
                ft_printf("%08lx %c %s\n", tmp->addr, tmp->seqnum, tmp->ptr_data);
            else
                ft_printf("% 10c %s\n", tmp->seqnum, tmp->ptr_data);
        }
        tmp = tmp->next;
    }
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
        if (tmp->type == FUNC_NAME)
        {
            if (CHECK_BIT(tmp->data_flag, ARCH_64_SHOW_ADDR))
                ft_printf("%016lx %c %s\n", tmp->addr, tmp->seqnum, tmp->ptr_data);
            else
                ft_printf("% 18c %s\n", tmp->seqnum, tmp->ptr_data);
        }
        tmp = tmp->next;
    }
}

