#include "ft_nm_otool.h"

int ft_object_event_hendler(t_object *ptr_obj)
{
    int fd;
    int res;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((fd = ptr_obj->event.event_validetion(ptr_obj)) == EXIT_FAILURE)
    {
        if (ptr_obj->event.error_lvl == SUCCESS)
            return (ptr_obj->event.event_crash(ptr_obj, "Error: is not binary file",
                                               ptr_obj->event.file_name, ERROR_EVENT));
        else
            return (EXIT_FAILURE);
    }
    if ((ptr_obj->event.data_buff = mmap(0, (size_t) ptr_obj->event.spcf.st_size,
                                         PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FILE)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: nmap file",
                                           ptr_obj->event.file_name, SYSTEM_ERROR));
    if ((res = ptr_obj->event.methods.constructor_mtd(ptr_obj)) == EXIT_FAILURE)
    {
        return ( ptr_obj->event.error_lvl == SUCCESS ? ptr_obj->event.event_crash(ptr_obj,
                                                                                  ptr_obj->event.file_name, "The file was not recognized as a valid object file", ERROR_EVENT)
                                                     : EXIT_FAILURE);
    }
    if (ptr_obj->event.methods.parser(ptr_obj) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj,
                                           "Error: parsing file ", ptr_obj->event.file_name, ERROR_EVENT));
    ptr_obj->event.methods.print(ptr_obj);
    return (ptr_obj->event.event_hendler_destructor(ptr_obj));
}