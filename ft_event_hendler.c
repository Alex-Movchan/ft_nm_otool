/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_hendler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 00:37:59 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 01:05:25 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static int	ft_check_errorlvl(t_object *ptr_obj,
			char *msg1, char *msg2, t_crash_lvl lvl)
{
	if (ptr_obj->event.error_lvl == SUCCESS)
		return (ptr_obj->event.event_crash(ptr_obj, msg1, msg2, lvl));
	return (EXIT_FAILURE);
}

static int	ft_init_data_for_event(t_object *ptr_obj)
{
	int		fd;

	if ((fd = ptr_obj->event.event_validetion(ptr_obj)) == EXIT_FAILURE)
	{
		return (ft_check_errorlvl(ptr_obj, ERR_BIN,
			ptr_obj->event.file_name, ERROR_EVENT));
	}
	if ((ptr_obj->event.data_buff = mmap(0, (size_t)ptr_obj->event.spcf.st_size,
			PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FILE)
	{
		return (ft_check_errorlvl(ptr_obj, "Error: nmap file",
			ptr_obj->event.file_name, SYSTEM_ERROR));
	}
	return (fd);
}

int			ft_object_event_hendler(t_object *ptr_obj)
{
	if (!ptr_obj)
		return (EXIT_FAILURE);
	if (ft_init_data_for_event(ptr_obj) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ptr_obj->event.methods.constructor_mtd(ptr_obj) == EXIT_FAILURE)
	{
		return (ft_check_errorlvl(ptr_obj, ERR_VALID_MS,
				ptr_obj->event.file_name, ERROR_EVENT));
	}
	if (ptr_obj->event.methods.parser(ptr_obj) == EXIT_FAILURE)
	{
		return (ptr_obj->event.event_crash(ptr_obj,
			"Error: parsing file ", ptr_obj->event.file_name, ERROR_EVENT));
	}
	ptr_obj->event.methods.print(ptr_obj);
	return (ptr_obj->event.event_hendler_destructor(ptr_obj));
}
