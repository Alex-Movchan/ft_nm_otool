
#ifndef FT_NM_OTOOL_H
#define FT_NM_OTOOL_H

#include "libft/libft.h"
#include "loader.h"
#include "ranlib.h"
#include <fcntl.h>
#include <sys/stat.h>
# include <sys/mman.h>
#include <ar.h>

#define SET_BIT(a, n) ((a) |= (1 << n))
#define RESET_BIT(a, n) ((a) &= ~(1 << n))
#define CHECK_BIT(a, n) ((a) &= (1 << n))
#define FLAG_J  1
#define FLAG_U  2
#define FLAG_UP_U  3
#define FLAG_P  4
#define FLAG_R  5

typedef enum	e_arch
{
    UNKNOW,
	FAT,
	ARCH32,
	ARCH64,
	ARMIVE
}				t_arch;

typedef struct s_dtata
{
    int         (*data_destructor)(void *,struct s_dtata *);
}				t_data;

typedef struct	s_methods
{
	int			(*parser)(void *);
	void		(*print)(struct s_dtata *, int);
}				t_methods;

typedef struct s_event
{
    int         (*event_validetion)(void *);
    int         (*ft_event_hendler)(void *);
    int         (*event_initmethods)(void *);
    int         (*event_hendler_destructor)(void *);
    t_arch      (*get_event_arch)(struct s_event *);
    char        *file_name;
    char        *data_buff;
    t_data      *data;
    t_methods   methods;
    struct stat spcf;

}               t_event;

typedef struct      s_object
{
	int			    (*crash)(char *, char *);
    int			    (*init_flag)(struct s_object *, int, char **);
    int			    (*object_process)(struct s_object *, int, char **);
    int             (*cllback_fat)(void *);
    t_event         event;
    unsigned int    flag;
}				    t_object;



t_event         ft_event_init(void);
int         	ft_error(char *msg, char *param);
int         	ft_check_flag(int ac, char **av);
int             pars_arch64_mtd(void *patern);
int             pars_arch32_mtd(void *patern);
void            ft_object_create(t_object *ptr_obj, int ac, char **av);


#endif
