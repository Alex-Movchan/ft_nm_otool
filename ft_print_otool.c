#include "ft_nm_otool.h"

static void    ft_printnchr(char src, int count)
{
    int i;

    i = -1;
    while (++i < count)
        ft_putchar(src);
}


int ft_long_count(unsigned long long int nbr)
{
    int count;

    count = 0;
    while (nbr > 0)
    {
        count += 1;
        nbr /= 0x10;
    }
    return (count);
}

int		print_section_64(t_object *ptr_obg, t_data *ptr_data)
{
    struct section_64 *section;
    uint64_t	i;
    void		*val;

    if (!ptr_obg || ! ptr_data)
        return (EXIT_FAILURE);
    i = 0;
    section = (struct section_64 *)ptr_data->ptr_data;
    while (i < section->size)
    {
        val = ptr_obg->event.data_buff + section->offset + i;
        ft_printnchr('0', ARCH_64 - ft_long_count(section->addr + i));
        if (section->addr + i > 0)
            ft_puthexaddr(section->addr + i);
        ft_putchar('\t');
        ft_print_hex(val, section->size - i);
        i += 16;
    }
    return (EXIT_SUCCESS);
}

int		print_section_32(t_object *ptr_obg, t_data *ptr_data)
{
    struct section *section;
    uint64_t	i;
    void		*val;

    if (!ptr_obg || ! ptr_data)
        return (EXIT_FAILURE);
    i = 0;
    section = (struct section *)ptr_data->ptr_data;
    while (i < section->size)
    {
        val = ptr_obg->event.data_buff + section->offset + i;
        ft_printnchr('0', ARCH_32 - ft_long_count(section->addr + i));
        if (section->addr + i > 0)
            ft_puthexaddr(section->addr + i);
        ft_putchar('\t');
        ft_print_hex(val, section->size - i);
        i += 16;
    }
    return (EXIT_SUCCESS);
}

void    ft_print_arch64_hex(t_object *ptr_obj)
{
    t_data *tmp;

    if (!ptr_obj)
        return ;
    tmp = ptr_obj->event.data;
    if (!tmp)
        return ;
    ft_printf("Contents of (__TEXT,__text) section\n");
    while (tmp)
    {
        print_section_64(ptr_obj, tmp);
        tmp= tmp->next;

    }
}

void    ft_print_arch32_hex(t_object *ptr_obj)
{
    t_data *tmp;

    if (!ptr_obj)
        return ;
    tmp = ptr_obj->event.data;
    if (!tmp)
        return ;
    ft_printf("%Contents of (__TEXT,__text) section\n");
    while (tmp)
    {
        print_section_32(ptr_obj, tmp);
        tmp= tmp->next;

    }
}