#include "ft_nm_otool.h"

int     ft_event_validetion(t_object *ptr_obj)
{
    int         fd;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((fd = open(ptr_obj->event.file_name, O_RDONLY)) < 0)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: can not open:", ptr_obj->event.file_name));
    if (fstat(fd, &ptr_obj->event.spcf) < 0)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: can not get stat:", ptr_obj->event.file_name));
    if (S_ISREG(ptr_obj->event.spcf) || S_ISLNK(ptr_obj->event.spcf) || S_ISSOCK(ptr_obj->event.spcf))
        return (fd);
    return EXIT_FAILURE;
}

int     ft_event_hendler_destructor(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.destructor_mtd(ptr_obj);
    if (munmap(ptr_obj->event.data_buff, (size_t)ptr_obj->event.spcf.st_size) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: munmap file:", ptr_obj->event.file_name));
    ptr_obj->event.data_buff = NULL;
    return (EXIT_SUCCESS);
}

int     ft_event_crash_destructor(t_object *ptr_obj, char *msg1, char *msg2)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    if (ptr_obj->event.data_buff && munmap(ptr_obj->event.data_buff, (size_t)ptr_obj->event.spcf.st_size) == EXIT_FAILURE)
        return (ptr_obj->object_crash_destructor(ptr_obj, msg1, msg2));
    if (ptr_obj->event.event_destructor(ptr_obj) == EXIT_FAILURE)
        return (ptr_obj->object_crash_destructor(ptr_obj, msg1, msg2));
    ptr_obj->event.data_buff = NULL;
    return (EXIT_SUCCESS);
}

int     ft_object_event_hendler(t_object *ptr_obj)
{
    int         fd;

    if (!ptr_obj)
        return (EXIT_FAILURE);
    if ((fd = ptr_obj->event.event_validetion(ptr_obj)) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: is not binary file", ptr_obj->event.file_name));
    if ((ptr_obj->event.data_buff = mmap(0, (size_t) ptr_obj->event.spcf.st_size,
            PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FILE)
        return (ptr_obj->event.event_crash(ptr_obj, "Error: nmap file", ptr_obj->event.file_name));
    if (ptr_obj->event.methods.constructor_mtd(ptr_obj) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj, NULL, NULL));
    if (ptr_obj->event.methods.parser(ptr_obj) == EXIT_FAILURE)
        return (ptr_obj->event.event_crash(ptr_obj, NULL, NULL));
    ptr_obj->event.methods.print(ptr_obj);
    return (ptr_obj->event.event_hendler_destructor(ptr_obj));
}

int     ft_event_destructor(t_object *ptr_obj)
{
    if (!ptr_obj)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.destructor_mtd(ptr_obj);
}

void     ft_event_init(t_object *ptr_obj)
{
    if (!ptr_obj)
        return ;
    ptr_obj->event.data_buff = NULL;
    ptr_obj->event.file_name = NULL;
    ft_memset(&ptr_obj->event.spcf, 0, sizeof(struct stat));
    ptr_obj->event.event_validetion = ft_event_validetion;
    ptr_obj->event.ft_event_hendler = ft_object_event_hendler;
    ptr_obj->event.event_hendler_destructor = ft_event_hendler_destructor;
    ptr_obj->event.event_crash = ft_event_crash_destructor;
    ptr_obj->event.cllback_fat = NULL; // To go!!
    ptr_obj->event.methods.constructor_mtd = ft_constructor_mtd;
    ptr_obj->event.event_destructor = ft_event_destructor;
}