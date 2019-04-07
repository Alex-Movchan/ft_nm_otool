#include "ft_nm_otool.h"

int         main(int ac, char **av)
{
    t_object    object;

    if (ac < 2)
        return (ft_error("Error: count argumens.", NULL));
    if (PROGRAM_STATE == UNKNOWN_PROGRAM)
        ;//return (ft_error("Error: unknown program.", NULL));
    object.object_cronstructor = ft_object_cronstructor;
    object.object_cronstructor(&object);
    object.init_flag(&object, ac, av);
    if (object.object_process(&object, ac, av) == EXIT_FAILURE)
        return (object.object_crash_destructor(&object, NULL, NULL));
    return (object.object_destructor(&object));
}