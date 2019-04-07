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

t_data		*ft_get_new_data_in_list(t_data **head)
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