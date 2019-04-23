/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 01:06:19 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 01:09:54 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static uint8_t	ft_get_section_type64(t_data *ptr_data, uint8_t n_sect)
{
	struct section_64	*tmp;

	if (n_sect == NO_SECT)
		return (' ');
	while (ptr_data)
	{
		if (ptr_data->type == SECTION)
		{
			tmp = (struct section_64*)ptr_data->ptr_data;
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

uint8_t			ft_get_func_type64(t_data *ptr_data,
					uint8_t type, uint8_t n_sect)
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
		ascii_type = ft_get_section_type64(ptr_data, n_sect);
	else
		return ('?');
	if (type & N_EXT)
		ascii_type = (uint8_t)ft_toupper(ascii_type);
	return (ascii_type);
}
