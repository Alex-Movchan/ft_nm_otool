/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 23:59:34 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/25 00:04:27 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	ft_print_arch32(t_object *ptr_obj)
{
	t_data	*tmp;

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
				ft_printf("%08lx %c %s\n", tmp->addr,
						tmp->seqnum, tmp->ptr_data);
			else
				ft_printf("% 10c %s\n", tmp->seqnum, tmp->ptr_data);
		}
		tmp = tmp->next;
	}
}

void	ft_print_arch64(t_object *ptr_obj)
{
	t_data	*tmp;

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
				ft_printf("%016lx %c %s\n",
						tmp->addr, tmp->seqnum, tmp->ptr_data);
			else
				ft_printf("% 18c %s\n", tmp->seqnum, tmp->ptr_data);
		}
		tmp = tmp->next;
	}
}
