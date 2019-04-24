/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 01:10:11 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/25 00:14:46 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static t_data	*ft_create_new_data(void)
{
	t_data	*new_data;

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

	ptr = (*head);
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
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

static void		ft_search_in_list(t_data **head,
			t_data *ptr_data, int (*cmp)(void*, void*))
{
	t_data	*tmp;
	t_data	*prev;

	prev = NULL;
	tmp = (*head);
	while (tmp->next && cmp(ptr_data->ptr_data, tmp->ptr_data) >= 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp->next && cmp(ptr_data->ptr_data, tmp->ptr_data) > 0)
		tmp->next = ptr_data;
	else
	{
		if (prev)
			prev->next = ptr_data;
		else
			(*head) = ptr_data;
		ptr_data->next = tmp;
	}
}

static t_data	*ft_add_data_to_sorted_list(t_data **head,
			void *ptr_data, int (*cmp) (void *, void *))
{
	t_data	*ptr;

	if ((ptr = ft_create_new_data()) == NULL)
		return (NULL);
	ptr->ptr_data = ptr_data;
	if (*head)
		ft_search_in_list(head, ptr, cmp);
	else
		(*head) = ptr;
	return (ptr);
}

t_data			*ft_add_datalist(t_object *ptr_obj, void *ptr_data, int type)
{
	t_data	*ptr;

	if (!ptr_obj || !ptr_data)
		return (NULL);
	if (CHECK_BIT(ptr_obj->flag, FLAG_SECTIONS))
		ptr = ft_add_data_to_list(&(ptr_obj->event.data));
	else
	{
		ptr = ft_add_data_to_sorted_list(&(ptr_obj->event.data),
				ptr_data, ptr_obj->event.methods.sort_cmp);
	}
	if (!ptr)
		return (NULL);
	ptr->ptr_data = ptr_data;
	ptr->type = type;
	ptr->data_flag = 0;
	ptr->addr = 0;
	return (ptr);
}
