/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 01:34:37 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 01:34:44 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		main(int ac, char **av)
{
	t_object	object;

	if (PROGRAM_STATE == UNKNOWN_PROGRAM)
		return (ft_error("Error: unknown program.", NULL));
	object.object_cronstructor = ft_object_cronstructor;
	object.object_cronstructor(&object);
	if (object.object_process(&object, ac, av) == EXIT_FAILURE)
		return (object.object_crash_destructor(&object, NULL, NULL));
	return (object.object_destructor(&object));
}
