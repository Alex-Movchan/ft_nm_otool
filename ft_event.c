#include "ft_nm_otool.h"

static int ft_event_validetion(t_object *ptr_obj)
{
    int         fd;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((fd = open(ptr_obj->event.file_name, O_RDONLY)) < 0)
        return (ptr_obj->event.event_crash(ptr_obj,
        		"Error: can not open:", ptr_obj->event.file_name, ERROR_EVENT));
    if (fstat(fd, &ptr_obj->event.spcf) < 0)
        return (ptr_obj->event.event_crash(ptr_obj,
        		"Error: can not get stat:", ptr_obj->event.file_name, ERROR_EVENT));
    ptr_obj->event.offset = 0;
    if (S_ISREG(ptr_obj->event.spcf.st_mode)
    	|| S_ISLNK(ptr_obj->event.spcf.st_mode) || S_ISSOCK(ptr_obj->event.spcf.st_mode))
        return (fd);
    return EXIT_FAILURE;
}

static int ft_event_hendler_destructor(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.destructor_mtd(ptr_obj);
    ptr_obj->event.free_data(&ptr_obj->event.data);
    if (munmap(ptr_obj->event.data_buff - ptr_obj->event.offset,
            (size_t)ptr_obj->event.spcf.st_size) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj,
        		"Error: munmap file:", ptr_obj->event.file_name, SYSTEM_ERROR));
    ptr_obj->event.data_buff = NULL;
    return (EXIT_SUCCESS);
}

static int ft_event_crash_destructor(t_object *ptr_obj, char *msg1, char *msg2, t_crash_lvl lvl)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.error_lvl = lvl;
    if (ptr_obj->event.data_buff)
    {
        if (munmap(ptr_obj->event.data_buff,
                   (size_t) ptr_obj->event.spcf.st_size) == EXIT_FAILURE)
        {
            ptr_obj->event.error_lvl = SYSTEM_ERROR;
            return (ft_error(msg1, msg2));
        }
    }
    if (ptr_obj->event.event_destructor(ptr_obj) == EXIT_FAILURE)
        return (ft_error(msg1, msg2));
    ptr_obj->event.data_buff = NULL;
    return (ft_error(msg1, msg2));
}

static int ft_object_event_hendler(t_object *ptr_obj)
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
        return (ptr_obj->event.event_crash(ptr_obj,
             "Error: unknown architecture:", ptr_obj->event.file_name, ERROR_EVENT));
    }
    if (ptr_obj->event.methods.parser(ptr_obj) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj,
             "Error: parsing file ", ptr_obj->event.file_name, ERROR_EVENT));
    ptr_obj->event.methods.print(ptr_obj);
    return (ptr_obj->event.event_hendler_destructor(ptr_obj));
}

void     ft_event_init(t_object *ptr_obj)
{
    if (!ptr_obj)
        return ;
    ptr_obj->event.data_buff = NULL;
    ptr_obj->event.file_name = NULL;
    ptr_obj->event.error_lvl = SUCCESS;
    ft_memset(&ptr_obj->event.spcf, 0, sizeof(struct stat));
    ptr_obj->event.event_validetion = ft_event_validetion;
    ptr_obj->event.ft_event_hendler = ft_object_event_hendler;
    ptr_obj->event.event_hendler_destructor = ft_event_hendler_destructor;
    ptr_obj->event.event_crash = ft_event_crash_destructor;
    ptr_obj->event.cllback_fat = ft_event_fat_hendler;
    ptr_obj->event.methods.constructor_mtd = ft_constructor_mtd;
    ptr_obj->event.methods.destructor_mtd = ft_destructor_mtd;
    ptr_obj->event.free_data = ft_free_datalist;
}