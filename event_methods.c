/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 00:13:54 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 00:15:37 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		ft_event_destructor(t_object *ptr_obj)
{
	if (!ptr_obj)
		return (EXIT_FAILURE);
	if (ptr_obj->event.methods.destructor_mtd(ptr_obj) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ptr_obj->event.data_buff = NULL;
	ptr_obj->event.file_name = NULL;
	ft_memset(&ptr_obj->event.spcf, 0, sizeof(struct stat));
	return (EXIT_SUCCESS);
}

int		ft_destructor_mtd(t_object *ptr_obj)
{
	if (!ptr_obj)
		return (EXIT_FAILURE);
	ptr_obj->event.methods.print = NULL;
	ptr_obj->event.methods.parser = NULL;
	ptr_obj->event.methods.sort_cmp = NULL;
	return (EXIT_SUCCESS);
}
