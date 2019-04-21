#include "ft_nm_otool.h"

static t_data   *ft_create_new_data(void)
{
    t_data		*new_data;

    if ((new_data = (t_data*)malloc(sizeof(t_data))) == NULL)
        return (NULL);
    new_data->next = NULL;
    new_data->ptr_data = NULL;
    new_data->seqnum = 0;
    new_data->type = 0;
    return (new_data);
}

static t_data	*ft_add_data_to_list(t_data **head)
{
    t_data	*ptr;
    int     count;

    ptr = (*head);
    if (ptr)
    {
        while (ptr->next)
        {
            ptr = ptr->next;
        }
        if (!(ptr->next = ft_create_new_data()))
            return (NULL);
        ptr->next->seqnum = ptr->seqnum + 1;
        ptr = ptr->next;
    }
    else
    {
        if (!(ptr = ft_create_new_data()))
            return (NULL);
        (*head) = ptr;
        ptr->seqnum = 1;
    }
    return (ptr);
}

t_data	*ft_add_data_to_sorted_list(t_data **head, void *ptr_data, int(*cmp)(void*, void*))
{
    t_data  *tmp;
    t_data  *prev;
    t_data	*ptr;

    if ((ptr = ft_create_new_data()) == NULL)
        return (NULL);
    prev = NULL;
    ptr->ptr_data = ptr_data;
    if (*head)
    {
        tmp = (*head);
        while (tmp->next && cmp(ptr->ptr_data, tmp->ptr_data) >= 0)
        {
            prev = tmp;
            tmp = tmp->next;
        }
        if (!tmp->next && cmp(ptr->ptr_data, tmp->ptr_data) > 0)
            tmp->next = ptr;
        else
        {
            if (prev)
                prev->next = ptr;
            else
                (*head) = ptr;
            ptr->next = tmp;
        }
    }
    else
        (*head) = ptr;
    return (ptr);
}

t_data             *ft_add_datalist(t_object *ptr_obj, void *ptr_data, int type)
{
    t_data  *ptr;

    if (!ptr_obj || !ptr_data)
        return (NULL);
    if (CHECK_BIT(ptr_obj->flag, FLAG_SECTIONS))
        ptr = ft_add_data_to_list(&(ptr_obj->event.data));
    else
        ptr = ft_add_data_to_sorted_list(&(ptr_obj->event.data), ptr_data, ptr_obj->event.methods.sort_cmp);
    if (!ptr)
        return (NULL);
    ptr->ptr_data = ptr_data;
    ptr->type = type;
    ptr->data_flag = 0;
    ptr->addr = 0;
    return (ptr);
}