#include "ft_nm_otool.h"

static int  ft_nm(char *file, int flag)
{
    int         file_fd;
    char        *ptr;
    struct stat specifications;

    if ((file_fd = open(file, O_RDONLY)) < 0)
        return (ft_error("Error: can not open:", file));
    if (fstat(file_fd, &specifications) < 0)
        return (ft_error("Error: can not get stat:", file));
    if (S_ISREG(specifications.st_mode) || S_ISLNK(specifications.st_mode) || S_ISSOCK(specifications.st_mode))
    {
        if ((ptr = mmap(0, (size_t) specifications.st_size, PROT_READ, MAP_PRIVATE, file_fd, 0)) == MAP_FILE)
            return (ft_error("Error: nmap file", file));
        if (ft_data_parser(file, ptr, flag) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (munmap(ptr, (size_t)specifications.st_size) == EXIT_FAILURE)
            return (ft_error("Error: munmap file:", file));
        return (EXIT_SUCCESS);
    }
    return (ft_error("Error: is not binary file", file));
}

int         main(int ac, char **av)
{
    int     flag;
    int     i;


    if (ac < 2)
        ft_error("Error: count argumens.", NULL);
    if ((flag = ft_check_flag(ac, av)) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    i = 0;
    while (++i < ac)
    {
        if (av[i][0] == '-')
            continue ;
        if (ft_nm(av[i], flag) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}