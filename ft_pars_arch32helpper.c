/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_arch32helpper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 23:05:30 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 23:08:45 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static uint8_t	ft_get_section_type32(t_data *ptr_data, uint8_t n_sect)
{
	struct section	*tmp;

	if (n_sect == NO_SECT)
		return (' ');
	while (ptr_data)
	{
		if (ptr_data->type == SECTION)
		{
			tmp = (struct section*)ptr_data->ptr_data;
			if (n_sect == ptr_data->seqnum)
			{
				if (!ft_strcmp(tmp->sectname, SECT_DATA))
					return ('d');
				if (!ft_strcmp(tmp->sectname, SECT_BSS))
					return ('b');
				if (!ft_strcmp(tmp->sectname, SECT_TEXT))
					return ('t');
				else
					return ('s');
			}
		}
		ptr_data = ptr_data->next;
	}
	return ('s');
}

static uint8_t	ft_get_func_type(t_data *ptr_data, uint8_t type, uint8_t n_sect)
{
	uint8_t		ascii_type;
	uint8_t		tmp;

	tmp = (uint8_t)(type & N_TYPE);
	if (tmp == N_UNDF || tmp == N_PBUD)
		ascii_type = 'u';
	else if (tmp == N_ABS)
		ascii_type = 'a';
	else if (tmp == N_INDR)
		ascii_type = 'i';
	else if (tmp == N_SECT)
		ascii_type = ft_get_section_type32(ptr_data, n_sect);
	else
		return ('?');
	if (type & N_EXT)
		ascii_type = (uint8_t)ft_toupper(ascii_type);
	return (ascii_type);
}

static int		ft_add_print_data_ptr(t_object *ptr_obj,
					t_data *head, struct nlist *node, char *str_table)
{
	t_data			*ptr;

	if (!(ptr = ptr_obj->event.methods.new_data(ptr_obj,
					(void*)str_table + node->n_un.n_strx, FUNC_NAME)))
		return (EXIT_FAILURE);
	ptr->seqnum = ft_get_func_type(head, node->n_type, node->n_sect);
	if ((node->n_type & N_TYPE) != N_UNDF)
	{
		SET_BIT(ptr->data_flag, ARCH_64_SHOW_ADDR);
		ptr->addr = node->n_value;
	}
	return (EXIT_SUCCESS);
}

int				ft_get_print_data32(t_object *ptr_obj,
					struct symtab_command *tab)
{
	t_data			*tmp;
	struct nlist	*arrey;
	char			*str_table;
	int				i;

	if (!ptr_obj)
		return (EXIT_FAILURE);
	arrey = ptr_obj->event.data_buff + tab->symoff;
	str_table = ptr_obj->event.data_buff + tab->stroff;
	tmp = ptr_obj->event.data;
	ptr_obj->event.data = NULL;
	i = -1;
	while (++i < tab->nsyms)
	{
		if (ft_add_print_data_ptr(ptr_obj,
				tmp, &(arrey[i]), str_table) == EXIT_FAILURE)
		{
			ft_free_datalist(&tmp);
			return (EXIT_FAILURE);
		}
	}
	ft_free_datalist(&tmp);
	return (EXIT_SUCCESS);
}
