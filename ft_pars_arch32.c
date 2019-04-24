/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_arch32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 01:35:00 by amovchan          #+#    #+#             */
/*   Updated: 2019/04/24 23:05:03 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static int		ft_add_ptr_section32(t_object *ptr_obj, struct section *section)
{
	if (PROGRAM_STATE == NM_PROGRAM)
	{
		if (!(ptr_obj->event.methods.new_data(ptr_obj, section, SECTION)))
			return (ptr_obj->event.event_crash(ptr_obj,
				"Error: create new data_list", NULL, ERROR_EVENT));
	}
	else if (PROGRAM_STATE == OTOOL_PROGRAM)
	{
		if ((!ft_strcmp(section->sectname, SECT_TEXT) ||
			!ft_strcmp(section->sectname, SEG_TEXT)) &&
			!(ptr_obj->event.methods.new_data(ptr_obj, section, SECTION)))
		{
			return (ptr_obj->event.event_crash(ptr_obj,
					"Error: create new data_list",
				NULL, ERROR_EVENT));
		}
	}
	return (EXIT_SUCCESS);
}

static int		pars_segment_arch32(t_object *ptr_obj, void *load_cmd)
{
	struct segment_command	*segment;
	struct section			*section;
	int						idx;
	int						count;

	idx = -1;
	segment = (struct segment_command *)load_cmd;
	count = segment->nsects;
	section = (void *)segment + sizeof(*segment);
	SET_BIT(ptr_obj->flag, FLAG_SECTIONS);
	while (++idx < count)
	{
		if (ft_add_ptr_section32(ptr_obj, section) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		section = (void *)section + sizeof(struct section);
	}
	RESET_BIT(ptr_obj->flag, FLAG_SECTIONS);
	return (EXIT_SUCCESS);
}

int				ft_parser_arch32(t_object *ptr_obj)
{
	struct mach_header	*header;
	struct load_command	*load;
	int					i;
	int					count;

	header = (struct mach_header*)ptr_obj->event.data_buff;
	load = ptr_obj->event.data_buff + sizeof(*header);
	count = header->ncmds;
	i = -1;
	while (++i < count && load->cmd != LC_SYMTAB)
	{
		if (load->cmd == LC_SEGMENT)
		{
			if (pars_segment_arch32(ptr_obj, load) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		load = (void*)load + load->cmdsize;
	}
	if (PROGRAM_STATE == NM_PROGRAM)
	{
		if (ft_get_print_data32(ptr_obj, (void*)load) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
