#include "ft_nm_otool.h"

int     ft_event_destructor(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if (ptr_obj->event.methods.destructor_mtd(ptr_obj) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    ptr_obj->event.data_buff = NULL;
    ptr_obj->event.file_name = NULL;
    ft_memset(&ptr_obj->event.spcf, 0, sizeof(struct stat));
    return (EXIT_SUCCESS);
}


int     pars_arch32_mtd(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
//    if (pars_segment_arch32(ptr_obj) == EXIT_FAILURE)
//        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
