/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 23:29:24 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 23:32:18 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	ft_puthex_byt(unsigned char hex)
{
	if (0 == hex / HEX)
		ft_putchar(HEX_BASE[hex % HEX]);
	else
	{
		ft_puthex_byt(hex / (unsigned char)HEX);
		ft_putchar(HEX_BASE[hex % HEX]);
	}
}

void	ft_puthexaddr(unsigned long long int hex)
{
	if (0 == hex / HEX)
		ft_putchar(HEX_BASE[hex % HEX]);
	else
	{
		ft_puthexaddr(hex / HEX);
		ft_putchar(HEX_BASE[hex % HEX]);
	}
}

int		ft_print_hex(unsigned char *str, size_t size)
{
	int		i;

	i = -1;
	while (++i < HEX && i < (int)size)
	{
		if (str[i] < 0x10)
			ft_putchar('0');
		ft_puthex_byt(str[i]);
		ft_putchar(' ');
	}
	ft_putstr("\n");
	return (i);
}

int		ft_long_count(unsigned long long int nbr)
{
	int		count;

	count = 0;
	while (nbr > 0)
	{
		count += 1;
		nbr /= 0x10;
	}
	return (count);
}
