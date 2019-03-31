#include "ft_nm_otool.h"

static int     ft_event_validetion(void *patern)
{
    t_object    *ptr_obj;
    int         fd;

    if (!patern)
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    if ((fd = open(ptr_obj->event.file_name, O_RDONLY)) < 0)
        return (ptr_obj->crash("Error: can not open:", ptr_obj->event.file_name));
    if (fstat(fd, &ptr_obj->event.spcf) < 0)
        return (ptr_obj->crash("Error: can not get stat:", ptr_obj->event.file_name));
    if (S_ISREG(ptr_obj->event.spcf) || S_ISLNK(ptr_obj->event.spcf) || S_ISSOCK(ptr_obj->event.spcf))
        return (fd);
    return EXIT_FAILURE;
}

static t_arch      get_event_arch(t_event *event)
{
    unsigned int    magic;

    if (!event)
        return (UNKNOW);
    magic = *(unsigned int *)event->data_buff;
    if (magic == MH_MAGIC_64)
        return (ARCH64);
    if (magic == MH_MAGIC)
        return (ARCH32);
    if (magic == FAT_MAGIC || magic == FAT_CIGAM)
        return  (FAT);
    if (!ft_strncmp(event->data_buff, ARMAG, SARMAG))
        return (ARMIVE);
    return (UNKNOW);
}

static int      ft_init_arch_methods(void *patern)
{
    t_object    *ptr_obj;
    t_arch      arch;

    if (!patern )
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    if ((arch = ptr_obj->event.get_event_arch(&ptr_obj->event)) == UNKNOW)
        return (ptr_obj->crash("Error: unknow architecture:",
                ptr_obj->event.file_name));
    if (arch == FAT)
        return (ptr_obj->cllback_fat(patern));
    if (arch == ARMIVE)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = NULL; //To do!
    }
    else if (ARCH64 == arch || ARCH32 == arch)
    {
        ptr_obj->event.methods.print = NULL; //To do!
        ptr_obj->event.methods.parser = (ARCH64 == arch) ?
            pars_arch64_mtd : pars_arch32_mtd; //To do!
    }
    return (EXIT_SUCCESS);
}

int             ft_event_hendler_destructor(void *patern)
{
    t_object    *ptr_obj;

    if (!patern)
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    ptr_obj->event.data->data_destructor((void *)patern, ptr_obj->event.data);
    if (munmap(ptr_obj->event.data_buff, (size_t)ptr_obj->event.spcf.st_size) == EXIT_FAILURE)
        return (ptr_obj->crash("Error: munmap file:", ptr_obj->event.file_name));
    return (EXIT_SUCCESS);
}

static int      object_event_hendler(void *patern)
{
    t_object    *ptr_obj;
    int         fd;

    if (!patern)
        return (EXIT_FAILURE);
    ptr_obj = (t_object*)patern;
    if ((fd = ptr_obj->event.event_validetion(patern)) == EXIT_FAILURE)
        return (ptr_obj->crash("Error: is not binary file", ptr_obj->event.file_name));
    if ((ptr_obj->event.data_buff = mmap(0, (size_t) ptr_obj->event.spcf.st_size,
            PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FILE)
        return (ptr_obj->crash("Error: nmap file", ptr_obj->event.file_name));
    if (ptr_obj->event.event_initmethods(patern) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (ptr_obj->event.methods.parser(patern) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    ptr_obj->event.methods.print(ptr_obj->event.data, ptr_obj->flag);
    return (ptr_obj->event.event_hendler_destructor(patern));
}


t_event     ft_event_init(void)
{
    t_event event;

    event.data_buff = NULL;
    event.file_name = NULL;
    ft_memset(&event.spcf, 0, sizeof(struct stat));
    event.event_validetion = ft_event_validetion;
    event.get_event_arch = get_event_arch;
    event.ft_event_hendler = object_event_hendler;
    event.event_initmethods = ft_init_arch_methods;
    event.event_hendler_destructor = ft_event_hendler_destructor;
}