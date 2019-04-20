#include "ft_nm_otool.h"

static uint8_t ft_get_section_type(t_data *ptr_data, uint8_t n_sect)
{
    struct section_64   *tmp;

    if (n_sect == NO_SECT)
        return (' ');
    while (ptr_data)
    {
        if (ptr_data->type == SECTION)
        {
            tmp = (struct section_64*)ptr_data->ptr_data;
            if (n_sect == ptr_data->seqnum)
            {
                if (!ft_strcmp(tmp->sectname, SECT_DATA))
                    return ('d');
                if (!ft_strcmp(tmp->sectname, SECT_BSS))
                    return ('b');
                if (!ft_strcmp(tmp->sectname, SECT_TEXT))
                    return ('t');
                else
                    return ('s');
            }
        }
        ptr_data = ptr_data->next;
    }
    return ('s');

}

static uint8_t ft_get_func_type(t_data *ptr_data, uint8_t type, uint8_t n_sect)
{
    uint8_t ascii_type;
    uint8_t tmp;

    tmp = (uint8_t)(type & N_TYPE);
    if (tmp == N_UNDF || tmp == N_PBUD)
        ascii_type = 'u';
    else if (tmp == N_ABS)
        ascii_type = 'a';
    else if (tmp == N_INDR)
        ascii_type = 'i';
    else if (tmp == N_SECT)
        ascii_type = ft_get_section_type(ptr_data, n_sect);
    else
        return ('?');
    if (type & N_EXT)
        ascii_type = (uint8_t)ft_toupper(ascii_type);
    return (ascii_type);
}

int     ft_get_print_data(t_object *ptr_obj, struct symtab_command *tab)
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
        if (!(ptr = ptr_obj->event.methods.new_data(ptr_obj, (void*)str_table + arrey[i].n_un.n_strx, FUNC_NAME)))
            return (EXIT_FAILURE);
        ptr->seqnum =  ft_get_func_type(tmp, arrey[i].n_type, arrey[i].n_sect);
    }
    ft_free_datalist(&tmp);
    return (EXIT_SUCCESS);
}