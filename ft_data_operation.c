#include "ft_nm_otool.h"

int     ft_cmp_arch64(void *ptr1, void *ptr2)
{
    struct section_64	*section1;
    struct section_64	*section2;

    section1 = (struct section_64 *)ptr1;
    section2 = (struct section_64 *)ptr2;
    return (ft_strcmp(section1->sectname, section2->sectname));
}

int     ft_cmp_arch32(void *ptr1, void *ptr2)
{
    struct section	*section1;
    struct section	*section2;

    section1 = (struct section *)ptr1;
    section2 = (struct section *)ptr2;
    return (ft_strcmp(section1->sectname, section2->sectname));
}

int     ft_datatype_count(t_data *data, int type)
{
    int count;

    count = 0;
    while (data)
    {
        if (data->type == type)
            count += 1;
        data = data->next;
    }
    return (count);
}

void    ft_free_datalist(t_data **head)
{
    t_data  *ptr;
    t_data  *tmp;

    ptr = (*head);
    while (ptr)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    (*head) = NULL;
}