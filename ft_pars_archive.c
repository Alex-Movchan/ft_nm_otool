#include "ft_nm_otool.h"
#include <ar.h>

int     ft_pars_archv(t_object *ptr_obj)
{
    struct ar_hdr	*hdr;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    hdr = ptr_obj->event.data_buff + SARMAG;
    ft_atoi(ft_strchr(hdr->ar_name,'/') + 1);

    return (EXIT_SUCCESS);
}