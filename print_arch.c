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

void	ft_puthexaddr(unsigned char hex)
{
    if (0 == hex / HEX)
        ft_putchar(HEX_BASE[hex % HEX]);
    else
    {
        ft_puthexaddr(hex / (unsigned char) HEX);
        ft_putchar(HEX_BASE[hex % HEX]);
    }
}

static int	ft_print_hex(unsigned char *str, size_t size)
{
    int		i;

    i = -1;
    while (++i < HEX && i < (int)size)
    {
        ft_puthexaddr(str[i]);
        ft_putchar(' ');
    }
    ft_putstr("\r\n");
    return (i);
}

void    ft_print_otool_arch64(t_object *ptr_obj)
{
    t_data  *tmp;
    int     i;
    struct section_64 *ptr_section;

    if (!ptr_obj)
        return ;
    tmp = ptr_obj->event.data;
    if (!tmp)
        return ;
    ft_printf("(__TEXT,__text) section\n");
    while (tmp)
    {
        i = 0;
        ptr_section = (struct section_64*)tmp;
        ft_printf("%016lx", ptr_section->addr);
        while ( i < ptr_section->size)
           i += ft_print_hex(ptr_obj->event.data_buff + ptr_section->offset, ptr_section->size);
        tmp = tmp->next;
    }
}