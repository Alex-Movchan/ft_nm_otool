#include "ft_nm_otool.h"

t_data		*ft_create_new_data(void)
{
    t_data		*new_data;

    if ((new_data = (t_data*)malloc(sizeof(t_data))) == NULL)
        return (NULL);
    new_data->next = NULL;
    new_data->ptr_data = NULL;
    new_data->seqnum = 0;
    return (new_data);
}

t_data		*ft_add_data_to_list(t_data **head)
{
    t_data	*ptr;

    ptr = (*head);
    if (ptr)
    {
        while (ptr->next)
            ptr = ptr->next;
        if ((ptr->next = ft_create_new_data()) != NULL)
            return (ptr->next);
        else
            return (NULL);
    }
    else
    {
        if (((*head) = ft_create_new_data()) != NULL)
            return (*head);
        else
            return (NULL);
    }
}

t_data		*ft_add_data_to_list_rev(t_data **head)
{
    t_data	*ptr;

    if ((ptr = ft_create_new_data()) == NULL)
        return (NULL);
    ptr->next = (*head);
    if (*head)
        (*head) = ptr;
    return (ptr);
}

t_data		*ft_add_data_to_sorted_list(t_data **head, void *ptr_data, int(*cmp)(void*, void*))
{
    t_data  *tmp;
    t_data	*ptr;

    if ((ptr = ft_create_new_data()) == NULL)
        return (NULL);
    ptr->ptr_data = ptr_data;
    if (*head)
    {
        tmp = (*head);
        while (tmp->next && cmp(tmp->ptr_data, ptr->ptr_data))
            tmp = tmp->next;
        ptr->next = tmp->next;
        tmp->next = ptr;
    }
    return (ptr);
}

int ft_data_from_section(t_object *ptr_obj, void *ptr_data)
{
    t_data  *ptr;

    if (!ptr_obj || !ptr_data)
        return (EXIT_FAILURE);
    if (CHECK_BIT(ptr_obj->flag, FLAG_R))
        ptr = ft_add_data_to_list_rev(&(ptr_obj->event.data));
    else if (CHECK_BIT(ptr_obj->flag, FLAG_P))
        ptr = ft_add_data_to_list(&(ptr_obj->event.data));
    else
    {
        ptr = ft_add_data_to_sorted_list(&(ptr_obj->event.data),
             ptr_data, ptr_obj->event.methods.sort_cmp);
    }
    if (!ptr)
        return (ptr_obj->event.event_crash(ptr_obj,
                "Error: create new data_list", NULL, ERROR_EVENT));
    ptr->ptr_data = ptr_data;
    ptr->seqnum = -1;
    return (EXIT_SUCCESS);
}