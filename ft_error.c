/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 00:23:19 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 00:24:17 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		ft_error(char *msg, char *param)
{
	if (msg && param)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putendl_fd(param, STDERR_FILENO);
	}
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}
