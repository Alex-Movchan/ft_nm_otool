#include "ft_nm_otool.h"

int     pars_arch64_mtd(void *patern)
{
    t_object    *ptr_obj;

    if (!patern)
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    if (pars_segment_arch64(&ptr_obj->event) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

int     pars_arch32_mtd(void *patern)
{
    t_object    *ptr_obj;

    if (!patern)
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    if (pars_segment_arch32(&ptr_obj->event) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}