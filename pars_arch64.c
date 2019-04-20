#include "ft_nm_otool.h"

static int     pars_segment_arch64(t_object *ptr_obj, void *load_cmd)
{
    struct segment_command_64	*segment;
    struct section_64			*section;
    t_data                      *data_ptr;
    int                         idx;
    int                         count;

    idx = -1;
    segment = (struct segment_command_64 *)load_cmd;
    count = segment->nsects;
    section = (void *)segment + sizeof(segment);
    while (++idx < count)
    {
        if (!(data_ptr = ptr_obj->event.methods.new_data(ptr_obj, section, SECTION)))
            return (ptr_obj->event.event_crash(ptr_obj,
                                        "Error: create new data_list", NULL, ERROR_EVENT));
        data_ptr->seqnum = ft_datatype_count(ptr_obj->event.data, SECTION);
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
    load = ptr_obj->event.data_buff + sizeof(struct mach_header_64);
    count = header64->ncmds;
    i = -1;
    while (++i < count)
    {
        if (load->cmd == LC_SEGMENT_64)
        {
            if (pars_segment_arch64(ptr_obj, load) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
        else if (load->cmd == LC_SYMTAB)
            break ;
        load = (void*)load + load->cmdsize;
    }
    if (ft_get_print_data(ptr_obj, (void*)load) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}


