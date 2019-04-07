#include "ft_nm_otool.h"

int     pars_arch64_mtd(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if (ft_parser_arch64(ptr_obj) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int     pars_arch32_mtd(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if (pars_segment_arch32(ptr_obj) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
