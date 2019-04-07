#include "ft_nm_otool.h"

int     ft_data_from_section(t_object *ptr_obj, struct section_64 *section)
{
    t_data  *ptr;
    if (!ptr_obj || !section)
        return (EXIT_FAILURE);
    if ((ptr = ft_get_new_data_in_list(&(ptr_obj->event.data))) == NULL)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: create new data_list", NULL, ERROR_EVENT));

    return (EXIT_SUCCESS);
}

int     pars_segment_arch64(t_object *ptr_obj, void *load_cmd)
{
    struct segment_command_64	*segment;
    struct section_64			*section;
    int                         idx;
    int                         count;

    idx = -1;
    segment = (struct segment_command_64 *)load_cmd;
    count = segment->nsects;
    section = (void *)segment + sizeof(segment);
    while (++idx < count)
    {
        if (ft_data_from_section(ptr_obj, section) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        section = (void *)section + sizeof(section);
    }
    return (EXIT_SUCCESS);
}

int  ft_parser_arch64(t_object *ptr_obj)
{
    struct mach_header_64   *header64;
    struct load_command     *load;
    int                     i;
    int                     count;

    header64 = (struct mach_header_64*)ptr_obj->event.data_buff;
    load = (void*)ptr_obj->event.data_buff + sizeof(struct mach_header_64);
    count = header64->ncmds;
    i = -1;
    while (++i < count)
    {
        if (load->cmd == LC_SEGMENT_64)
        {
            if (pars_segment_arch64(ptr_obj, load) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
        ;
        load = (void*)load + load->cmdsize;
    }
    return (EXIT_SUCCESS);
}


