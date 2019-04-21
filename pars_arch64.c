#include "ft_nm_otool.h"

static int     pars_segment_arch64(t_object *ptr_obj, void *load_cmd)
{
    struct segment_command_64	*segment;
    struct section_64			*section;
    int                         idx;
    int                         count;

    idx = -1;
    segment = (struct segment_command_64 *)load_cmd;
    count = segment->nsects;
    section = (void *)segment + sizeof(*segment);
    SET_BIT(ptr_obj->flag, FLAG_SECTIONS);
    while (++idx < count)
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
                        "Error: create new data_list", NULL, ERROR_EVENT));
            }
        }
        section = (void *)section + sizeof(struct section_64);
    }
    RESET_BIT(ptr_obj->flag, FLAG_SECTIONS);
    return (EXIT_SUCCESS);
}



static int     ft_get_print_data64(t_object *ptr_obj, struct symtab_command *tab)
{
    t_data  *tmp;
    t_data  *ptr;
    struct nlist_64 *arrey;
    char *str_table;
    int i;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    arrey = ptr_obj->event.data_buff + tab->symoff;
    str_table = ptr_obj->event.data_buff + tab->stroff;
    tmp = ptr_obj->event.data;
    ptr_obj->event.data = NULL;
    i = -1;
    while (++i < tab->nsyms)
    {
        if (!(ptr = ptr_obj->event.methods.new_data(ptr_obj,
                (void*)str_table + arrey[i].n_un.n_strx, FUNC_NAME)))
        {
            ft_free_datalist(&tmp);
            return (EXIT_FAILURE);
        }
        ptr->seqnum =  ft_get_func_type64(tmp, arrey[i].n_type, arrey[i].n_sect);
        if ((arrey[i].n_type & N_TYPE) != N_UNDF)
        {
            SET_BIT(ptr->data_flag, ARCH_64_SHOW_ADDR);
            ptr->addr = arrey[i].n_value;
        }
    }
    ft_free_datalist(&tmp);
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
    if (PROGRAM_STATE == NM_PROGRAM)
    {
        if (ft_get_print_data64(ptr_obj, (void*)load) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

